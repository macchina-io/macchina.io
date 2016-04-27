//
// SwitchEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SwitchEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SwitchEventDispatcher_INCLUDED
#define IoT_Devices_SwitchEventDispatcher_INCLUDED


#include "IoT/Devices/SwitchRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class SwitchEventDispatcher: public Poco::RemotingNG::EventDispatcher
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
	SwitchEventDispatcher(SwitchRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a SwitchEventDispatcher.

	virtual ~SwitchEventDispatcher();
		/// Destroys the SwitchEventDispatcher.

	void event__stateChanged(const void* pSender, const bool& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__stateChangedImpl(const std::string& subscriberURI, const bool& data);

	static const std::string DEFAULT_NS;
	SwitchRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SwitchEventDispatcher::remoting__typeId() const
{
	return ISwitch::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SwitchEventDispatcher_INCLUDED

