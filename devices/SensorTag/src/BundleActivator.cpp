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
#include "Poco/Util/Timer.h"
#include "IoT/Devices/SensorServerHelper.h"
#include "IoT/BtLE/BlueZGATTClient.h"
#include "IoT/BtLE/PeripheralImpl.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include "Poco/String.h"
#include "Poco/StringTokenizer.h"
#include "SensorTag.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace BtLE {
namespace SensorTag {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}
	
	void createSensor(Peripheral::Ptr pPeripheral, const SensorTagSensor::Params& params)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Sensor> ServerHelper;

		Poco::SharedPtr<SensorTagSensor> pSensor;
		if (params.physicalQuantity == "temperature")
			pSensor = new SensorTagTemperatureSensor(pPeripheral, params, _pTimer);
		else if (params.physicalQuantity == "humidity")
			pSensor = new SensorTagHumiditySensor(pPeripheral, params, _pTimer);
		else if (params.physicalQuantity == "illuminance")
			pSensor = new SensorTagLightSensor(pPeripheral, params, _pTimer);
		else if (params.physicalQuantity == "airPressure")
			pSensor = new SensorTagAirPressureSensor(pPeripheral, params, _pTimer);
		else
			throw Poco::InvalidArgumentException("Unknown sensor type", params.physicalQuantity);

		std::string oid(SensorTagSensor::SYMBOLIC_NAME);
		oid += ".";
		oid += params.physicalQuantity;
		oid += '#';
		oid += pPeripheral->address();

		ServerHelper::RemoteObjectPtr pSensorRemoteObject = ServerHelper::createRemoteObject(pSensor, oid);
		
		Properties props;
		props.set("io.macchina.device", SensorTagSensor::SYMBOLIC_NAME);
		props.set("io.macchina.physicalQuantity", params.physicalQuantity);
		
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pSensorRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}
	
	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		_pTimer = new Poco::Util::Timer;
	
		Poco::Util::AbstractConfiguration::Keys keys;
		std::string helperPath = _pPrefs->configuration()->getString("sensortag.bluez.helper");
		_pPrefs->configuration()->keys("sensortag.sensors", keys);
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "sensortag.sensors.";
			baseKey += *it;

			std::string address = _pPrefs->configuration()->getString(baseKey + ".address");
			
			GATTClient::Ptr pGATTClient = new BlueZGATTClient(helperPath);
			Peripheral::Ptr pPeripheral = new PeripheralImpl(address, pGATTClient);
			
			SensorTagSensor::Params params;
			// humidity
			params.serviceUUID = "f000aa20-0451-4000-b000-000000000000";
			params.controlUUID = "f000aa22-0451-4000-b000-000000000000";
			params.dataUUID    = "f000aa21-0451-4000-b000-000000000000";
			params.physicalQuantity = "humidity";
			params.physicalUnit = "%RH";
			params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".humidity.pollInterval", 10000);

			try
			{
				createSensor(pPeripheral, params);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create SensorTag Sensor: %s", exc.displayText())); 
			}

			// ambient temperature
			params.serviceUUID = "f000aa20-0451-4000-b000-000000000000";
			params.controlUUID = "f000aa22-0451-4000-b000-000000000000";
			params.dataUUID    = "f000aa21-0451-4000-b000-000000000000";
			params.physicalQuantity = "temperature";
			params.physicalUnit = IoT::Devices::Sensor::PHYSICAL_UNIT_DEGREES_CELSIUS;
			params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".temperature.pollInterval", 10000);
			
			try
			{
				createSensor(pPeripheral, params);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create SensorTag Sensor: %s", exc.displayText())); 
			}

			// illuminance
			params.serviceUUID = "f000aa70-0451-4000-b000-000000000000";
			params.controlUUID = "f000aa72-0451-4000-b000-000000000000";
			params.dataUUID    = "f000aa71-0451-4000-b000-000000000000";
			params.physicalQuantity = "illuminance";
			params.physicalUnit = IoT::Devices::Sensor::PHYSICAL_UNIT_LUX;
			params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".illuminance.pollInterval", 10000);
			
			try
			{
				createSensor(pPeripheral, params);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create SensorTag Sensor: %s", exc.displayText())); 
			}

			// air pressure
			params.serviceUUID = "f000aa40-0451-4000-b000-000000000000";
			params.controlUUID = "f000aa42-0451-4000-b000-000000000000";
			params.dataUUID    = "f000aa41-0451-4000-b000-000000000000";
			params.physicalQuantity = "airPressure";
			params.physicalUnit = "hPa";
			params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".airPressure.pollInterval", 10000);
			
			try
			{
				createSensor(pPeripheral, params);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create SensorTag Sensor: %s", exc.displayText())); 
			}
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		_pTimer->cancel(true);
		_pTimer = 0;
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
	Poco::SharedPtr<Poco::Util::Timer> _pTimer;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } } // namespace IoT::BtLE::SensorTag


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::BtLE::SensorTag::BundleActivator)
POCO_END_MANIFEST
