//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
#include "IoT/Devices/GNSSSensorServerHelper.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace GNSS {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}
	
	void createGNSSSensor(Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::GNSSSensor> ServerHelper;
		
		Poco::SharedPtr<GNSSSensorImpl> pGNSSSensor = new GNSSSensorImpl(pSerialPort);
		Poco::RemotingNG::Identifiable::ObjectId oid = pGNSSSensor->getPropertyString("symbolicName");
		oid += "#0";
		ServerHelper::RemoteObjectPtr pGNSSSensorRemoteObject = ServerHelper::createRemoteObject(pGNSSSensor, oid);
		
		Properties props;
		props.set("io.macchina.device", oid);
		props.set("io.macchina.serialport.device", pSerialPort->device());
		
		_serviceRef = _pContext->registry().registerService(oid, pGNSSSensorRemoteObject, props);
	}
	
	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		std::string device = _pPrefs->configuration()->getString("gnss.nmea.device", "");
		std::string params = _pPrefs->configuration()->getString("gnss.nmea.params", "8N1");
		int speed = _pPrefs->configuration()->getInt("gnss.nmea.speed", 4800);
		
		try
		{
			if (!device.empty())
			{
				pContext->logger().information(Poco::format("Creating GNSSSensor for serial port '%s'.", device));

				createGNSSSensor(new Poco::Serial::SerialPort(device, speed, params));
			}
		}
		catch (Poco::Exception& exc)
		{
			pContext->logger().error(Poco::format("Cannot create serial port for device '%s': %s", device, exc.displayText())); 
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		_pContext->registry().unregisterService(_serviceRef);
		_serviceRef = 0;
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
	ServiceRef::Ptr _serviceRef;
};


} } // namespace IoT::GNSS


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::GNSS::BundleActivator)
POCO_END_MANIFEST
