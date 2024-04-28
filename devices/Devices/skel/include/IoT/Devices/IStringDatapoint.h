//
// IStringDatapoint.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IStringDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_IStringDatapoint_INCLUDED
#define IoT_Devices_IStringDatapoint_INCLUDED


#include "IoT/Devices/IDatapoint.h"
#include "IoT/Devices/StringDatapoint.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IStringDatapoint: public IoT::Devices::IDatapoint
	/// The base class for datapoints holding a string value.
	///
	/// In addition to the methods defined in this interface,
	/// a StringDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Ptr = Poco::AutoPtr<IStringDatapoint>;

	IStringDatapoint();
		/// Creates a IStringDatapoint.

	virtual ~IStringDatapoint();
		/// Destroys the IStringDatapoint.

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

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual void update(const std::string& value) = 0;
		/// Updates the value of the datapoint and makes it valid.
		///
		/// Not all Datapoint implementations may support
		/// this method.

	virtual Poco::Optional<std::string> validValue() const = 0;
		/// Returns the current value of the datapoint if
		/// it is valid, otherwise an empty value.

	virtual std::string value() const = 0;
		/// Returns the current value of the datapoint,
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	Poco::BasicEvent<const std::string> validated;
	Poco::BasicEvent<const std::string> valueChanged;
	Poco::BasicEvent<const std::string> valueUpdated;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IStringDatapoint_INCLUDED

