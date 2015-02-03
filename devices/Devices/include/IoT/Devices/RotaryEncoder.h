//
// RotaryEncoder.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/RotaryEncoder.h#2 $
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


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API RotaryEncoder: public Device
	/// A rotary encoder with an optional push button.
{
public:
	Poco::BasicEvent<const Poco::Int32> countChanged;
		/// Fired when the counter of the encoder has changed.
		
	Poco::BasicEvent<const bool> buttonStateChanged;
		/// Fired when the button has been pressed or released.
		
	RotaryEncoder();
		/// Creates the RotaryEncoder.
		
	~RotaryEncoder();
		/// Destroys the RotaryEncoder.

	virtual Poco::Int32 count() const = 0;
		/// Returns the current value of the counter.
		
	virtual Poco::Int32 reset() = 0;
		/// Returns the current value of the counter and
		/// sets the counter to 0.
		
	virtual bool buttonState() const = 0;
		/// Returns the current state of the button.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_RotaryEncoder_INCLUDED
