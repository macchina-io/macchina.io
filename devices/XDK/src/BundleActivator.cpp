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
#include "Poco/Util/TimerTask.h"
#include "IoT/Devices/SensorServerHelper.h"
#include "IoT/Devices/AccelerometerServerHelper.h"
#include "IoT/BtLE/BlueZGATTClient.h"
#include "IoT/BtLE/PeripheralImpl.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include "Poco/String.h"
#include "Poco/StringTokenizer.h"
#include "XDKSensor.h"
#include <vector>
#include <map>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace BtLE {
namespace XDK {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}
	
	void createSensor(Peripheral::Ptr pPeripheral, const XDKSensor::Params& params)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Sensor> ServerHelper;

		Poco::SharedPtr<XDKSensor> pSensor;
		if (params.physicalQuantity == "temperature")
			pSensor = new XDKTemperatureSensor(pPeripheral, params, _pTimer);
		else if (params.physicalQuantity == "humidity")
			pSensor = new XDKHumiditySensor(pPeripheral, params, _pTimer);
		else if (params.physicalQuantity == "illuminance")
			pSensor = new XDKLightSensor(pPeripheral, params, _pTimer);
		else if (params.physicalQuantity == "airPressure")
			pSensor = new XDKAirPressureSensor(pPeripheral, params, _pTimer);
		else if (params.physicalQuantity == "soundLevel")
			pSensor = new XDKNoiseSensor(pPeripheral, params, _pTimer);
		else 
			throw Poco::InvalidArgumentException("Unknown sensor type", params.physicalQuantity);

		std::string oid(XDKSensor::SYMBOLIC_NAME);
		oid += ".";
		oid += params.physicalQuantity;
		oid += '#';
		oid += pPeripheral->address();

		ServerHelper::RemoteObjectPtr pSensorRemoteObject = ServerHelper::createRemoteObject(pSensor, oid);
		
		Properties props;
		props.set("io.macchina.device", XDKSensor::SYMBOLIC_NAME);
		props.set("io.macchina.physicalQuantity", params.physicalQuantity);
		props.set("io.macchina.btle.address", pPeripheral->address());
		
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pSensorRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

/***
	void createAccelerometer(Peripheral::Ptr pPeripheral, const XDKAccelerometer::Params& params)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Accelerometer> ServerHelper;

		Poco::SharedPtr<XDKAccelerometer> pAccelerometer;
		if (pPeripheral->modelNumber() != "CC2650 XDK")
		{
			pAccelerometer = new XDK1Accelerometer(pPeripheral, params);
		}
		else
		{
			pAccelerometer = new XDKAccelerometer(pPeripheral, params);
		}

		std::string oid(XDKAccelerometer::SYMBOLIC_NAME);
		oid += '#';
		oid += pPeripheral->address();

		ServerHelper::RemoteObjectPtr pAccelerometerRemoteObject = ServerHelper::createRemoteObject(pAccelerometer, oid);
		
		Properties props;
		props.set("io.macchina.device", XDKAccelerometer::SYMBOLIC_NAME);
		props.set("io.macchina.btle.address", pPeripheral->address());
		
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pAccelerometerRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}
***/
	void createSensors(Peripheral::Ptr pPeripheral, const std::string& baseKey)
	{
		XDKSensor::Params params;

		// humidity
		params.serviceUUID = "92dab060-7634-11e4-82f8-0800200c9a66";
		params.dataUUID    = "92dab063-7634-11e4-82f8-0800200c9a66";
		params.physicalQuantity = "humidity";
		params.physicalUnit = "%RH";
		params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".humidity.pollInterval", 10000);

		try
		{
			createSensor(pPeripheral, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK %s Sensor: %s", params.physicalQuantity, exc.displayText())); 
		}

		// temperature
		params.serviceUUID = "92dab060-7634-11e4-82f8-0800200c9a66";
		params.dataUUID    = "92dab062-7634-11e4-82f8-0800200c9a66";
		params.physicalQuantity = "ambientTemperature";
		params.physicalUnit = IoT::Devices::Sensor::PHYSICAL_UNIT_DEGREES_CELSIUS;
		params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".ambientTemperature.pollInterval", 10000);
		
		try
		{
			createSensor(pPeripheral, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK %s Sensor: %s", params.physicalQuantity, exc.displayText())); 
		}

		// air pressure
		params.serviceUUID = "92dab060-7634-11e4-82f8-0800200c9a66";
		params.dataUUID    = "92dab061-7634-11e4-82f8-0800200c9a66";
		params.physicalQuantity = "airPressure";
		params.physicalUnit = "hPa";
		params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".airPressure.pollInterval", 10000);
		
		try
		{
			createSensor(pPeripheral, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK %s Sensor: %s", params.physicalQuantity, exc.displayText())); 
		}

		// illuminance
		params.serviceUUID = "38eb02c0-7540-11e4-82f8-0800200c9a66";
		params.dataUUID    = "38eb02c1-7540-11e4-82f8-0800200c9a66";
		params.physicalQuantity = "illuminance";
		params.physicalUnit = IoT::Devices::Sensor::PHYSICAL_UNIT_LUX;
		params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".illuminance.pollInterval", 10000);
		
		try
		{
			createSensor(pPeripheral, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK %s Sensor: %s", params.physicalQuantity, exc.displayText())); 
		}

		// noise
		params.serviceUUID = "01033830-754c-11e4-82f8-0800200c9a66";
		params.dataUUID    = "01033831-754c-11e4-82f8-0800200c9a66";
		params.physicalQuantity = "soundLevel";
		params.physicalUnit = "dB SPL";
		params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".noise.pollInterval", 10000);
		
		try
		{
			createSensor(pPeripheral, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK %s Sensor: %s", params.physicalQuantity, exc.displayText())); 
		}

/***
		// accelerometer
		XDKAccelerometer::Params accParams;
		if (pPeripheral->modelNumber() != "CC2650 XDK")
		{
			accParams.serviceUUID = "f000aa10-0451-4000-b000-000000000000";
			accParams.controlUUID = "f000aa12-0451-4000-b000-000000000000";
			accParams.dataUUID    = "f000aa11-0451-4000-b000-000000000000";
			accParams.periodUUID  = "f000aa13-0451-4000-b000-000000000000";
			accParams.notifUUID   = "00002902-0000-1000-8000-00805f9b34fb";
		}
		else
		{
			accParams.serviceUUID = "f000aa80-0451-4000-b000-000000000000";
			accParams.controlUUID = "f000aa82-0451-4000-b000-000000000000";
			accParams.dataUUID    = "f000aa81-0451-4000-b000-000000000000";
			accParams.periodUUID  = "f000aa83-0451-4000-b000-000000000000";
			accParams.notifUUID   = "00002902-0000-1000-8000-00805f9b34fb";
		}

		try
		{
			createAccelerometer(pPeripheral, accParams);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK Accelerometer: %s", exc.displayText())); 
		}
***/
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		_pTimer = new Poco::Util::Timer;
	
		Poco::Util::AbstractConfiguration::Keys keys;
		std::string helperPath = _pPrefs->configuration()->getString("btle.bluez.helper");
		_pPrefs->configuration()->keys("XDK.sensors", keys);
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "XDK.sensors.";
			baseKey += *it;

			std::string address = _pPrefs->configuration()->getString(baseKey + ".address");
		
			try
			{	
				GATTClient::Ptr pGATTClient = new BlueZGATTClient(helperPath);
				Peripheral::Ptr pPeripheral = new PeripheralImpl(address, pGATTClient);
				pPeripheral->connected += Poco::delegate(this, &BundleActivator::onConnected);
				pPeripheral->disconnected += Poco::delegate(this, &BundleActivator::onDisconnected);	

				PeripheralInfo info;
				info.pPeripheral = pPeripheral;
				info.baseKey = baseKey;
				info.reconnectDelay = MIN_RECONNECT_DELAY;
				info.haveSensors = false;
				_peripherals.push_back(info);		

				pPeripheral->connect(GATTClient::GATT_CONNECT_NOWAIT);
			}
			catch (Poco::Exception& exc)
			{
				_pContext->logger().error(Poco::format("Cannot create peripheral object for device %s: %s", address, exc.displayText()));
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
		_peripherals.clear();

		_pPrefs = 0;
		_pContext = 0;
	}
	
protected:
	class ReconnectTask: public Poco::Util::TimerTask
	{
	public:
		ReconnectTask(BundleActivator& activator, Peripheral::Ptr pPeripheral):
			_bundleActivator(activator),
			_pPeripheral(pPeripheral)
		{
		}

		void run()
		{
			_bundleActivator.connect(_pPeripheral);
		}

	private:
		BundleActivator& _bundleActivator;
		Peripheral::Ptr _pPeripheral;
	};

	void onConnected(const void* pSender)
	{
		for (std::vector<PeripheralInfo>::iterator it = _peripherals.begin(); it != _peripherals.end(); ++it)
		{
			if (it->pPeripheral.get() == pSender)
			{
				_pContext->logger().information(Poco::format("Peripheral connected: %s", it->pPeripheral->address()));
				try
				{
					_pContext->logger().debug(Poco::format("Manufacturer Name: %s", it->pPeripheral->manufacturerName()));
					_pContext->logger().debug(Poco::format("Model Number: %s", it->pPeripheral->modelNumber()));
					if (!it->haveSensors)
					{
						createSensors(it->pPeripheral, it->baseKey);
						it->haveSensors = true;
					}
					it->reconnectDelay = MIN_RECONNECT_DELAY;
				}
				catch (Poco::Exception& exc)
				{
					_pContext->logger().error(Poco::format("Failed to create sensors for device %s: %s", it->pPeripheral->address(), exc.displayText()));
				}
				break;
			}
		}
	}

	void onDisconnected(const void* pSender)
	{
		for (std::vector<PeripheralInfo>::iterator it = _peripherals.begin(); it != _peripherals.end(); ++it)
		{
			if (it->pPeripheral.get() == pSender)
			{
				_pContext->logger().information(Poco::format("Peripheral disconnected: %s", it->pPeripheral->address()));

				it->reconnectDelay *= 2;
				if (it->reconnectDelay > MAX_RECONNECT_DELAY)
					it->reconnectDelay = MAX_RECONNECT_DELAY;
				Poco::Clock clock;
				clock += static_cast<Poco::Clock::ClockDiff>(it->reconnectDelay)*1000;
				_pTimer->schedule(new ReconnectTask(*this, it->pPeripheral), clock);
				break;
			}
		}
	}

	void connect(Peripheral::Ptr pPeripheral)
	{
		try
		{
			pPeripheral->connect(GATTClient::GATT_CONNECT_NOWAIT);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot reconnect to device %s: %s", pPeripheral->address(), exc.displayText()));
		}
	}
	
	enum 
	{
		MIN_RECONNECT_DELAY = 1000,
		MAX_RECONNECT_DELAY = 30000
	};

private:
	struct PeripheralInfo
	{
		Peripheral::Ptr pPeripheral;
		std::string baseKey;
		unsigned reconnectDelay;
		bool haveSensors;
	};

	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	Poco::SharedPtr<Poco::Util::Timer> _pTimer;
	std::vector<PeripheralInfo> _peripherals;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } } // namespace IoT::BtLE::XDK


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::BtLE::XDK::BundleActivator)
POCO_END_MANIFEST
