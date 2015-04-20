//
// ILED.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ILED
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_ILED_INCLUDED
#define IoT_Devices_ILED_INCLUDED


#include "IoT/Devices/IDevice.h"
#include "IoT/Devices/LED.h"


namespace IoT {
namespace Devices {


class ILED: public IoT::Devices::IDevice
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
	typedef Poco::AutoPtr<ILED> Ptr;

	ILED();
		/// Creates a ILED.

	virtual ~ILED();
		/// Destroys the ILED.

	virtual void blink(int onMilliseconds, int offMilliseconds) = 0;
		/// Turns on blinking of the LED.
		///
		/// May not be supported by all implementations.

	virtual double getBrightness() const = 0;
		/// Returns the current brightness of the LED in range 0.0 to 1.0.
		///
		/// 0.0 means off, every value > 0.0 means on, with 1.0 being 
		/// the maximum brightness level.
		///
		/// Note that most LED devices do not support different brightness levels
		/// and can only be turned on or off.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual void off() = 0;
		/// Convenience method that turns the LED off by
		/// calling setBrightness(0.0).

	virtual void on() = 0;
		/// Convenience method that turns the LED on by
		/// calling setBrightness(1.0).

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void setBrightness(double brightness) = 0;
		/// Sets the brightness of the LED.
		///
		/// 0.0 means off, every value > 0.0 means on, with 1.0 being 
		/// the maximum brightness level.
		///
		/// Note that most LED devices do not support different brightness levels
		/// and can only be turned on or off.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_ILED_INCLUDED

