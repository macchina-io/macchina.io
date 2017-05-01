//
// SwitchRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SwitchRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SwitchRemoteObject_INCLUDED
#define IoT_Devices_SwitchRemoteObject_INCLUDED


#include "IoT/Devices/ISwitch.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class SwitchRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::ISwitch
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
	typedef Poco::AutoPtr<SwitchRemoteObject> Ptr;

	SwitchRemoteObject();
		/// Creates a SwitchRemoteObject.

	virtual ~SwitchRemoteObject();
		/// Destroys the SwitchRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& SwitchRemoteObject::remoting__typeId() const
{
	return ISwitch::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SwitchRemoteObject_INCLUDED

