//
// RotaryEncoder.h
//
// Library: IoT/Devices
// Package: Devices
// Module:  RotaryEncoder
//
// Definition of the RotaryEncoder interface.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_RotaryEncoder_INCLUDED
#define IoT_Devices_RotaryEncoder_INCLUDED


#include "IoT/Devices/Counter.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API RotaryEncoder: public Counter
	/// A rotary encoder with an optional push button, based
	/// on the Counter interface.
{
public:
	Poco::BasicEvent<const bool> buttonStateChanged;
		/// Fired when the button has been pressed or released.

	RotaryEncoder();
		/// Creates the RotaryEncoder.

	~RotaryEncoder();
		/// Destroys the RotaryEncoder.

	virtual bool buttonState() const = 0;
		/// Returns the current state of the button.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_RotaryEncoder_INCLUDED
