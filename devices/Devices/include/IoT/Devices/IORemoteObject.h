//
// IORemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IORemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IORemoteObject_INCLUDED
#define IoT_Devices_IORemoteObject_INCLUDED


#include "IoT/Devices/IIO.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class IORemoteObject: public IoT::Devices::IIO, public Poco::RemotingNG::RemoteObject
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
	typedef Poco::AutoPtr<IORemoteObject> Ptr;

	IORemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::IO> pServiceObject);
		/// Creates a IORemoteObject.

	virtual ~IORemoteObject();
		/// Destroys the IORemoteObject.

	virtual Poco::UInt32 available() const;
		/// Returns a bitmask specifying available I/O ports.
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.

	virtual bool getFeature(const std::string& name) const;
		/// Returns true if the feature with the given name
		/// is enabled, or false otherwise.

	virtual bool getPinState(int pin) const;
		/// Returns the state of the input or output pin with the given index (0 - 31).

	virtual bool getPropertyBool(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual double getPropertyDouble(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual int getPropertyInt(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual std::string getPropertyString(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual bool hasFeature(const std::string& name) const;
		/// Returns true if the feature with the given name
		/// is known, or false otherwise.

	virtual bool hasProperty(const std::string& name) const;
		/// Returns true if the property with the given name
		/// exists, or false otherwise.

	virtual Poco::UInt32 inputs() const;
		/// Returns a bitmask specifying available input ports.
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.

	virtual bool isAvailable(int pin) const;
		/// Returns true if the I/O pin with the given index (0 - 31)
		/// is available.

	virtual bool isInput(int pin) const;
		/// Returns true if the given pin is configured as input, otherwise false.

	virtual bool isOutput(int pin) const;
		/// Returns true if the given pin is configured as output, otherwise false.

	virtual Poco::UInt32 outputs() const;
		/// Returns a bitmask specifying available input ports.
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.

	virtual void remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setFeature(const std::string& name, bool enable);
		/// Enables or disables the feature with the given name.
		///
		/// Which features are supported is defined by the
		/// actual device implementation.

	virtual void setPinState(int pin, bool value);
		/// Sets the state of the output pin with the given index (0 - 31) to
		/// the given value. The pin must be configured as an output pin.

	virtual void setPropertyBool(const std::string& name, bool value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyDouble(const std::string& name, double value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyInt(const std::string& name, int value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyString(const std::string& name, const std::string& value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setState(Poco::UInt32 state);
		/// Sets the state of all output pins according to the given bit mask.
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.
		/// Only pins configured as output will be affected.

	virtual void setStateMask(Poco::UInt32 state, Poco::UInt32 mask);
		/// Sets the state of certain output pins according to the given state bit mask
		/// and logical pin selection bit mask. Only pins whose bit in mask is 1
		/// will be changed.
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.
		/// Only pins configured as output will be affected.

	virtual Poco::UInt32 state() const;
		/// Returns the current state of all input and output pins as
		/// a bit mask. 
		///
		/// Bit 0 corresponds to logical pin 0, bit 31 to logical pin 31. 
		/// Actual mapping of logical pins to physical
		/// pins is configured when setting up the IO device.

protected:
	void event__stateChanged(const Poco::UInt32& data);

private:
	Poco::SharedPtr<IoT::Devices::IO> _pServiceObject;
};


inline Poco::UInt32 IORemoteObject::available() const
{
	return _pServiceObject->available();
}


inline bool IORemoteObject::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool IORemoteObject::getPinState(int pin) const
{
	return _pServiceObject->getPinState(pin);
}


inline bool IORemoteObject::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double IORemoteObject::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int IORemoteObject::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string IORemoteObject::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool IORemoteObject::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool IORemoteObject::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline Poco::UInt32 IORemoteObject::inputs() const
{
	return _pServiceObject->inputs();
}


inline bool IORemoteObject::isAvailable(int pin) const
{
	return _pServiceObject->isAvailable(pin);
}


inline bool IORemoteObject::isInput(int pin) const
{
	return _pServiceObject->isInput(pin);
}


inline bool IORemoteObject::isOutput(int pin) const
{
	return _pServiceObject->isOutput(pin);
}


inline Poco::UInt32 IORemoteObject::outputs() const
{
	return _pServiceObject->outputs();
}


inline const Poco::RemotingNG::Identifiable::TypeId& IORemoteObject::remoting__typeId() const
{
	return IIO::remoting__typeId();
}


inline void IORemoteObject::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void IORemoteObject::setPinState(int pin, bool value)
{
	_pServiceObject->setPinState(pin, value);
}


inline void IORemoteObject::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void IORemoteObject::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void IORemoteObject::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void IORemoteObject::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


inline void IORemoteObject::setState(Poco::UInt32 state)
{
	_pServiceObject->setState(state);
}


inline void IORemoteObject::setStateMask(Poco::UInt32 state, Poco::UInt32 mask)
{
	_pServiceObject->setStateMask(state, mask);
}


inline Poco::UInt32 IORemoteObject::state() const
{
	return _pServiceObject->state();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IORemoteObject_INCLUDED

