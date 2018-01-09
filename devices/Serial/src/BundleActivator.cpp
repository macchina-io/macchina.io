//
// BundleActivator.cpp
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
#include "SerialDeviceImpl.h"
#include "IoT/Devices/SerialDeviceServerHelper.h"
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
using Poco::Serial::SerialPort;


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
		std::string type = pDevice->getPropertyString("type");
		std::string symbolicName = pDevice->getPropertyString("symbolicName");
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		oid += '#';
		oid += uid;
		ServerHelper::RemoteObjectPtr pDeviceRemoteObject = ServerHelper::createRemoteObject(pDevice, oid);
		
		Properties props;
		props.set("io.macchina.device", symbolicName);
		props.set("io.macchina.deviceType", type);
		props.set("io.macchina.serialport.device", pSerialPort->device());
		
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pDeviceRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}
	
	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		
		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("serial.ports", keys);

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
				
				if (_pPrefs->configuration()->getBool(baseKey + ".rs485.enable", false))
				{
					SerialPort::RS485Params rs485Params;
					rs485Params.flags = SerialPort::RS485Params::RS485_ENABLED;
					if (_pPrefs->configuration()->getBool(baseKey + ".rs485.rtsOnSend", false))
						rs485Params.flags |= SerialPort::RS485Params::RS485_RTS_ON_SEND;
					if (_pPrefs->configuration()->getBool(baseKey + ".rs485.rtsAfterSend", false))
						rs485Params.flags |= SerialPort::RS485Params::RS485_RTS_AFTER_SEND;
					if (_pPrefs->configuration()->getBool(baseKey + ".rs485.useGPIO", false))
						rs485Params.flags |= SerialPort::RS485Params::RS485_USE_GPIO;
						
					rs485Params.delayRTSBeforeSend = _pPrefs->configuration()->getInt(baseKey + ".rs485.delayRTSBeforeSend", 0);
					rs485Params.delayRTSAfterSend  = _pPrefs->configuration()->getInt(baseKey + ".rs485.delayRTSAfterSend", 0);
					rs485Params.gpioPin            = _pPrefs->configuration()->getInt(baseKey + ".rs485.gpioPin", 0);
					
					pSerialPort->configureRS485(rs485Params);
				}
				
				createSerialDevice(*it, pSerialPort);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create serial port for device '%s': %s", device, exc.displayText())); 
			}
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
	
private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } // namespace IoT::Serial


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Serial::BundleActivator)
POCO_END_MANIFEST
