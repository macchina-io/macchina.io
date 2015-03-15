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
	/// The base class for general purpose input/output (GPIO)
	/// devices.
	///
	/// The IO class supports up to 32 logical pins. Each logical
	/// pin is mapped to a physical pin on the hardware. Logical
	/// pins are counted from 0 to 31. Mapping to physical pins
	/// is configured when setting up the IO implementation class,
	/// typically using a configuration file.
	///
	/// Implementations that support interrupt-capable input pins
	/// should expose an int property named "stateChangedEventMask"
	/// that allows enabling interrupts for specific pins, based
	/// on the given bit mask.
	///
	/// Implementations supporting dynamically changing pin directions
	/// should expose int properties named "configureInputs" and
	/// "configureOutputs" that take a bit mask specifying affected pins.
{
public:
	Poco::BasicEvent<const Poco::UInt32> stateChanged;
		/// Fired when the state of one or more interrupt-capable
		/// input pins has changed.
		///
		/// For this event to be fired, the I/O device must support
		/// interrupt-capable input pins, and those pins must be
		/// configured to trigger interrupts, by setting the
		/// "stateChangedEventMask" property.
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.
		///
		/// Only pins configured as input will trigger the event.
		
	IO();
		/// Creates the IO.
		
	~IO();
		/// Destroys the IO.

	virtual Poco::UInt32 state() const = 0;
		/// Returns the current state of all input and output pins as
		/// a bit mask. 
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.

	virtual void setState(Poco::UInt32 state) = 0;
		/// Sets the state of all output pins according to the given bit mask.
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.
		/// Only pins configured as output will be affected.
	
	virtual void setStateMask(Poco::UInt32 state, Poco::UInt32 mask) = 0;
		/// Sets the state of certain output pins according to the given state bit mask
		/// and logical pin selection bit mask. Only pins whose bit in mask is 1
		/// will be changed.
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.
		/// Only pins configured as output will be affected.

	virtual bool getPinState(int pin) const = 0;
		/// Returns the state of the input or output pin with the given index (0 - 31).
		
	virtual void setPinState(int pin, bool value) = 0;
		/// Sets the state of the output pin with the given index (0 - 31) to
		/// the given value. The pin must be configured as an output pin.
		
	virtual int physicalPin(int pin) const = 0;
		/// Returns the physical pin number the logical pin with the given index
		/// (0 - 31) is mapped to. Mapping of logical to physical pin numbers is
		/// done when setting up the IO object and is specific to the actual
		/// implementation.

	virtual Poco::UInt32 available() const = 0;
		/// Returns a bitmask specifying available I/O ports.
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.

	virtual bool isAvailable(int pin) const = 0;
		/// Returns true if the I/O pin with the given index (0 - 31)
		/// is available.

	virtual Poco::UInt32 inputs() const = 0;
		/// Returns a bitmask specifying available input ports.
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.

	virtual Poco::UInt32 outputs() const = 0;
		/// Returns a bitmask specifying available input ports.
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.
		
	virtual bool isInput(int pin) const = 0;
		/// Returns true if the given pin is configured as input, otherwise false.
		
	virtual bool isOutput(int pin) const = 0;
		/// Returns true if the given pin is configured as output, otherwise false.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_IO_INCLUDED
