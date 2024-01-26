//
// Datapoint.h
//
// Library: IoT/Devices
// Package: Datapoints
// Module:  Datapoint
//
// Definition of the Datapoint interface.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_Datapoint_INCLUDED
#define IoT_Devices_Datapoint_INCLUDED


#include "IoT/Devices/Device.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API Datapoint: public Device
	/// The base class for datapoints.
	/// Datapoints typically represent the result of
	/// sensor measurements, or data obtained from monitoring
	/// processes.
	///
	/// The main difference between a Datapoint and a Sensor is
	/// that a Sensor is typically an interface to a specific
	/// device (i.e., a temperature sensor), whereas a Datapoint 
	/// holds a value that has been acquired from another
	/// device (via a network or bus system) or computed
	/// from other data points.
	///
	/// In addition to the methods defined in this interface,
	/// a Sensor implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
	///   - updated (timestamp, optional): The point in time when the
	///     datapoint's value was last updated.
	///   - access (string, optional): Access permissions ("rw" - read/write,
	///     "ro" - read-only, "wo" - write-only).
	///
	/// Subclasses of Datapoint implement specific value types.
{
public:
	Datapoint();
		/// Creates the Datapoint.

	~Datapoint();
		/// Destroys the Datapoint.

	Poco::BasicEvent<void> invalidated;
		/// Fired when the datapoint has been invalidated.

	virtual void invalidate() = 0;
		/// Invalidates the datapoint's value.
		///
		/// Subsequent calls to valid() will return false,
		/// until a new value has been set.

	virtual bool valid() const = 0;
		/// Returns true if a valid value is available.
		///
		/// Note that between the time valid() is called and
		/// a subsequent call to value() or similar method, the
		/// validity may change. Use validValue() or similar methods
		/// of subclasses to atomically get validity and value.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Datapoint_INCLUDED
