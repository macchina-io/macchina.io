//
// GNSSSensor.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/Sensor.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  GNSSSensor
//
// Definition of the GNSSSensor interface.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GNSSSensor_INCLUDED
#define IoT_Devices_GNSSSensor_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"
#include "Poco/Timestamp.h"


namespace IoT {
namespace Devices {


//@ serialize
struct LatLon
	/// LatLon represents a point on the two-dimensional surface of a globe. 
	/// Latitude is the degrees North and ranges between [-90, 90]
	/// while longitude refers to degrees East, and ranges between (-180, 180].
{
	double latitude; 
	double longitude;
};


//@ serialize
struct PositionUpdate
	/// The information contained in a NMEA 0183 RMC message.
{
	LatLon position;           /// position 
	double heading;            /// heading in degrees [0, 360)
	double speed;              /// speed in nautical knots
	double magneticVariation;  /// magnetic variation in degrees [0, 360)
	Poco::Timestamp timestamp; /// timestamp of position update
};


//@ remote
class IoTDevices_API GNSSSensor: public Device
	/// The interface for GNSS/GPS receivers.
{
public:
	Poco::BasicEvent<const PositionUpdate> positionUpdate;
		/// Fired when a position update (e.g., a NMEA 0183 RMC message)
		/// has been received from the receiver.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.
		
	GNSSSensor();
		/// Creates the GNSSSensor.
		
	~GNSSSensor();
		/// Destroys the GNSSSensor.
		
	virtual bool positionAvailable() const = 0;
		/// Returns true if a valid position is available.

	virtual LatLon position() const = 0;
		/// Returns the last obtained position.
		///
		/// If no position is available, latitude and longitude will both be 0.
		/// To disambiguate with a real position, also check positionAvailable().
		
	virtual double heading() const = 0;
		/// Returns the current heading in degrees [0, 360).
		
	virtual double speed() const = 0;
		/// Returns the current speed in nautical knots.
		/// If no speed is available, returns -1.
		
	virtual double magneticVariation() const = 0;
		/// Returns the current magnetic variation in degrees [0, 360).
		/// Returns -1 if no magnetic variation is available.
		
	virtual double altitude() const = 0;
		/// Returns the current altitude above sea level in meters.
		/// Returns -9999 if no altitude is available.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_GNSSSensor_INCLUDED
