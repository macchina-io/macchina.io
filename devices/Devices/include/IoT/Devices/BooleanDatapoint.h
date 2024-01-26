//
// BooleanDatapoint.h
//
// Library: IoT/Devices
// Package: Datapoints
// Module:  BooleanDatapoint
//
// Definition of the BooleanDatapoint interface.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_BooleanDatapoint_INCLUDED
#define IoT_Devices_BooleanDatapoint_INCLUDED


#include "IoT/Devices/Datapoint.h"
#include "Poco/BasicEvent.h"
#include "Poco/Optional.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API BooleanDatapoint: public Datapoint
	/// The base class for datapoints holding a boolean value.
	///
	/// In addition to the methods defined in this interface,
	/// a BooleanDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	Poco::BasicEvent<const bool> valueChanged;
		/// Fired when the value of the datapoint has changed.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.

	Poco::BasicEvent<const bool> valueUpdated;
		/// Fired when the value of the datapoint has been updated
		/// by calling update(). This event is also fired if
		/// the actual value has not changed.

	Poco::BasicEvent<const bool> validated;
		/// Fired when an invalid datapoint becomes valid again, by
		/// being updated with a new value. The new valud is given
		/// as event argument.

	BooleanDatapoint();
		/// Creates the BooleanDatapoint.

	~BooleanDatapoint();
		/// Destroys the BooleanDatapoint.

	virtual bool value() const = 0;
		/// Returns the current value of the datapoint, 
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	virtual Poco::Optional<bool> validValue() const = 0;
		/// Returns the current value of the datapoint if
		/// it is valid, otherwise an empty value.

	virtual bool update(bool value) = 0;
		/// Updates the value of the datapoint and makes it
		/// valid.
		///
		/// Returns the previous value of the datapoint.
		///
		/// Not all Datapoint implementations may support
		/// this method.

	virtual bool invert() = 0;
		/// Inverts the value of the datapoint.
		///
		/// Returns the previous value of the datapoint.
		///
		/// Not all Datapoint implementations may support
		/// this method.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_BooleanDatapoint_INCLUDED
