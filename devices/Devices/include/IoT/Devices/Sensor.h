//
// Sensor.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/Sensor.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  Sensor
//
// Definition of the Sensor interface.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Sensor_INCLUDED
#define IoT_Devices_Sensor_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API Sensor: public Device
	/// The base class for analog sensors, such as
	/// temperature or ambient light sensors.
	///
	/// In addition to the methods defined in this interface,
	/// a Sensor implementation should expose the following
	/// properties:
	///   - physicalQuantity (string): The physical quantity that is
	///     being measured by the sensor, e.g. "temperature".
	///   - physicalUnit (string): The physical unit the measured value
	///     is being represented in (e.g. "°C"), UTF-8 encoded.
	///     See the PHYSICAL_UNIT_* strings for predefined values.
	///   - displayValue (string, optional): The current value of the sensor,
	///     formatted as string for display purposes.
{
public:
	Poco::BasicEvent<const double> valueChanged;
		/// Fired when the state of the Sensor has changed.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.
		
	Sensor();
		/// Creates the Sensor.
		
	~Sensor();
		/// Destroys the Sensor.

	virtual double value() const = 0;
		/// Returns the current value measured by the sensor.
		///
		/// Some sensors may not be able to immediately report
		/// a valid value. Therefore, before calling value() the first time, ready() 
		/// should be called to check if a valid value is available.
		
	virtual bool ready() const = 0;
		/// Returns true if a valid value is available.
		
	static std::string PHYSICAL_UNIT_DEGREES_CELSIUS;
	static std::string PHYSICAL_UNIT_DEGREES_FAHRENHEIT;
	static std::string PHYSICAL_UNIT_KELVIN;
	static std::string PHYSICAL_UNIT_METER;
	static std::string PHYSICAL_UNIT_KILOGRAM;
	static std::string PHYSICAL_UNIT_SECOND;
	static std::string PHYSICAL_UNIT_VOLT;
	static std::string PHYSICAL_UNIT_AMPERE;
	static std::string PHYSICAL_UNIT_MOL;
	static std::string PHYSICAL_UNIT_CANDELA;
	static std::string PHYSICAL_UNIT_LUX;
	static std::string PHYSICAL_UNIT_MBAR;
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Sensor_INCLUDED
