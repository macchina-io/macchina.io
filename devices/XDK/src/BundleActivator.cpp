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
#include "IoT/Devices/GyroscopeServerHelper.h"
#include "IoT/Devices/MagnetometerServerHelper.h"
#include "IoT/Devices/TriggerServerHelper.h"
#include "IoT/BtLE/BlueZGATTClient.h"
#include "IoT/BtLE/PeripheralImpl.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include "Poco/String.h"
#include "Poco/StringTokenizer.h"
#include "Poco/BinaryReader.h"
#include "XDKSensor.h"
#include "HighRateSensor.h"
#include "HighRateAccelerometer.h"
#include "HighRateGyroscope.h"
#include "HighRateMagnetometer.h"
#include "HighRateButton.h"
#include <vector>


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

	void handleHighPrioData(const std::string& data)
	{
		if (data.size() >= 12)
		{
			Poco::MemoryInputStream istr(data.data(), data.size());
			Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
			Poco::Int16 x, y, z;
			reader >> x >> y >> z;
			IoT::Devices::Acceleration acc;
			acc.x = x/1000.0;
			acc.y = y/1000.0;
			acc.z = z/1000.0;	
			_pAccelerometer->update(acc);

			reader >> x >> y >> z;
			IoT::Devices::Rotation rot;
			rot.x = x/1000.0;
			rot.y = y/1000.0;
			rot.z = z/1000.0;	
			_pGyroscope->update(rot);
		}
	}
	
	void handleLowPrioData(const std::string& data)
	{
		if (data.size() == 20)
		{
			Poco::MemoryInputStream istr(data.data(), data.size());
			Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
			Poco::UInt8 messageId;
			reader >> messageId;
			if (messageId == 0x01)
			{
				Poco::UInt32 light;
				reader >> light;
				_pAmbientLightSensor->update(light/10000.0);
				
				Poco::UInt8 noise;
				reader >> noise;
				_pNoiseSensor->update(noise*1.0);
				
				Poco::UInt32 pressure;
				reader >> pressure;
				_pAirPressureSensor->update(pressure/100.0);
				
				Poco::Int32 temperature;
				reader >> temperature;
				_pTemperatureSensor->update(temperature/1000.0);
				
				Poco::UInt32 humidity;
				reader >> humidity;
				_pHumiditySensor->update(humidity*1.0);
				
				Poco::UInt8 cardDetect;
				reader >> cardDetect;
				
				Poco::UInt8 buttons;
				reader >> buttons;
				_pButton1->update((buttons & 0x01) != 0);
				_pButton2->update((buttons & 0x02) != 0);
			}
			else if (messageId == 0x02)
			{
				Poco::Int16 x, y, z, r;
				reader >> x >> y >> z >> r;
				IoT::Devices::MagneticFieldStrength field;
				field.x = x/1000.0; // millitesla
				field.y = y/1000.0;
				field.z = z/1000.0;	
				field.r = r/1000.0;
				_pMagnetometer->update(field);
			}
		}
	}
	
	void handleHighRateNotification(const void* sender, const IoT::BtLE::GATTClient::Notification& nf)
	{
		if (nf.handle == 0x34)
		{
			handleHighPrioData(nf.data);
		}
		else if (nf.handle == 0x36)
		{
			handleLowPrioData(nf.data);
		}
	}
	
	Poco::SharedPtr<HighRateSensor> createHighRateSensor(Peripheral::Ptr pPeripheral, const HighRateSensor::Params& params)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Sensor> ServerHelper;

		Poco::SharedPtr<HighRateSensor> pSensor = new HighRateSensor(pPeripheral, params);

		std::string oid(HighRateSensor::SYMBOLIC_NAME);
		oid += ".";
		oid += params.physicalQuantity;
		oid += '#';
		oid += pPeripheral->address();

		ServerHelper::RemoteObjectPtr pSensorRemoteObject = ServerHelper::createRemoteObject(pSensor, oid);
		
		Properties props;
		props.set("io.macchina.device", HighRateSensor::SYMBOLIC_NAME);
		props.set("io.macchina.physicalQuantity", params.physicalQuantity);
		props.set("io.macchina.btle.address", pPeripheral->address());
		
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pSensorRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
		
		return pSensor;
	}

	Poco::SharedPtr<HighRateAccelerometer> createHighRateAccelerometer(Peripheral::Ptr pPeripheral)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Accelerometer> ServerHelper;
		Poco::SharedPtr<HighRateAccelerometer> pAccelerometer = new HighRateAccelerometer(pPeripheral);
		std::string oid(HighRateAccelerometer::SYMBOLIC_NAME);
		oid += '#';
		oid += pPeripheral->address();
		ServerHelper::RemoteObjectPtr pAccelerometerRemoteObject = ServerHelper::createRemoteObject(pAccelerometer, oid);
		Properties props;
		props.set("io.macchina.device", HighRateAccelerometer::SYMBOLIC_NAME);
		props.set("io.macchina.btle.address", pPeripheral->address());
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pAccelerometerRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
		return pAccelerometer;
	}

	Poco::SharedPtr<HighRateGyroscope> createHighRateGyroscope(Peripheral::Ptr pPeripheral)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Gyroscope> ServerHelper;
		Poco::SharedPtr<HighRateGyroscope> pGyroscope = new HighRateGyroscope(pPeripheral);
		std::string oid(HighRateGyroscope::SYMBOLIC_NAME);
		oid += '#';
		oid += pPeripheral->address();
		ServerHelper::RemoteObjectPtr pGyroscopeRemoteObject = ServerHelper::createRemoteObject(pGyroscope, oid);
		Properties props;
		props.set("io.macchina.device", HighRateGyroscope::SYMBOLIC_NAME);
		props.set("io.macchina.btle.address", pPeripheral->address());
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pGyroscopeRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
		return pGyroscope;
	}
	
	Poco::SharedPtr<HighRateMagnetometer> createHighRateMagnetometer(Peripheral::Ptr pPeripheral)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Magnetometer> ServerHelper;
		Poco::SharedPtr<HighRateMagnetometer> pMagnetometer = new HighRateMagnetometer(pPeripheral);
		std::string oid(HighRateMagnetometer::SYMBOLIC_NAME);
		oid += '#';
		oid += pPeripheral->address();
		ServerHelper::RemoteObjectPtr pMagnetometerRemoteObject = ServerHelper::createRemoteObject(pMagnetometer, oid);
		Properties props;
		props.set("io.macchina.device", HighRateMagnetometer::SYMBOLIC_NAME);
		props.set("io.macchina.btle.address", pPeripheral->address());
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pMagnetometerRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
		return pMagnetometer;
	}

	Poco::SharedPtr<HighRateButton> createHighRateButton(Peripheral::Ptr pPeripheral, int id)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Trigger> ServerHelper;
		Poco::SharedPtr<HighRateButton> pButton = new HighRateButton(pPeripheral);
		std::string oid(Poco::format("%s%d#%s", HighRateButton::SYMBOLIC_NAME, id, pPeripheral->address()));
		ServerHelper::RemoteObjectPtr pButtonRemoteObject = ServerHelper::createRemoteObject(pButton, oid);
		Properties props;
		props.set("io.macchina.device", HighRateButton::SYMBOLIC_NAME);
		props.set("io.macchina.btle.address", pPeripheral->address());
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pButtonRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
		return pButton;
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

	void createHighRateSensors(Peripheral::Ptr pPeripheral, const std::string& baseKey)
	{
		HighRateSensor::Params params;

		// humidity
		params.physicalQuantity = "humidity";
		params.physicalUnit = "%RH";

		try
		{
			_pHumiditySensor = createHighRateSensor(pPeripheral, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK %s Sensor: %s", params.physicalQuantity, exc.displayText())); 
		}

		// temperature
		params.physicalQuantity = "temperature";
		params.physicalUnit = IoT::Devices::Sensor::PHYSICAL_UNIT_DEGREES_CELSIUS;
		
		try
		{
			_pTemperatureSensor = createHighRateSensor(pPeripheral, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK %s Sensor: %s", params.physicalQuantity, exc.displayText())); 
		}

		// air pressure
		params.physicalQuantity = "airPressure";
		params.physicalUnit = "hPa";
		
		try
		{
			_pAirPressureSensor = createHighRateSensor(pPeripheral, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK %s Sensor: %s", params.physicalQuantity, exc.displayText())); 
		}

		// illuminance
		params.physicalQuantity = "illuminance";
		params.physicalUnit = IoT::Devices::Sensor::PHYSICAL_UNIT_LUX;
		
		try
		{
			_pAmbientLightSensor = createHighRateSensor(pPeripheral, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK %s Sensor: %s", params.physicalQuantity, exc.displayText())); 
		}

		// noise
		params.physicalQuantity = "soundLevel";
		params.physicalUnit = "dB SPL";
		
		try
		{
			_pNoiseSensor = createHighRateSensor(pPeripheral, params);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK %s Sensor: %s", params.physicalQuantity, exc.displayText())); 
		}
		
		// acceleration
		try
		{
			_pAccelerometer = createHighRateAccelerometer(pPeripheral);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK Accelerometer: %s", exc.displayText()));
		}

		// rotation
		try
		{
			_pGyroscope = createHighRateGyroscope(pPeripheral);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK Gyroscope: %s", exc.displayText()));
		}

		// magnetic field
		try
		{
			_pMagnetometer = createHighRateMagnetometer(pPeripheral);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK Magnetometer: %s", exc.displayText()));
		}

		// buttons
		try
		{
			_pButton1 = createHighRateButton(pPeripheral, 1);
			_pButton2 = createHighRateButton(pPeripheral, 2);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error(Poco::format("Cannot create XDK Button: %s", exc.displayText()));
		}

		pPeripheral->notificationReceived += Poco::delegate(this, &BundleActivator::handleHighRateNotification);
	}
	
	void enableHighRateSensors(Peripheral::Ptr pPeripheral)
	{
		pPeripheral->services();
		// turn off built-in sensor fusion - send raw accelerometer data
		Characteristic fusionChar = pPeripheral->characteristic("55b741d0-7ada-11e4-82f8-0800200c9a66", "55b741d5-7ada-11e4-82f8-0800200c9a66");
		pPeripheral->writeUInt8(fusionChar.valueHandle, 0, true);
		// turn on high-rate data
		Characteristic controlChar = pPeripheral->characteristic("55b741d0-7ada-11e4-82f8-0800200c9a66", "55b741d1-7ada-11e4-82f8-0800200c9a66");
		pPeripheral->writeUInt8(controlChar.valueHandle, 1, true);
	}

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
		params.physicalQuantity = "temperature";
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
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		_pTimer = new Poco::Util::Timer;
	
		_useHighRateService = _pPrefs->configuration()->getBool("xdk.useHighRateDataService", true);

		Poco::Util::AbstractConfiguration::Keys keys;
		std::string helperPath = _pPrefs->configuration()->getString("btle.bluez.helper");
		_pPrefs->configuration()->keys("xdk.sensors", keys);
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "xdk.sensors.";
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
		for (std::vector<PeripheralInfo>::iterator it = _peripherals.begin(); it != _peripherals.end(); ++it)
		{
			// unsub and turn off high-rate data
			try
			{
				it->pPeripheral->connected -= Poco::delegate(this, &BundleActivator::onConnected);
				it->pPeripheral->disconnected -= Poco::delegate(this, &BundleActivator::onDisconnected);

				if (it->pPeripheral->isConnected())
				{
					Characteristic controlChar = it->pPeripheral->characteristic("55b741d0-7ada-11e4-82f8-0800200c9a66", "55b741d1-7ada-11e4-82f8-0800200c9a66");
					it->pPeripheral->writeUInt8(controlChar.valueHandle, 0, true);
				}
			}
			catch (Poco::Exception& exc)
			{
				_pContext->logger().warning("Error while turning off high-rate data for device %s: %s", it->pPeripheral->address(), exc.displayText());
			}
		}

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
				it->pPeripheral->disconnect();
			}
			catch (Poco::Exception& exc)
			{
				_pContext->logger().warning("Error while disconnecting from device %s: %s", it->pPeripheral->address(), exc.displayText());
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
					if (!it->haveSensors)
					{
						if (_useHighRateService)
							createHighRateSensors(it->pPeripheral, it->baseKey);
						else
							createSensors(it->pPeripheral, it->baseKey);

						it->haveSensors = true;
					}
					if (_useHighRateService)
					{
						enableHighRateSensors(it->pPeripheral);
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
	bool _useHighRateService;

	Poco::SharedPtr<HighRateSensor> _pHumiditySensor;
	Poco::SharedPtr<HighRateSensor> _pTemperatureSensor;
	Poco::SharedPtr<HighRateSensor> _pAirPressureSensor;
	Poco::SharedPtr<HighRateSensor> _pAmbientLightSensor;
	Poco::SharedPtr<HighRateSensor> _pNoiseSensor;
	Poco::SharedPtr<HighRateAccelerometer> _pAccelerometer;
	Poco::SharedPtr<HighRateGyroscope> _pGyroscope;
	Poco::SharedPtr<HighRateMagnetometer> _pMagnetometer;
	Poco::SharedPtr<HighRateButton> _pButton1;
	Poco::SharedPtr<HighRateButton> _pButton2;
};


} } } // namespace IoT::BtLE::XDK


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::BtLE::XDK::BundleActivator)
POCO_END_MANIFEST
