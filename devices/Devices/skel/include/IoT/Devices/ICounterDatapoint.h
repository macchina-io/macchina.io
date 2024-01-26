//
// ICounterDatapoint.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ICounterDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_ICounterDatapoint_INCLUDED
#define IoT_Devices_ICounterDatapoint_INCLUDED


#include "IoT/Devices/CounterDatapoint.h"
#include "IoT/Devices/IDatapoint.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class ICounterDatapoint: public IoT::Devices::IDatapoint
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
	using Ptr = Poco::AutoPtr<ICounterDatapoint>;

	ICounterDatapoint();
		/// Creates a ICounterDatapoint.

	virtual ~ICounterDatapoint();
		/// Destroys the ICounterDatapoint.

	virtual Poco::Int64 increment(Poco::Int64 delta = Poco::Int64(1)) = 0;
		/// Updates the counter and returns the new value.
		///
		/// Not all CounterDatapoint implementations may support
		/// this method.

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

	virtual Poco::Int64 reset(Poco::Int64 value = Poco::Int64(0)) = 0;
		/// Resets the counter to zero
		/// or the given value and returns the
		/// previous value. Also makes the datapoint valid.
		///
		/// Not all CounterDatapoint implementations may support
		/// this method.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual Poco::Optional < Poco::Int64 > validValue() const = 0;
		/// Returns the current value of the datapoint if it
		/// is valid, otherwise an empty value.

	virtual Poco::Int64 value() const = 0;
		/// Returns the current value of the datapoint, 
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	Poco::BasicEvent < const Poco::Int64 > validated;
	Poco::BasicEvent < const Poco::Int64 > valueChanged;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_ICounterDatapoint_INCLUDED

