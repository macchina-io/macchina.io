//
// Accelerometer.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/Sensor.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  Accelerometer
//
// Definition of the GNSSSensor interface.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Accelerometer_INCLUDED
#define IoT_Devices_Accelerometer_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"
#include "Poco/Timestamp.h"


namespace IoT {
namespace Devices {


//@ serialize
struct Acceleration
	/// Acceleration values from a three-axis accelerometer.
{
	Acceleration():
		x(0),
		y(0),
		z(0)
	{
	}

	double x; 
	double y;
	double z;
};


//@ remote
class IoTDevices_API Accelerometer: public Device
	/// The interface for three-axis Accelerometers.
{
public:
	Poco::BasicEvent<const Acceleration> accelerationChanged;
		/// Fired when new acceleration values are available.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.
		
	Accelerometer();
		/// Creates the Accelerometer.
		
	~Accelerometer();
		/// Destroys the Accelerometer.
		
	virtual Acceleration acceleration() const = 0;
		/// Returns the most recently measured acceleration values.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Accelerometer_INCLUDED
