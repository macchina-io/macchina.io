//
// FlagsDatapoint.h
//
// Library: IoT/Devices
// Package: Datapoints
// Module:  FlagsDatapoint
//
// Definition of the FlagsDatapoint interface.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_FlagsDatapoint_INCLUDED
#define IoT_Devices_FlagsDatapoint_INCLUDED


#include "IoT/Devices/Datapoint.h"
#include "Poco/BasicEvent.h"
#include "Poco/Optional.h"
#include <vector>


namespace IoT {
namespace Devices {


//@ serialize
struct FlagValue
{
	Poco::UInt16 bit = 0; // Bit number
	std::string symbolicName;
};


//@ remote
class IoTDevices_API FlagsDatapoint: public Datapoint
	/// The base class for datapoints holding a variable number of
	/// flag bits, internally stored as a std::vector<bool>.
	///
	/// An implementation should handle conversion between a
	/// flag bit and the corresponding symbolic name of
	/// a flag.
	///
	/// In addition to the methods defined in this interface,
	/// a FlagsDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using FlagsType = std::vector<bool>;

	Poco::BasicEvent<const FlagsType> valueChanged;
		/// Fired when the value of the datapoint has changed.

	Poco::BasicEvent<const FlagsType> valueUpdated;
		/// Fired when the value of the datapoint has been updated
		/// by calling update(). This event is also fired if
		/// the actual value has not changed.

	Poco::BasicEvent<const FlagsType> validated;
		/// Fired when an invalid datapoint becomes valid again, by
		/// being updated with a new value. The new valud is given
		/// as event argument.

	FlagsDatapoint();
		/// Creates the FlagsDatapoint.

	~FlagsDatapoint();
		/// Destroys the FlagsDatapoint.

	virtual FlagsType value() const = 0;
		/// Returns the bit vector value of the datapoint,
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	virtual Poco::Optional<FlagsType> validValue() const = 0;
		/// Returns the bit vector value of the datapoint if
		/// it is valid, otherwise an empty value.

	virtual std::vector<std::string> flags() const = 0;
		/// Returns a vector containing the symbolic names
		/// of all flags currently set, even if the datapoint
		/// has been invalidated.
		///
		/// Use validFlags() to get a valid value only.

	virtual Poco::Optional<std::vector<std::string>> validFlags() const = 0;
		/// Returns a vector containing the symbolic names
		/// of all flags currently set if the datapoint is valid,
		/// otherwise an empty value.

	//@ $value={optional}
	virtual FlagsType reset(FlagsType value = FlagsType()) = 0;
		/// Resets all flags to zero or the given value.
		/// Also makes the datapoint valid.
		///
		/// Returns the previously set flags.

	//@ $flags={optional}
	virtual void resetFlags(const std::vector<std::string>& flags = std::vector<std::string>()) = 0;
		/// Resets all flags to the given set of flags and
		/// makes the datapoint valid.

	virtual FlagsType set(FlagsType flags) = 0;
		/// Sets flags by logically OR-ing the currently set flags with the given ones.
		///
		/// Returns the previously set flags.

	virtual void setFlags(const std::vector<std::string>& flags) = 0;
		/// Sets flags by logically OR-ing the currently set flags with the given ones.

	virtual FlagsType unset(FlagsType flags) = 0;
		/// Unsets flags by logically AND-ing the currently set flags with
		/// the inverted given ones.
		///
		/// Returns the previously set flags.

	virtual void unsetFlags(const std::vector<std::string>& flags) = 0;
		/// Unsets flags by logically AND-ing the currently set flags with
		/// the inverted given ones.

	virtual FlagsType toggle(FlagsType flags) = 0;
		/// Sets flags by logically XOR-ing the currently set flags with
		/// the given ones.
		///
		/// Returns the previously set flags.

	virtual void toggleFlags(const std::vector<std::string>& flags) = 0;
		/// Sets flags by logically XOR-ing the currently set flags with
		/// the given ones.

	virtual std::vector<FlagValue> definedFlags() const = 0;
		/// Returns a vector containing the possible flags
		/// and mappings to symbolic names.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_FlagsDatapoint_INCLUDED
