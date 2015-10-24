//
// IO.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/Sensor.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  IO
//
// Definition of the IO interface.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IO_INCLUDED
#define IoT_Devices_IO_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API IO: public Device
	/// The interface for general purpose input/output (GPIO)
	/// ports.
	///
	/// This class represents a single GPIO pin. 
	/// Mapping to physical pins is configured when setting up 
	/// the specific IO implementation class, typically using a 
	/// configuration file.
	///
	/// Implementations supporting dynamically changing pin directions
	/// should expose a string property named "direction" that takes the
	/// values "in" and "out".
{
public:
	Poco::BasicEvent<const bool> stateChanged;
		/// Fired when the state of the interrupt-capable
		/// input pin has changed.
		///
		/// For this event to be fired, the I/O device must support
		/// interrupt-capable input pins, and those pins must be
		/// configured to trigger interrupts, by an implementation-specific
		/// means.
		///
		/// Only a pin configured as input will trigger the event.
		
	IO();
		/// Creates the IO.
		
	~IO();
		/// Destroys the IO.

	virtual bool state() const = 0;
		/// Returns the current state of the pin.

	virtual void set(bool state) = 0;
		/// Sets the state of an output pin to the given state.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_IO_INCLUDED
