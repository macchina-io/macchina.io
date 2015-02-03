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
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Sensor_INCLUDED
