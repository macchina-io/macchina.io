//
// VectorDatapoint.h
//
// Library: IoT/Devices
// Package: Datapoints
// Module:  VectorDatapoint
//
// Definition of the VectorDatapoint interface.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_VectorDatapoint_INCLUDED
#define IoT_Devices_VectorDatapoint_INCLUDED


#include "IoT/Devices/Datapoint.h"
#include "Poco/BasicEvent.h"
#include "Poco/Optional.h"
#include <vector>


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API VectorDatapoint: public Datapoint
	/// The base class for datapoints holding a vector value.
	///
	/// In addition to the methods defined in this interface,
	/// a VectorDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Vector = std::vector<double>;

	Poco::BasicEvent<const Vector> valueChanged;
		/// Fired when the value of the datapoint has changed.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.

	Poco::BasicEvent<const Vector> valueUpdated;
		/// Fired when the value of the datapoint has been updated
		/// by calling update(). This event is also fired if
		/// the actual value has not changed.

	Poco::BasicEvent<const Vector> validated;
		/// Fired when an invalid datapoint becomes valid again, by
		/// being updated with a new value. The new valud is given
		/// as event argument.

	VectorDatapoint();
		/// Creates the VectorDatapoint.

	~VectorDatapoint();
		/// Destroys the VectorDatapoint.

	virtual Vector value() const = 0;
		/// Returns the current value of the datapoint,
		/// even if it has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	virtual Poco::Optional<Vector> validValue() const = 0;
		/// Returns the current value of the datapoint if
		/// it is valid, otherwise an empty value.

	virtual void update(const Vector& value) = 0;
		/// Updates the value of the datapoint and makes it valid.
		///
		/// Not all Datapoint implementations may support
		/// this method.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_VectorDatapoint_INCLUDED
