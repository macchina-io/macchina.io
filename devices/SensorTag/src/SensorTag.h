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
		Poco::UUID serviceUUID;
		Poco::UUID controlUUID;
		Poco::UUID dataUUID;
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


class SensorTagCC1352Sensor: public SensorTagSensor
{
public:
	SensorTagCC1352Sensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagCC1352Sensor.

	~SensorTagCC1352Sensor();
		/// Destroys the SensorTagCC1352Sensor.

protected:
	void poll();
};


class SensorTagCC2541AmbientTemperatureSensor: public SensorTagSensor
{
public:
	SensorTagCC2541AmbientTemperatureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagCC2541AmbientTemperatureSensor.

	~SensorTagCC2541AmbientTemperatureSensor();
		/// Destroys the SensorTagCC2541AmbientTemperatureSensor.

protected:
	void poll();
};


class SensorTagCC2541IRObjectTemperatureSensor: public SensorTagSensor
{
public:
	SensorTagCC2541IRObjectTemperatureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagCC2541IRObjectTemperatureSensor.

	~SensorTagCC2541IRObjectTemperatureSensor();
		/// Destroys the SensorTagCC2541IRObjectTemperatureSensor.

protected:
	void poll();
};


class SensorTagCC2650AmbientTemperatureSensor: public SensorTagSensor
{
public:
	SensorTagCC2650AmbientTemperatureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagCC2650AmbientTemperatureSensor.

	~SensorTagCC2650AmbientTemperatureSensor();
		/// Destroys the SensorTagCC2650AmbientTemperatureSensor.

protected:
	void poll();
};


class SensorTagCC2650IRObjectTemperatureSensor: public SensorTagSensor
{
public:
	SensorTagCC2650IRObjectTemperatureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagCC2650IRObjectTemperatureSensor.

	~SensorTagCC2650IRObjectTemperatureSensor();
		/// Destroys the SensorTagCC2650IRObjectTemperatureSensor.

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


class SensorTagCC1352HumiditySensor: public SensorTagSensor
{
public:
	SensorTagCC1352HumiditySensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagCC1352HumiditySensor.

	~SensorTagCC1352HumiditySensor();
		/// Destroys the SensorTagCC1352HumiditySensor.

protected:
	void poll();
};


class SensorTagCC2650LightSensor: public SensorTagSensor
{
public:
	SensorTagCC2650LightSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagCC2650LightSensor.

	~SensorTagCC2650LightSensor();
		/// Destroys the SensorTagCC2650LightSensor.

protected:
	void poll();
};


class SensorTagCC1352LightSensor: public SensorTagSensor
{
public:
	SensorTagCC1352LightSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagCC1352LightSensor.

	~SensorTagCC1352LightSensor();
		/// Destroys the SensorTagCC1352LightSensor.

protected:
	void poll();
};


class SensorTagCC2541AirPressureSensor: public SensorTagSensor
{
public:
	SensorTagCC2541AirPressureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagCC2541AirPressureSensor.

	~SensorTagCC2541AirPressureSensor();
		/// Destroys the SensorTagCC2541AirPressureSensor.

protected:
	void poll();

private:
	Poco::UInt16 _calCoeff[8];
};


class SensorTagCC2650AirPressureSensor: public SensorTagSensor
{
public:
	SensorTagCC2650AirPressureSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagCC2650AirPressureSensor.

	~SensorTagCC2650AirPressureSensor();
		/// Destroys the SensorTagCC2650AirPressureSensor.

protected:
	void poll();
};


} } // namespace IoT::SensorTag


#endif // IoT_SensorTag_SensorTag_INCLUDED
