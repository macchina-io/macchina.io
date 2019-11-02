//
// LinuxThermalSensor.h
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_LinuxThermalSensor_INCLUDED
#define IoT_LinuxThermalSensor_INCLUDED


#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"


namespace IoT {
namespace LinuxThermalSimple {


class LinuxThermalSensor: public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, LinuxThermalSensor>
{
public:
	LinuxThermalSensor(const std::string& devicePath);
		/// Creates a LinuxThermalSensor using the given devicePath, e.g. "/sys/class/thermal/thermal_zone0".

	~LinuxThermalSensor();
		/// Destroys the LinuxThermalSensor.

	// Sensor
	double value() const;
	bool ready() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;
	static const std::string PHYSICAL_QUANTITY;

protected:
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getPhysicalQuantity(const std::string&) const;
	Poco::Any getPhysicalUnit(const std::string&) const;

private:
	std::string _path;
};


} } // namespace IoT::LinuxThermalSimple


#endif // IoT_LinuxThermalSensor_INCLUDED
