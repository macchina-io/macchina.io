//
// Switch.h
//
// $Id$
//
// Library: IoT/Devices
// Package: Devices
// Module:  Switch
//
// Definition of the Switch interface.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Switch_INCLUDED
#define IoT_Devices_Switch_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API Switch: public Device
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
	Poco::BasicEvent<const bool> stateChanged;
		/// Fired when the state of the Switch has changed.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.
		
	Switch();
		/// Creates the Switch.
		
	~Switch();
		/// Destroys the Switch.

	virtual bool state() const = 0;
		/// Returns the current state of the Switch.

	virtual bool getTargetState() const = 0;
		/// Returns the target state of the Switch.
		
	virtual void setTargetState(bool newState) = 0;
		/// Sets the target state of the Switch.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Switch_INCLUDED
