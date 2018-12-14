//
// StateEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  StateEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_StateEventDispatcher_INCLUDED
#define IoT_Devices_StateEventDispatcher_INCLUDED


#include "IoT/Devices/StateRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class StateEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// A State represents a sensor or device register that reports a state.
	///
	/// States are represented by unsigned int (Poco::UInt32) values.
	///
	/// An actual implementation should define possible states as
	/// an enum, and provide the read-only displayValue property
	/// that returns the current state as a string suitable for display.
{
public:
	StateEventDispatcher(StateRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a StateEventDispatcher.

	virtual ~StateEventDispatcher();
		/// Destroys the StateEventDispatcher.

	void event__stateChanged(const void* pSender, const Poco::UInt32& data);

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__stateChangedImpl(const std::string& subscriberURI, const Poco::UInt32& data);

	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	StateRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& StateEventDispatcher::remoting__typeId() const
{
	return IState::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_StateEventDispatcher_INCLUDED

