//
// GenericSensor.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GenericSensor_INCLUDED
#define IoT_Devices_GenericSensor_INCLUDED


#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "Poco/Util/Timer.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class IoTDevices_API GenericSensor: public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, GenericSensor>
{
public:
	typedef Poco::SharedPtr<GenericSensor> Ptr;

	GenericSensor(const std::string& name, const std::string& symbolicName, const std::string& physicalQuantity, const std::string& physicalUnit, Poco::Util::Timer& timer);
		/// Creates a Sensor.

	~GenericSensor();
		/// Destroys the Sensor.

	void update(double value);
		/// Updates the sensor value.

	void enable(bool enabled);
		/// Enables or disables the sensor.

	// Sensor
	double value() const;
	bool ready() const;

	static const std::string TYPE;

protected:
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getPhysicalQuantity(const std::string&) const;
	Poco::Any getPhysicalUnit(const std::string&) const;

protected:
	std::string _name;
	std::string _symbolicName;
	Poco::Any _physicalQuantity;
	Poco::Any _physicalUnit;
	Poco::Util::Timer& _timer;
	bool _ready;
	bool _enabled;
	double _value;
	double _valueChangedDelta;
	int _valueChangedPeriod;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<double> > _pEventPolicy;
};


} } // namespace IoT::Devices


#endif // IoT_Devices_GenericSensor_INCLUDED
