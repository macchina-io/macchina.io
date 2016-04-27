//
// ISwitch.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ISwitch
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_ISwitch_INCLUDED
#define IoT_Devices_ISwitch_INCLUDED


#include "IoT/Devices/IDevice.h"
#include "IoT/Devices/Switch.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class ISwitch: public IoT::Devices::IDevice
	/// The base class for switchable things (that can
	/// be turned on and off).
	///
	/// A Switch has a current state and a target state.
	/// Depending upon the implementation, the current state
	/// and target state may be different for a short amount
	/// of time (e.g., while the device is powering on).
	///
	/// In addition to the methods defined in this interface,
	/// a Switch implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the Switch,
	///     formatted as string for display purposes.
{
public:
	typedef Poco::AutoPtr<ISwitch> Ptr;

	ISwitch();
		/// Creates a ISwitch.

	virtual ~ISwitch();
		/// Destroys the ISwitch.

	virtual bool getTargetState() const = 0;
		/// Returns the target state of the Switch.

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

	virtual void setTargetState(bool newState) = 0;
		/// Sets the target state of the Switch.

	virtual bool state() const = 0;
		/// Returns the current state of the Switch.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const bool > stateChanged;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_ISwitch_INCLUDED

