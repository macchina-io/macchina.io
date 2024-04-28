//
// IFlagsDatapoint.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IFlagsDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_IFlagsDatapoint_INCLUDED
#define IoT_Devices_IFlagsDatapoint_INCLUDED


#include "IoT/Devices/FlagsDatapoint.h"
#include "IoT/Devices/IDatapoint.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IFlagsDatapoint: public IoT::Devices::IDatapoint
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
	using Ptr = Poco::AutoPtr<IFlagsDatapoint>;

	IFlagsDatapoint();
		/// Creates a IFlagsDatapoint.

	virtual ~IFlagsDatapoint();
		/// Destroys the IFlagsDatapoint.

	virtual std::vector<IoT::Devices::FlagValue> definedFlags() const = 0;
		/// Returns a vector containing the possible flags
		/// and mappings to symbolic names.

	virtual std::vector<std::string> flags() const = 0;
		/// Returns a vector containing the symbolic names
		/// of all flags currently set, even if the datapoint
		/// has been invalidated.
		///
		/// Use validFlags() to get a valid value only.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual std::vector<bool> reset(std::vector<bool> value = std::vector<bool>()) = 0;
		/// Resets all flags to zero or the given value.
		/// Also makes the datapoint valid.
		///
		/// Returns the previously set flags.

	virtual void resetFlags(const std::vector<std::string>& flags = std::vector<std::string>()) = 0;
		/// Resets all flags to the given set of flags and
		/// makes the datapoint valid.

	virtual std::vector<bool> set(std::vector<bool> flags) = 0;
		/// Sets flags by logically OR-ing the currently set flags with the given ones.
		///
		/// Returns the previously set flags.

	virtual void setFlags(const std::vector<std::string>& flags) = 0;
		/// Sets flags by logically OR-ing the currently set flags with the given ones.

	virtual std::vector<bool> toggle(std::vector<bool> flags) = 0;
		/// Sets flags by logically XOR-ing the currently set flags with
		/// the given ones.
		///
		/// Returns the previously set flags.

	virtual void toggleFlags(const std::vector<std::string>& flags) = 0;
		/// Sets flags by logically XOR-ing the currently set flags with
		/// the given ones.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual std::vector<bool> unset(std::vector<bool> flags) = 0;
		/// Unsets flags by logically AND-ing the currently set flags with
		/// the inverted given ones.
		///
		/// Returns the previously set flags.

	virtual void unsetFlags(const std::vector<std::string>& flags) = 0;
		/// Unsets flags by logically AND-ing the currently set flags with
		/// the inverted given ones.

	virtual Poco::Optional<std::vector<std::string>> validFlags() const = 0;
		/// Returns a vector containing the symbolic names
		/// of all flags currently set if the datapoint is valid,
		/// otherwise an empty value.

	virtual Poco::Optional<std::vector<bool>> validValue() const = 0;
		/// Returns the bit vector value of the datapoint if
		/// it is valid, otherwise an empty value.

	virtual std::vector<bool> value() const = 0;
		/// Returns the bit vector value of the datapoint,
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	Poco::BasicEvent<const std::vector<bool>> validated;
	Poco::BasicEvent<const std::vector<bool>> valueChanged;
	Poco::BasicEvent<const std::vector<bool>> valueUpdated;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IFlagsDatapoint_INCLUDED

