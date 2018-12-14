//
// IState.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IState
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IState_INCLUDED
#define IoT_Devices_IState_INCLUDED


#include "IoT/Devices/IDevice.h"
#include "IoT/Devices/State.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IState: public IoT::Devices::IDevice
	/// A State represents a sensor or device register that reports a state.
	///
	/// States are represented by unsigned int (Poco::UInt32) values.
	///
	/// An actual implementation should define possible states as
	/// an enum, and provide the read-only displayValue property
	/// that returns the current state as a string suitable for display.
{
public:
	typedef Poco::AutoPtr<IState> Ptr;

	IState();
		/// Creates a IState.

	virtual ~IState();
		/// Destroys the IState.

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

	virtual Poco::UInt32 state() const = 0;
		/// Returns the value representing the current state.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const State::StateType > stateChanged;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IState_INCLUDED

