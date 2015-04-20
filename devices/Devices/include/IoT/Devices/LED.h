//
// LED.h
//
// $Id$
//
// Library: IoT/Devices
// Package: Devices
// Module:  LED
//
// Definition of the LED interface.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_LED_INCLUDED
#define IoT_Devices_LED_INCLUDED


#include "IoT/Devices/Device.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API LED: public Device
	/// The base class for LEDs.
	///
	/// Each instance of the LED class represents a single physical
	/// LED. Some LED devices support different brightness levels,
	/// this is accounted for by allowing to specify a brightness
	/// level in range 0.0 to 1.0, where 0.0 turns the LED off and
	/// 1.0 is the maximum brightness. 
	///
	/// Some implementations may also support blinking LEDs.
	/// This is exposed via the "blinkOn" and "blinkOff" properties,
	/// which take as values the time in milliseconds the LED should
	/// be on, or off, respectively. There is also a shortcut
	/// method, blink(), which allows setting both properties at once.
	///
	/// To turn on blinking, both "blinkOn" and "blinkOff" must be 
	/// set to a non-zero value. Furthermore, the brightness must
	/// be non-zero.
{
public:		
	LED();
		/// Creates the LED.
		
	~LED();
		/// Destroys the LED.
		
	virtual void on() = 0;
		/// Convenience method that turns the LED on by
		/// calling setBrightness(1.0).
		
	virtual void off() = 0;
		/// Convenience method that turns the LED off by
		/// calling setBrightness(0.0).

	virtual double getBrightness() const = 0;
		/// Returns the current brightness of the LED in range 0.0 to 1.0.
		///
		/// 0.0 means off, every value > 0.0 means on, with 1.0 being 
		/// the maximum brightness level.
		///
		/// Note that most LED devices do not support different brightness levels
		/// and can only be turned on or off.

	virtual void setBrightness(double brightness) = 0;
		/// Sets the brightness of the LED.
		///
		/// 0.0 means off, every value > 0.0 means on, with 1.0 being 
		/// the maximum brightness level.
		///
		/// Note that most LED devices do not support different brightness levels
		/// and can only be turned on or off.
		
	virtual void blink(int onMilliseconds, int offMilliseconds) = 0;
		/// Turns on blinking of the LED.
		///
		/// May not be supported by all implementations.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_LED_INCLUDED
