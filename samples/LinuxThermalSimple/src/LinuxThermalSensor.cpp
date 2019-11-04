//
// LinuxThermalSensor.cpp
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "LinuxThermalSensor.h"
#include "Poco/NumberFormatter.h"
#include "Poco/FileStream.h"


namespace IoT {
namespace LinuxThermalSimple {


const std::string LinuxThermalSensor::NAME("Linux Thermal Sensor");
const std::string LinuxThermalSensor::TYPE("io.macchina.sensor");
const std::string LinuxThermalSensor::SYMBOLIC_NAME("io.macchina.linux-thermal-simple");
const std::string LinuxThermalSensor::PHYSICAL_QUANTITY("temperature");


LinuxThermalSensor::LinuxThermalSensor(const std::string& path):
	_path(path + "/temp")
{
	addProperty("displayValue", &LinuxThermalSensor::getDisplayValue);
	addProperty("symbolicName", &LinuxThermalSensor::getSymbolicName);
	addProperty("name", &LinuxThermalSensor::getName);
	addProperty("type", &LinuxThermalSensor::getType);
	addProperty("physicalQuantity", &LinuxThermalSensor::getPhysicalQuantity);
	addProperty("physicalUnit", &LinuxThermalSensor::getPhysicalUnit);
}


double LinuxThermalSensor::value() const
{
	Poco::FileInputStream istr(_path);
	int value;
	istr >> value;
	return value/1000.0;
}


bool LinuxThermalSensor::ready() const
{
	// Keep it simple, always return true.
	return true;
}


Poco::Any LinuxThermalSensor::getDisplayValue(const std::string&) const
{
	return Poco::NumberFormatter::format(value(), 0, 2);
}


Poco::Any LinuxThermalSensor::getName(const std::string&) const
{
	return NAME;
}


Poco::Any LinuxThermalSensor::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any LinuxThermalSensor::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any LinuxThermalSensor::getPhysicalQuantity(const std::string&) const
{
	return PHYSICAL_QUANTITY;
}


Poco::Any LinuxThermalSensor::getPhysicalUnit(const std::string&) const
{
	return IoT::Devices::Sensor::PHYSICAL_UNIT_DEGREES_CELSIUS;
}


} } // namespace IoT::LinuxThermalSimple
