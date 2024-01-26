//
// EnumDatapoint.h
//
// Library: IoT/Devices
// Package: Datapoints
// Module:  EnumDatapoint
//
// Definition of the EnumDatapoint interface.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_EnumDatapoint_INCLUDED
#define IoT_Devices_EnumDatapoint_INCLUDED


#include "IoT/Devices/Datapoint.h"
#include "Poco/BasicEvent.h"
#include "Poco/Optional.h"
#include <vector>


namespace IoT {
namespace Devices {


//@ serialize
struct EnumValue
{
	int value = 0;
	std::string symbolicName;
};


//@ remote
class IoTDevices_API EnumDatapoint: public Datapoint
	/// The base class for datapoints holding an enumeration
	/// value (based on an int).
	///
	/// An implementation should handle conversion between an
	/// integer value and the corresponding symbolic name.
	///
	/// In addition to the methods defined in this interface,
	/// a EnumDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	Poco::BasicEvent<const int> valueChanged;
		/// Fired when the value of the datapoint has changed.

	Poco::BasicEvent<const int> valueUpdated;
		/// Fired when the value of the datapoint has been updated
		/// by calling update(). This event is also fired if
		/// the actual value has not changed.

	Poco::BasicEvent<const int> validated;
		/// Fired when an invalid datapoint becomes valid again, by
		/// being updated with a new value. The new valud is given
		/// as event argument.

	EnumDatapoint();
		/// Creates the EnumDatapoint.

	~EnumDatapoint();
		/// Destroys the EnumDatapoint.

	virtual int value() const = 0;
		/// Returns the current integer value of the datapoint,
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	virtual Poco::Optional<int> validValue() const = 0;
		/// Returns the current integer value of the datapoint
		/// if it is valid, otherwise an empty value.

	virtual std::string stringValue() const = 0;
		/// Returns the symbolic name corresponding to the datapoint's current value,
		/// even if the datapoint has been invalidated.
		///
		/// Use validStringValue() to get a valid value only.

	virtual Poco::Optional<std::string> validStringValue() const = 0;
		/// Returns the symbolic name corresponding to the datapoint's current value
		/// if the datapoint is valid, otherwise an empty value.

	virtual void update(int value) = 0;
		/// Updates the value of the enumeration.
		///
		/// Throws a Poco::InvalidArgumentException if the given value
		/// is not in the range of defined values.

	virtual void updateString(const std::string& symbolicName) = 0;
		/// Updates the value of the enumeration from
		/// the given symbolic name.
		///
		/// Throws a Poco::InvalidArgumentException if the given symbolicName
		/// is not in the range of defined values and their symbolic names.

	virtual std::vector<EnumValue> definedValues() const = 0;
		/// Returns a vector containing the possible values
		/// and mappings to symbolic names.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_EnumDatapoint_INCLUDED
