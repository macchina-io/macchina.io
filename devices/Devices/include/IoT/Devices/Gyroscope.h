//
// Gyroscope.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/Sensor.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  Gyroscope
//
// Definition of the GNSSSensor interface.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Gyroscope_INCLUDED
#define IoT_Devices_Gyroscope_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"
#include "Poco/Timestamp.h"


namespace IoT {
namespace Devices {


//@ serialize
struct Rotation
	/// Rotation values from a three-axis Gyroscope.
{
	Rotation():
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
class IoTDevices_API Gyroscope: public Device
	/// The interface for three-axis Gyroscopes.
{
public:
	Poco::BasicEvent<const Rotation> rotationChanged;
		/// Fired when new acceleration values are available.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.
		
	Gyroscope();
		/// Creates the Gyroscope.
		
	~Gyroscope();
		/// Destroys the Gyroscope.
		
	virtual Rotation rotation() const = 0;
		/// Returns the most recently measured rotation values.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Gyroscope_INCLUDED
