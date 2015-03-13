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
	double course;             /// course in degrees [0, 360)
	double speed;              /// speed in nautical knots
	double magneticVariation;  /// magnetic variation in degrees [0, 360)
	Poco::Timestamp timestamp; /// timestamp of position update
};


//@ remote
class IoTDevices_API GNSSSensor: public Device
	/// The interface for GNSS/GPS receivers.
	///
	/// Implementations of this class should also support the
	/// following (optional) properties for configuration:
	///
	///   - positionChangedPeriod (int): the minimum time interval
	///     in milliseconds between firings of the positionUpdate event.
	///   - positionChangedDelta (int): the minimum distance (in meters)
	///     the receiver must move before the positionUpdate event
	///     is fired again.
	///   - positionTimeout (int): Timeout in milliseconds after which the
	///     positionLost event is fired if no valid position has been
	///     received from the GNSS receiver.
{
public:
	Poco::BasicEvent<const PositionUpdate> positionUpdate;
		/// Fired when a position update (e.g., a valid NMEA 0183 RMC message)
		/// has been received from the receiver.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.

	Poco::BasicEvent<void> positionLost;
		/// Fired when the GNSS receiver no longer provides position
		/// updates or has otherwise indicated that it is no longer
		/// able to determine the position.
		
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
		
	virtual double course() const = 0;
		/// Returns the current course in degrees [0, 360).
		
	virtual double speed() const = 0;
		/// Returns the current speed in nautical knots.
		/// If no speed is available, returns -1.
		
	virtual double magneticVariation() const = 0;
		/// Returns the current magnetic variation in degrees [0, 360).
		/// Returns -1 if no magnetic variation is available.
		
	virtual double altitude() const = 0;
		/// Returns the current altitude above sea level in meters.
		/// Returns -9999 if no altitude is available.
		
	virtual double hdop() const = 0;
		/// Returns the Horizontal Dilution Of Precision (HDOP) in meters,
		/// or -9999 if no HDOP value is available.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_GNSSSensor_INCLUDED
