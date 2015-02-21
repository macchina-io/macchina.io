//
// Sensor.cpp
//
// $Id: //iot/Main/Devices/src/Sensor.cpp#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  Sensor
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/Sensor.h"


namespace IoT {
namespace Devices {


std::string Sensor::PHYSICAL_UNIT_DEGREES_CELSIUS("°C");
std::string Sensor::PHYSICAL_UNIT_DEGREES_FAHRENHEIT("°F");
std::string Sensor::PHYSICAL_UNIT_KELVIN("K");
std::string Sensor::PHYSICAL_UNIT_METER("m");
std::string Sensor::PHYSICAL_UNIT_KILOGRAM("kg");
std::string Sensor::PHYSICAL_UNIT_SECOND("s");
std::string Sensor::PHYSICAL_UNIT_VOLT("V");
std::string Sensor::PHYSICAL_UNIT_AMPERE("A");
std::string Sensor::PHYSICAL_UNIT_MOL("mol");
std::string Sensor::PHYSICAL_UNIT_CANDELA("cd");
std::string Sensor::PHYSICAL_UNIT_LUX("lx");
std::string Sensor::PHYSICAL_UNIT_MBAR("mbar");


Sensor::Sensor()
{
}


Sensor::~Sensor()
{
}


} } // namespace IoT::Devices
