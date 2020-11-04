//
// BundleActivator.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "GNSSSensorImpl.h"
#include "VoltageSensorImpl.h"
#include "IoT/Devices/GNSSSensorServerHelper.h"
#include "IoT/Devices/SensorServerHelper.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/File.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace Legato {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void createGNSSSensor()
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::GNSSSensor> ServerHelper;

		Poco::SharedPtr<GNSSSensorImpl> pGNSSSensor = new GNSSSensorImpl;
		Poco::RemotingNG::Identifiable::ObjectId oid = pGNSSSensor->getPropertyString("symbolicName");
		std::string type = pGNSSSensor->getPropertyString("type");
		oid += "#0";
		ServerHelper::RemoteObjectPtr pGNSSSensorRemoteObject = ServerHelper::createRemoteObject(pGNSSSensor, oid);

		Properties props;
		props.set("io.macchina.device", oid);
		props.set("io.macchina.deviceType", type);

		_serviceRefs.push_back(_pContext->registry().registerService(oid, pGNSSSensorRemoteObject, props));
	}

	void createVoltageSensor(const std::string& cmPath)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Sensor> ServerHelper;

		Poco::SharedPtr<VoltageSensorImpl> pVoltageSensor = new VoltageSensorImpl(cmPath);
		Poco::RemotingNG::Identifiable::ObjectId oid = pVoltageSensor->getPropertyString("symbolicName");
		std::string type = pVoltageSensor->getPropertyString("type");
		oid += "#0";
		ServerHelper::RemoteObjectPtr pVoltageSensorRemoteObject = ServerHelper::createRemoteObject(pVoltageSensor, oid);

		Properties props;
		props.set("io.macchina.device", oid);
		props.set("io.macchina.deviceType", type);
		props.set("io.macchina.physicalQuantity", pVoltageSensor->getPropertyString("physicalQuantity"));
		props.set("io.macchina.physicalUnit", pVoltageSensor->getPropertyString("physicalUnit"));

		_serviceRefs.push_back(_pContext->registry().registerService(oid, pVoltageSensorRemoteObject, props));
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		try
		{
			Poco::File nmeaFile("/dev/nmea");
			if (nmeaFile.exists())
			{
				if (_pPrefs->configuration()->getBool("legato.gnss.enable", true))
				{
					pContext->logger().information("Creating Legato GNSSSensor");
					createGNSSSensor();
				}
			}
		}
		catch (Poco::Exception& exc)
		{
			pContext->logger().error(Poco::format("Cannot create Legato GNSS Sensor: %s", exc.displayText()));
		}

		try
		{
			std::string cmPath = getStringConfig("legato.cm.path", "/legato/systems/current/bin/cm");
			Poco::File cmFile(cmPath);
			if (cmFile.exists() && cmFile.canExecute())
			{
				pContext->logger().information("Creating Legato Module Power Supply Voltage Sensor");
				createVoltageSensor(cmPath);
			}
		}
		catch (Poco::Exception& exc)
		{
			pContext->logger().error(Poco::format("Cannot create Legato Voltage Sensor: %s", exc.displayText()));
		}
	}

	void stop(BundleContext::Ptr pContext)
	{
		for (std::vector<ServiceRef::Ptr>::iterator it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
		{
			_pContext->registry().unregisterService(*it);
		}
		_serviceRefs.clear();
		_pPrefs = 0;
		_pContext = 0;
	}

protected:
	bool getBoolConfig(const std::string& key)
	{
		return _pPrefs->configuration()->getBool(key, _pContext->thisBundle()->properties().getBool(key));
	}

	bool getBoolConfig(const std::string& key, bool deflt)
	{
		return _pPrefs->configuration()->getBool(key, _pContext->thisBundle()->properties().getBool(key, deflt));
	}

	int getIntConfig(const std::string& key)
	{
		return _pPrefs->configuration()->getInt(key, _pContext->thisBundle()->properties().getInt(key));
	}

	int getIntConfig(const std::string& key, int deflt)
	{
		return _pPrefs->configuration()->getInt(key, _pContext->thisBundle()->properties().getInt(key, deflt));
	}

	std::string getStringConfig(const std::string& key)
	{
		return _pPrefs->configuration()->getString(key, _pContext->thisBundle()->properties().getString(key));
	}

	std::string getStringConfig(const std::string& key, const std::string& deflt)
	{
		return _pPrefs->configuration()->getString(key, _pContext->thisBundle()->properties().getString(key, deflt));
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } // namespace IoT::Legato


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Legato::BundleActivator)
POCO_END_MANIFEST
