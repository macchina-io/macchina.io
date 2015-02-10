//
// BundleActivator.cpp
//
// $Id: //iot/Main/Tf/src/BundleActivator.cpp#2 $
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
#include "IoT/Serial/SerialDeviceImpl.h"
#include "IoT/Devices/SerialDeviceServerHelper.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include <map>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace Serial {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}
	
	void createSerialDevice(const std::string& uid, SerialDeviceImpl::SerialPortPtr pSerialPort)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::SerialDevice> ServerHelper;
		
		Poco::SharedPtr<IoT::Devices::SerialDevice> pDevice = new SerialDeviceImpl(pSerialPort);
		std::string symbolicName = pDevice->getPropertyString("symbolicName");
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		oid += '#';
		oid += uid;
		typename ServerHelper::RemoteObjectPtr pDeviceRemoteObject = ServerHelper::createRemoteObject(pDevice, oid);
		
		Properties props;
		props.set("io.macchina.device", oid);
		props.set("io.macchina.serialport.device", pSerialPort->device());
		
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pDeviceRemoteObject, props);
	}
	
	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		
		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("serial.ports", keys);
		int index = 0;
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "serial.ports.";
			baseKey += *it;

			std::string device = _pPrefs->configuration()->getString(baseKey + ".device", "");
			std::string params = _pPrefs->configuration()->getString(baseKey + ".params", "8N1");
			int speed = _pPrefs->configuration()->getInt(baseKey + ".speed", 9600);
		
			try
			{
				pContext->logger().information(Poco::format("Creating serial port for device '%s'.", device));

				SerialDeviceImpl::SerialPortPtr pSerialPort = new SerialPort(device, speed, params);
				createSerialDevice(Poco::NumberFormatter::format(index), pSerialPort);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create serial port for device '%s': %s", device, exc.displayText())); 
			}
			index++;
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
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
};


} } // namespace IoT::Serial


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Serial::BundleActivator)
POCO_END_MANIFEST
