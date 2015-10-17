//
// SensorTag.h
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
namespace BtLE {
namespace SensorTag {


class SensorTagSensor: public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, SensorTagSensor>
{
public:
	typedef Poco::SharedPtr<SensorTagSensor> Ptr;

	struct Params
	{
		std::string serviceUUID;
		std::string controlUUID;
		std::string dataUUID;
		std::string physicalQuantity;
		std::string physicalUnit;
		long pollInterval;
	};
	
	SensorTagSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates a SensorTagSensor.

	~SensorTagSensor();
		/// Destroys the SensorTagSensor.
	
	// Sensor
	double value() const;
	bool ready() const;

	static const std::string NAME;
	static const std::string SYMBOLIC_NAME;

protected:
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getPhysicalQuantity(const std::string&) const;
	Poco::Any getPhysicalUnit(const std::string&) const;
	void update(double value);
	virtual void poll() = 0;

protected:
	Params _params;
	Peripheral::Ptr _pPeripheral;
	Poco::SharedPtr<Poco::Util::Timer> _pTimer;
	Poco::Util::TimerTask::Ptr _pPollTask;
	Characteristic _controlChar;
	Characteristic _dataChar;
	bool _ready;
	double _value;
	double _valueChangedDelta;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<double> > _pEventPolicy;
	Poco::Any _deviceIdentifier;
	Poco::Any _symbolicName;
	Poco::Any _name;
	Poco::Any _physicalQuantity;
	Poco::Any _physicalUnit;
	
	friend class PollTask;
};


class SensorTagTemperatureSensor: public SensorTagSensor
{
public:
	SensorTagTemperatureSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagTemperatureSensor.

	~SensorTagTemperatureSensor();
		/// Destroys the SensorTagTemperatureSensor.
		
protected:
	void poll();
};


class SensorTagHumiditySensor: public SensorTagSensor
{
public:
	SensorTagHumiditySensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagTemperatureSensor.

	~SensorTagHumiditySensor();
		/// Destroys the SensorTagTemperatureSensor.
		
protected:
	void poll();
};


class SensorTagLightSensor: public SensorTagSensor
{
public:
	SensorTagLightSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorTagTemperatureSensor.

	~SensorTagLightSensor();
		/// Destroys the SensorTagTemperatureSensor.
		
protected:
	void poll();
};


class SensorTagAirPressureSensor: public SensorTagSensor
{
public:
	SensorTagAirPressureSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates the SensorAirPressureSensor.

	~SensorTagAirPressureSensor();
		/// Destroys the SensorAirPressureSensor.
		
protected:
	void poll();
};


} } } // namespace IoT::BtLE::SensorTag


#endif // IoT_SensorTag_SensorTag_INCLUDED
