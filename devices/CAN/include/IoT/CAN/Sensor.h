//
// Sensor.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_CAN_Sensor_INCLUDED
#define IoT_CAN_Sensor_INCLUDED


#include "IoT/CAN/CANDevices.h"
#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "Poco/Util/Timer.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace CAN {


class IoTCANDevices_API Sensor: public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, Sensor>
{
public:
	typedef Poco::SharedPtr<Sensor> Ptr;

	Sensor(Poco::Util::Timer& timer, const std::string& signal, const std::string& physicalQuantity, const std::string& physicalUnit);
		/// Creates a Sensor.

	~Sensor();
		/// Destroys the Sensor.

	void update(double value);
		/// Updates the sensor value.

	void enable(bool enabled);
		/// Enables or disables the sensor.

	// Sensor
	double value() const;
	bool ready() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getSignal(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getPhysicalQuantity(const std::string&) const;
	Poco::Any getPhysicalUnit(const std::string&) const;

protected:
	Poco::Util::Timer& _timer;
	bool _ready;
	bool _enabled;
	double _value;
	double _valueChangedDelta;
	int _valueChangedPeriod;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<double> > _pEventPolicy;
	Poco::Any _signal;
	Poco::Any _physicalQuantity;
	Poco::Any _physicalUnit;
};


} } // namespace IoT::CAN


#endif // IoT_CAN_Sensor_INCLUDED
