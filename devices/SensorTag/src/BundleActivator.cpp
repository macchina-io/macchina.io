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
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include "IoT/Devices/SensorServerHelper.h"
#include "IoT/Devices/AccelerometerServerHelper.h"
#include "IoT/BtLE/PeripheralFactory.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include "Poco/String.h"
#include "Poco/StringTokenizer.h"
#include "SensorTag.h"
#include "SensorTagAccelerometer.h"
#include "SensorTagCC1352Accelerometer.h"
#include <vector>
#include <map>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;
using namespace std::string_literals;


namespace IoT {
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

	enum SensorTagType
	{
		TYPE_CC2541,
		TYPE_CC2650,
		TYPE_CC1352
	};

	SensorTagType sensorTagType(const std::string& modelNumber, const std::string& type)
	{
		if (isSensorTagCC1352(modelNumber, type))
			return TYPE_CC1352;
		else if (isSensorTagCC2650(modelNumber, type))
			return TYPE_CC2650;
		else 
			return TYPE_CC2541;
	}

	bool isSensorTagCC2541(const std::string& modelNumber, const std::string& type)
	{
		// Original Sensor Tag
		return Poco::icompare(type, "CC2541"s) == 0 || (type.empty() && modelNumber != "CC2650 SensorTag"s && modelNumber != "Model Number"s);
	}
	
	bool isSensorTagCC2650(const std::string& modelNumber, const std::string& type)
	{
		// Sensor Tag 2
		return Poco::icompare(type, "CC2650"s) == 0 || (type.empty() && modelNumber == "CC2650 SensorTag"s);
	}

	bool isSensorTagCC1352(const std::string& modelNumber, const std::string& type)
	{
		// LaunchPad SensorTag
		return Poco::icompare(type, "CC1352"s) == 0 || (type.empty() && modelNumber == "Model Number"s);
	}

	void createSensor(BtLE::Peripheral::Ptr pPeripheral, SensorTagType type, const SensorTagSensor::Params& params)
	{
		using ServerHelper = Poco::RemotingNG::ServerHelper<IoT::Devices::Sensor>;

		Poco::SharedPtr<SensorTagSensor> pSensor;
		if (type == TYPE_CC1352)
		{
			if (params.physicalQuantity == "temperature"s)
				pSensor = new SensorTagCC1352Sensor(pPeripheral, params, _pTimer);
			else if (params.physicalQuantity == "humidity"s)
				pSensor = new SensorTagCC1352Sensor(pPeripheral, params, _pTimer);
			else if (params.physicalQuantity == "illuminance"s)
				pSensor = new SensorTagCC1352Sensor(pPeripheral, params, _pTimer);
			else
				throw Poco::InvalidArgumentException("Unknown sensor type"s, params.physicalQuantity);
		}
		else if (type == TYPE_CC2650)
		{
			if (params.physicalQuantity == "temperature"s)
				pSensor = new SensorTagCC2650AmbientTemperatureSensor(pPeripheral, params, _pTimer);
			else if (params.physicalQuantity == "objectTemperature"s)
				pSensor = new SensorTagCC2650IRObjectTemperatureSensor(pPeripheral, params, _pTimer);
			else if (params.physicalQuantity == "humidity"s)
				pSensor = new SensorTagHumiditySensor(pPeripheral, params, _pTimer);
			else if (params.physicalQuantity == "illuminance"s)
				pSensor = new SensorTagCC2650LightSensor(pPeripheral, params, _pTimer);
			else if (params.physicalQuantity == "airPressure"s)
				pSensor = new SensorTagCC2650AirPressureSensor(pPeripheral, params, _pTimer);
			else
				throw Poco::InvalidArgumentException("Unknown sensor type"s, params.physicalQuantity);
		}
		else
		{
			if (params.physicalQuantity == "temperature"s)
				pSensor = new SensorTagCC2541AmbientTemperatureSensor(pPeripheral, params, _pTimer);
			else if (params.physicalQuantity == "objectTemperature"s)
				pSensor = new SensorTagCC2541IRObjectTemperatureSensor(pPeripheral, params, _pTimer);
			else if (params.physicalQuantity == "humidity"s)
				pSensor = new SensorTagHumiditySensor(pPeripheral, params, _pTimer);
			else if (params.physicalQuantity == "airPressure"s)
				pSensor = new SensorTagCC2541AirPressureSensor(pPeripheral, params, _pTimer);
			else
				throw Poco::InvalidArgumentException("Unknown sensor type"s, params.physicalQuantity);
		}

		std::string oid(SensorTagSensor::SYMBOLIC_NAME);
		oid += ".";
		oid += params.physicalQuantity;
		oid += '#';
		oid += pPeripheral->address();

		ServerHelper::RemoteObjectPtr pSensorRemoteObject = ServerHelper::createRemoteObject(pSensor, oid);

		Properties props;
		props.set("io.macchina.device"s, SensorTagSensor::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType"s, SensorTagSensor::TYPE);
		props.set("io.macchina.physicalQuantity"s, params.physicalQuantity);
		props.set("io.macchina.btle.address"s, pPeripheral->address());

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pSensorRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void createAccelerometer(BtLE::Peripheral::Ptr pPeripheral, SensorTagType type, const SensorTagAccelerometer::Params& params)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Accelerometer> ServerHelper;

		Poco::SharedPtr<IoT::Devices::Accelerometer> pAccelerometer;
		if (type == TYPE_CC1352)
		{
			pAccelerometer = new SensorTagCC1352Accelerometer(pPeripheral);
		}
		else if (type == TYPE_CC2650)
		{
			pAccelerometer = new SensorTagCC2650Accelerometer(pPeripheral, params);
		}
		else
		{
			pAccelerometer = new SensorTagCC2541Accelerometer(pPeripheral, params);
		}

		std::string oid(SensorTagAccelerometer::SYMBOLIC_NAME);
		oid += '#';
		oid += pPeripheral->address();

		ServerHelper::RemoteObjectPtr pAccelerometerRemoteObject = ServerHelper::createRemoteObject(pAccelerometer, oid);

		Properties props;
		props.set("io.macchina.device"s, SensorTagAccelerometer::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType"s, SensorTagAccelerometer::TYPE);
		props.set("io.macchina.btle.address"s, pPeripheral->address());

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pAccelerometerRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void createSensors(BtLE::Peripheral::Ptr pPeripheral, SensorTagType type, const std::string& baseKey)
	{
		SensorTagSensor::Params params;

		// humidity
		params.serviceUUID = Poco::UUID("f000aa20-0451-4000-b000-000000000000"s);
		params.controlUUID = Poco::UUID("f000aa22-0451-4000-b000-000000000000"s);
		params.dataUUID    = Poco::UUID("f000aa21-0451-4000-b000-000000000000"s);
		params.physicalQuantity = "humidity";
		params.physicalUnit = "%";
		params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".humidity.pollInterval"s, 10000);

		try
		{
			createSensor(pPeripheral, type, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error("Cannot create SensorTag %s Sensor: %s"s, params.physicalQuantity, exc.displayText());
		}

		// ambient temperature
		params.serviceUUID = Poco::UUID("f000aa00-0451-4000-b000-000000000000"s);
		params.controlUUID = Poco::UUID("f000aa02-0451-4000-b000-000000000000"s);
		params.dataUUID    = Poco::UUID("f000aa01-0451-4000-b000-000000000000"s);
		params.physicalQuantity = "temperature";
		params.physicalUnit = IoT::Devices::Sensor::PHYSICAL_UNIT_DEGREES_CELSIUS;
		params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".temperature.pollInterval"s, 10000);

		try
		{
			createSensor(pPeripheral, type, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error("Cannot create SensorTag %s Sensor: %s"s, params.physicalQuantity, exc.displayText());
		}

		// object temperature
		params.serviceUUID = Poco::UUID("f000aa00-0451-4000-b000-000000000000"s);
		params.controlUUID = Poco::UUID("f000aa02-0451-4000-b000-000000000000"s);
		params.dataUUID    = Poco::UUID("f000aa01-0451-4000-b000-000000000000"s);
		params.physicalQuantity = "objectTemperature";
		params.physicalUnit = IoT::Devices::Sensor::PHYSICAL_UNIT_DEGREES_CELSIUS;
		params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".objectTemperature.pollInterval"s, 10000);

		try
		{
			if (type != TYPE_CC1352)
			{
				createSensor(pPeripheral, type, params);
			}
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error("Cannot create SensorTag %s Sensor: %s"s, params.physicalQuantity, exc.displayText());
		}

		// illuminance
		params.serviceUUID = Poco::UUID("f000aa70-0451-4000-b000-000000000000"s);
		params.controlUUID = Poco::UUID("f000aa72-0451-4000-b000-000000000000"s);
		params.dataUUID    = Poco::UUID("f000aa71-0451-4000-b000-000000000000"s);
		params.physicalQuantity = "illuminance";
		params.physicalUnit = IoT::Devices::Sensor::PHYSICAL_UNIT_LUX;
		params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".illuminance.pollInterval"s, 10000);

		try
		{
			if (type == TYPE_CC2650 || type == TYPE_CC1352)
			{
				createSensor(pPeripheral, type, params);
			}
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error("Cannot create SensorTag %s Sensor: %s"s, params.physicalQuantity, exc.displayText());
		}

		// air pressure
		params.serviceUUID = Poco::UUID("f000aa40-0451-4000-b000-000000000000"s);
		params.controlUUID = Poco::UUID("f000aa42-0451-4000-b000-000000000000"s);
		params.dataUUID    = Poco::UUID("f000aa41-0451-4000-b000-000000000000"s);
		params.physicalQuantity = "airPressure";
		params.physicalUnit = "hPa";
		params.pollInterval = _pPrefs->configuration()->getInt(baseKey + ".airPressure.pollInterval"s, 10000);

		try
		{
			if (type != TYPE_CC1352)
			{
				createSensor(pPeripheral, type, params);
			}
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error("Cannot create SensorTag %s Sensor: %s"s, params.physicalQuantity, exc.displayText());
		}

		// accelerometer
		SensorTagAccelerometer::Params accParams;
		if (type == TYPE_CC1352)
		{
			// no accParams
		}
		else if (type == TYPE_CC2650)
		{
			accParams.serviceUUID = Poco::UUID("f000aa80-0451-4000-b000-000000000000"s);
			accParams.controlUUID = Poco::UUID("f000aa82-0451-4000-b000-000000000000"s);
			accParams.dataUUID    = Poco::UUID("f000aa81-0451-4000-b000-000000000000"s);
			accParams.periodUUID  = Poco::UUID("f000aa83-0451-4000-b000-000000000000"s);
			accParams.notifUUID   = Poco::UUID("00002902-0000-1000-8000-00805f9b34fb"s);
		}
		else 
		{
			accParams.serviceUUID = Poco::UUID("f000aa10-0451-4000-b000-000000000000"s);
			accParams.controlUUID = Poco::UUID("f000aa12-0451-4000-b000-000000000000"s);
			accParams.dataUUID    = Poco::UUID("f000aa11-0451-4000-b000-000000000000"s);
			accParams.periodUUID  = Poco::UUID("f000aa13-0451-4000-b000-000000000000"s);
			accParams.notifUUID   = Poco::UUID("00002902-0000-1000-8000-00805f9b34fb"s);
		}

		try
		{
			createAccelerometer(pPeripheral, type, accParams);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error("Cannot create SensorTag Accelerometer: %s"s, exc.displayText());
		}
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		_pTimer = new Poco::Util::Timer;

		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("sensortag.sensors"s, keys);

		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "sensortag.sensors.";
			baseKey += *it;

			std::string address = _pPrefs->configuration()->getString(baseKey + ".address"s);
			std::string type = _pPrefs->configuration()->getString(baseKey + ".type"s, ""s);

			try
			{
				IoT::BtLE::PeripheralFactory::Ptr pPeripheralFactory = ServiceFinder::find<IoT::BtLE::PeripheralFactory>(pContext);
				BtLE::Peripheral::Ptr pPeripheral = pPeripheralFactory->createPeripheral(address);

				pPeripheral->connected += Poco::delegate(this, &BundleActivator::onConnected);
				pPeripheral->disconnected += Poco::delegate(this, &BundleActivator::onDisconnected);

				PeripheralInfo info;
				info.pPeripheral = pPeripheral;
				info.type = type;
				info.baseKey = baseKey;
				info.reconnectDelay = MIN_RECONNECT_DELAY;
				info.haveSensors = false;
				_peripherals.push_back(info);

				pPeripheral->connectAsync();
			}
			catch (Poco::Exception& exc)
			{
				_pContext->logger().error("Cannot create peripheral object for device %s: %s"s, address, exc.displayText());
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

		for (std::vector<PeripheralInfo>::iterator it = _peripherals.begin(); it != _peripherals.end(); ++it)
		{
			try
			{
				it->pPeripheral->connected -= Poco::delegate(this, &BundleActivator::onConnected);
				it->pPeripheral->disconnected -= Poco::delegate(this, &BundleActivator::onDisconnected);
				it->pPeripheral->disconnect();
			}
			catch (Poco::Exception& exc)
			{
				_pContext->logger().warning("Error disconnecting peripheral %s"s, it->pPeripheral->address());
			}
		}

		_peripherals.clear();

		_pPrefs = 0;
		_pContext = 0;
	}

protected:
	class ReconnectTask: public Poco::Util::TimerTask
	{
	public:
		ReconnectTask(BundleActivator& activator, BtLE::Peripheral::Ptr pPeripheral):
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
		BtLE::Peripheral::Ptr _pPeripheral;
	};

	void onConnected(const void* pSender)
	{
		for (std::vector<PeripheralInfo>::iterator it = _peripherals.begin(); it != _peripherals.end(); ++it)
		{
			if (it->pPeripheral.get() == pSender)
			{
				_pContext->logger().information("Peripheral connected: %s"s, it->pPeripheral->address());
				try
				{
					_pContext->logger().debug("Device Name: %s"s, it->pPeripheral->deviceName());
					std::string modelNumber = it->pPeripheral->modelNumber();
					_pContext->logger().debug("Manufacturer Name: %s"s, it->pPeripheral->manufacturerName());
					_pContext->logger().debug("Model Number: %s"s, modelNumber);
					SensorTagType type = sensorTagType(modelNumber, it->type);
					_pContext->logger().debug("SensorTag Type: %d"s, static_cast<int>(type));
					if (!it->haveSensors)
					{
						createSensors(it->pPeripheral, type, it->baseKey);
						it->haveSensors = true;
					}
					it->reconnectDelay = MIN_RECONNECT_DELAY;
				}
				catch (Poco::Exception& exc)
				{
					_pContext->logger().error("Failed to create sensors for device %s: %s"s, it->pPeripheral->address(), exc.displayText());
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
				_pContext->logger().information("Peripheral disconnected: %s"s, it->pPeripheral->address());

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

	void connect(BtLE::Peripheral::Ptr pPeripheral)
	{
		try
		{
			pPeripheral->connectAsync();
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error("Cannot reconnect to device %s: %s"s, pPeripheral->address(), exc.displayText());
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
		BtLE::Peripheral::Ptr pPeripheral;
		std::string type;
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


} } // namespace IoT::SensorTag


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::SensorTag::BundleActivator)
POCO_END_MANIFEST
