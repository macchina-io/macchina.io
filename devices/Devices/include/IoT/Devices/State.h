//
// State.h
//
// Library: IoT/Devices
// Package: Devices
// Module:  State
//
// Definition of the State interface.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_State_INCLUDED
#define IoT_Devices_State_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API State: public Device
	/// A State represents a sensor or device register that reports a state.
	///
	/// States are represented by unsigned int (Poco::UInt32) values.
	///
	/// An actual implementation should define possible states as
	/// an enum, and provide the read-only displayValue property
	/// that returns the current state as a string suitable for display.
{
public:
	typedef Poco::UInt32 StateType;

	Poco::BasicEvent<const State::StateType> stateChanged;
		/// Fired when the state has changed.

	State();
		/// Creates the State.

	~State();
		/// Destroys the State.

	virtual StateType state() const = 0;
		/// Returns the value representing the current state.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_State_INCLUDED
