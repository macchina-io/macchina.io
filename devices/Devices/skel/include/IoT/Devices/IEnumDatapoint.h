//
// IEnumDatapoint.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IEnumDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_IEnumDatapoint_INCLUDED
#define IoT_Devices_IEnumDatapoint_INCLUDED


#include "IoT/Devices/EnumDatapoint.h"
#include "IoT/Devices/IDatapoint.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IEnumDatapoint: public IoT::Devices::IDatapoint
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
	using Ptr = Poco::AutoPtr<IEnumDatapoint>;

	IEnumDatapoint();
		/// Creates a IEnumDatapoint.

	virtual ~IEnumDatapoint();
		/// Destroys the IEnumDatapoint.

	virtual std::vector < IoT::Devices::EnumValue > definedValues() const = 0;
		/// Returns a vector containing the possible values
		/// and mappings to symbolic names.

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

	virtual std::string stringValue() const = 0;
		/// Returns the symbolic name corresponding to the datapoint's current value,
		/// even if the datapoint has been invalidated.
		///
		/// Use validStringValue() to get a valid value only.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

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

	virtual Poco::Optional < std::string > validStringValue() const = 0;
		/// Returns the symbolic name corresponding to the datapoint's current value
		/// if the datapoint is valid, otherwise an empty value.

	virtual Poco::Optional < int > validValue() const = 0;
		/// Returns the current integer value of the datapoint
		/// if it is valid, otherwise an empty value.

	virtual int value() const = 0;
		/// Returns the current integer value of the datapoint,
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	Poco::BasicEvent < const int > validated;
	Poco::BasicEvent < const int > valueChanged;
	Poco::BasicEvent < const int > valueUpdated;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IEnumDatapoint_INCLUDED

