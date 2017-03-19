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
#include "IoT/Modbus/RTUPort.h"
#include "IoT/Modbus/SimPort.h"
#include "IoT/Modbus/ModbusMasterImpl.h"
#include "IoT/Modbus/ModbusMasterServerHelper.h"
#include "Poco/Serial/SerialPort.h"
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
namespace Modbus {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	typedef Poco::RemotingNG::ServerHelper<IoT::Modbus::ModbusMaster> ServerHelper;

	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}
	
	void createModbusRTUMaster(const std::string& uid, Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort, Poco::Timespan timeout, Poco::Timespan interCharTimeout)
	{		
		Poco::SharedPtr<ModbusMaster> pModbusMaster = new ModbusMasterImpl<RTUPort>(new RTUPort(pSerialPort, interCharTimeout), timeout);
		std::string symbolicName = "io.macchina.modbus.rtu";
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		oid += '#';
		oid += uid;
		ServerHelper::RemoteObjectPtr pModbusMasterRemoteObject = ServerHelper::createRemoteObject(pModbusMaster, oid);
		
		Properties props;
		props.set("io.macchina.protocol", symbolicName);
		props.set("io.macchina.modbus.device", pSerialPort->device());
		
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pModbusMasterRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void createModbusSimMaster(const std::string& uid, Poco::Timespan timeout)
	{		
		Poco::SharedPtr<ModbusMaster> pModbusMaster = new ModbusMasterImpl<SimPort>(new SimPort, timeout);
		std::string symbolicName = "io.macchina.modbus.sim";
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		oid += '#';
		oid += uid;
		ServerHelper::RemoteObjectPtr pModbusMasterRemoteObject = ServerHelper::createRemoteObject(pModbusMaster, oid);
		
		Properties props;
		props.set("io.macchina.protocol", symbolicName);
		props.set("io.macchina.modbus.device", "simulation");
		
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pModbusMasterRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}
	
	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		
		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("modbus.ports", keys);
		int index = 0;
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "modbus.ports.";
			baseKey += *it;

			std::string device = _pPrefs->configuration()->getString(baseKey + ".device", "");
			std::string params = _pPrefs->configuration()->getString(baseKey + ".params", "8N1");
			int speed = _pPrefs->configuration()->getInt(baseKey + ".speed", 9600);
			Poco::Timespan timeout = 1000*_pPrefs->configuration()->getInt(baseKey + ".rtu.timeout", 2000);
			Poco::Timespan interCharTimeout = _pPrefs->configuration()->getInt(baseKey + ".rtu.interCharTimeout", speed <= 19200 ? 1500 : 750);
		
			try
			{
				if (device == "simulation")
				{
					createModbusSimMaster(Poco::NumberFormatter::format(index), timeout);
				}
				else
				{
					pContext->logger().information(Poco::format("Creating serial port for Modbus device '%s'.", device));

					Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort = new Poco::Serial::SerialPort(device, speed, params);
				
					if (_pPrefs->configuration()->getBool(baseKey + ".rs485.enable", false))
					{
						Poco::Serial::SerialPort::RS485Params rs485Params;
						rs485Params.flags = Poco::Serial::SerialPort::RS485Params::RS485_ENABLED;
						if (_pPrefs->configuration()->getBool(baseKey + ".rs485.rtsOnSend", false))
							rs485Params.flags |= Poco::Serial::SerialPort::RS485Params::RS485_RTS_ON_SEND;
						if (_pPrefs->configuration()->getBool(baseKey + ".rs485.rtsAfterSend", false))
							rs485Params.flags |= Poco::Serial::SerialPort::RS485Params::RS485_RTS_AFTER_SEND;
						if (_pPrefs->configuration()->getBool(baseKey + ".rs485.useGPIO", false))
							rs485Params.flags |= Poco::Serial::SerialPort::RS485Params::RS485_USE_GPIO;
						
						rs485Params.delayRTSBeforeSend = _pPrefs->configuration()->getInt(baseKey + ".rs485.delayRTSBeforeSend", 0);
						rs485Params.delayRTSAfterSend  = _pPrefs->configuration()->getInt(baseKey + ".rs485.delayRTSAfterSend", 0);
						rs485Params.gpioPin            = _pPrefs->configuration()->getInt(baseKey + ".rs485.gpioPin", 0);
					
						pSerialPort->configureRS485(rs485Params);
					}
								
					createModbusRTUMaster(Poco::NumberFormatter::format(index), pSerialPort, timeout, interCharTimeout);
				}
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create serial port for Modbus device '%s': %s", device, exc.displayText())); 
			}
			index++;
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
		
		ServerHelper::shutdown();
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } // namespace IoT::Modbus


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Modbus::BundleActivator)
POCO_END_MANIFEST
