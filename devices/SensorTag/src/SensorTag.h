//
// SensorTag.h
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_SensorTag_SensorTag_INCLUDED
#define IoT_SensorTag_SensorTag_INCLUDED


#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "IoT/BtLE/Peripheral.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace SensorTag {


class SensorTagSensor: public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, SensorTagSensor>
{
public:
	using Ptr = Poco::SharedPtr<SensorTagSensor>;

	struct Params
	{
		std::string serviceUUID;
		std::string controlUUID;
		std::string dataUUID;
		std::string physicalQuantity;
		std::string physicalUnit;
		long pollInterval;
	};

	SensorTagSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates a SensorTagSensor.

	~SensorTagSensor();
		/// Destroys the SensorTagSensor.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	// Sensor
	double value() const;
	bool ready() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	void init();
	void startPolling();
	void stopPolling();
	void enable(bool enabled);
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getConnected(const std::string&) const;
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getPhysicalQuantity(const std::string&) const;
	Poco::Any getPhysicalUnit(const std::string&) const;
	void update(double value);
	virtual void poll() = 0;
	void onConnected();
	void onDisconnected();

protected:
	Params _params;
	mutable BtLE::Peripheral::Ptr _pPeripheral;
	Poco::SharedPtr<Poco::Util::Timer> _pTimer;
	Poco::Util::TimerTask::Ptr _pPollTask;
	BtLE::Characteristic _controlChar;
	BtLE::Characteristic _dataChar;
	bool _ready;
	bool _enabled;
	double _value;
	double _valueChangedDelta;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<double>> _pEventPolicy;
	Poco::Any _deviceIdentifier;
	Poco::Any _physicalQuantity;
	Poco::Any _physicalUnit;

	friend class PollTask;
};


class SensorTag1IRAmbientTemperatureSensor: public SensorTagSensor
{
public:
	SensorTag1IRAmbientTemperatureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTag1IRAmbientTemperatureSensor.

	~SensorTag1IRAmbientTemperatureSensor();
		/// Destroys the SensorTag1IRAmbientTemperatureSensor.

protected:
	void poll();
};


class SensorTag1IRObjectTemperatureSensor: public SensorTagSensor
{
public:
	SensorTag1IRObjectTemperatureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTag1IRObjectTemperatureSensor.

	~SensorTag1IRObjectTemperatureSensor();
		/// Destroys the SensorTag1IRObjectTemperatureSensor.

protected:
	void poll();
};


class SensorTag2IRAmbientTemperatureSensor: public SensorTagSensor
{
public:
	SensorTag2IRAmbientTemperatureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTag2IRAmbientTemperatureSensor.

	~SensorTag2IRAmbientTemperatureSensor();
		/// Destroys the SensorTag2IRAmbientTemperatureSensor.

protected:
	void poll();
};


class SensorTag2IRObjectTemperatureSensor: public SensorTagSensor
{
public:
	SensorTag2IRObjectTemperatureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTag2IRObjectTemperatureSensor.

	~SensorTag2IRObjectTemperatureSensor();
		/// Destroys the SensorTag2IRObjectTemperatureSensor.

protected:
	void poll();
};


class SensorTagHumiditySensor: public SensorTagSensor
{
public:
	SensorTagHumiditySensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagHumiditySensor.

	~SensorTagHumiditySensor();
		/// Destroys the SensorTagHumiditySensor.

protected:
	void poll();
};


class SensorTag2LightSensor: public SensorTagSensor
{
public:
	SensorTag2LightSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTag2LightSensor.

	~SensorTag2LightSensor();
		/// Destroys the SensorTag2LightSensor.

protected:
	void poll();
};


class SensorTag1AirPressureSensor: public SensorTagSensor
{
public:
	SensorTag1AirPressureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTag1AirPressureSensor.

	~SensorTag1AirPressureSensor();
		/// Destroys the SensorTag1AirPressureSensor.

protected:
	void poll();

private:
	Poco::UInt16 _calCoeff[8];
};


class SensorTag2AirPressureSensor: public SensorTagSensor
{
public:
	SensorTag2AirPressureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTag2AirPressureSensor.

	~SensorTag2AirPressureSensor();
		/// Destroys the SensorTag2AirPressureSensor.

protected:
	void poll();
};


} } // namespace IoT::SensorTag


#endif // IoT_SensorTag_SensorTag_INCLUDED
