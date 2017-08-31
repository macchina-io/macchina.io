//
// BooleanSensor.h
//
// $Id$
//
// Library: IoT/Devices
// Package: Devices
// Module:  BooleanSensor
//
// Definition of the BooleanSensor interface.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_BooleanSensor_INCLUDED
#define IoT_Devices_BooleanSensor_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API BooleanSensor: public Device
	/// The base class for two-state sensors measuring
	/// on/off or open/closed state.
	///
	/// In addition to the methods defined in this interface,
	/// a BooleanSensor implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the trigger,
	///     formatted as string for display purposes.
{
public:
	Poco::BasicEvent<const bool> stateChanged;
		/// Fired when the state of the sensor has changed.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.

	BooleanSensor();
		/// Creates the BooleanSensor.

	~BooleanSensor();
		/// Destroys the BooleanSensor.

	virtual bool state() const = 0;
		/// Returns the current state of the trigger.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_BooleanSensor_INCLUDED
