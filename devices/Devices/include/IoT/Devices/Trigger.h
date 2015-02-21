//
// Trigger.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/Trigger.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  Trigger
//
// Definition of the Trigger interface.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Trigger_INCLUDED
#define IoT_Devices_Trigger_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API Trigger: public Device
	/// The base class for triggers, such as
	/// push buttons or motion detectors.
	///
	/// In addition to the methods defined in this interface,
	/// a Trigger implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the trigger,
	///     formatted as string for display purposes.
{
public:
	Poco::BasicEvent<const bool> stateChanged;
		/// Fired when the state of the trigger has changed.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.
		
	Trigger();
		/// Creates the Trigger.
		
	~Trigger();
		/// Destroys the Trigger.

	virtual bool state() const = 0;
		/// Returns the current state of the trigger.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Trigger_INCLUDED
