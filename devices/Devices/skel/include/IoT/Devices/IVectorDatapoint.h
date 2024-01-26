//
// IVectorDatapoint.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IVectorDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_IVectorDatapoint_INCLUDED
#define IoT_Devices_IVectorDatapoint_INCLUDED


#include "IoT/Devices/IDatapoint.h"
#include "IoT/Devices/VectorDatapoint.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IVectorDatapoint: public IoT::Devices::IDatapoint
	/// The base class for datapoints holding a vector value.
	///
	/// In addition to the methods defined in this interface,
	/// a VectorDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Ptr = Poco::AutoPtr<IVectorDatapoint>;

	IVectorDatapoint();
		/// Creates a IVectorDatapoint.

	virtual ~IVectorDatapoint();
		/// Destroys the IVectorDatapoint.

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

	virtual void update(const std::vector < double >& value) = 0;
		/// Updates the value of the datapoint and makes it valid.
		///
		/// Not all Datapoint implementations may support
		/// this method.

	virtual Poco::Optional < std::vector < double > > validValue() const = 0;
		/// Returns the current value of the datapoint if
		/// it is valid, otherwise an empty value.

	virtual std::vector < double > value() const = 0;
		/// Returns the current value of the datapoint,
		/// even if it has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	Poco::BasicEvent < const std::vector < double > > validated;
	Poco::BasicEvent < const std::vector < double > > valueChanged;
	Poco::BasicEvent < const std::vector < double > > valueUpdated;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IVectorDatapoint_INCLUDED

