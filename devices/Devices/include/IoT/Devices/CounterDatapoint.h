//
// CounterDatapoint.h
//
// Library: IoT/Devices
// Package: Datapoints
// Module:  CounterDatapoint
//
// Definition of the CounterDatapoint interface.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_CounterDatapoint_INCLUDED
#define IoT_Devices_CounterDatapoint_INCLUDED


#include "IoT/Devices/Datapoint.h"
#include "Poco/BasicEvent.h"
#include "Poco/Optional.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API CounterDatapoint: public Datapoint
	/// The base class for datapoints holding a counter
	/// (a 64-bit unsigned integer).
	///
	/// In addition to the methods defined in this interface,
	/// a CounterDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using CounterType = Poco::Int64;

	Poco::BasicEvent<const CounterType> valueChanged;
		/// Fired when the value of the datapoint has changed.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.

	Poco::BasicEvent<const CounterType> validated;
		/// Fired when an invalid datapoint becomes valid again, by
		/// being updated with a new value. The new valud is given
		/// as event argument.

	CounterDatapoint();
		/// Creates the CounterDatapoint.

	~CounterDatapoint();
		/// Destroys the CounterDatapoint.

	virtual CounterType value() const = 0;
		/// Returns the current value of the datapoint, 
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	virtual Poco::Optional<CounterType> validValue() const = 0;
		/// Returns the current value of the datapoint if it
		/// is valid, otherwise an empty value.

	//@ $delta={optional}
	virtual CounterType increment(CounterType delta = 1) = 0;
		/// Updates the counter and returns the new value.
		///
		/// Not all CounterDatapoint implementations may support
		/// this method.

	//@ $value={optional}
	virtual CounterType reset(CounterType value = 0) = 0;
		/// Resets the counter to zero
		/// or the given value and returns the
		/// previous value. Also makes the datapoint valid.
		///
		/// Not all CounterDatapoint implementations may support
		/// this method.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_CounterDatapoint_INCLUDED
