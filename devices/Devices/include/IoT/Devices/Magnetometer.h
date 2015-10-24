//
// Magnetometer.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/Sensor.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  Magnetometer
//
// Definition of the GNSSSensor interface.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Magnetometer_INCLUDED
#define IoT_Devices_Magnetometer_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"
#include "Poco/Timestamp.h"


namespace IoT {
namespace Devices {


//@ serialize
struct MagneticFieldStrength
	/// Magnetic field strength values from a three-axis Magnetometer.
{
	double x; 
	double y;
	double z;
};


//@ remote
class IoTDevices_API Magnetometer: public Device
	/// The interface for three-axis Magnetometers.
{
public:
	Poco::BasicEvent<const MagneticFieldStrength> fieldStrengthChanged;
		/// Fired when new magnetic field strength values are available.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.
		
	Magnetometer();
		/// Creates the Magnetometer.
		
	~Magnetometer();
		/// Destroys the Magnetometer.
		
	virtual MagneticFieldStrength fieldStrength() const = 0;
		/// Returns the most recently measured field strength values.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Magnetometer_INCLUDED
