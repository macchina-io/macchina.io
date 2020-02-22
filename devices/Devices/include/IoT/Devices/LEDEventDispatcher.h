//
// LEDEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  LEDEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_LEDEventDispatcher_INCLUDED
#define IoT_Devices_LEDEventDispatcher_INCLUDED


#include "IoT/Devices/LEDRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class LEDEventDispatcher: public Poco::RemotingNG::EventDispatcher
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
	LEDEventDispatcher(LEDRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a LEDEventDispatcher.

	virtual ~LEDEventDispatcher();
		/// Destroys the LEDEventDispatcher.

	void event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data);

	static const std::string DEFAULT_NS;
	LEDRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& LEDEventDispatcher::remoting__typeId() const
{
	return ILED::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_LEDEventDispatcher_INCLUDED

