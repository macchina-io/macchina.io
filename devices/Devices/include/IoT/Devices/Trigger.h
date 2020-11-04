//
// Trigger.h
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
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_Trigger_INCLUDED
#define IoT_Devices_Trigger_INCLUDED


#include "IoT/Devices/BooleanSensor.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API Trigger: public BooleanSensor
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
	Trigger();
		/// Creates the Trigger.

	~Trigger();
		/// Destroys the Trigger.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Trigger_INCLUDED
