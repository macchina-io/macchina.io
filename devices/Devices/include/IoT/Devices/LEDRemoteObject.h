//
// LEDRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  LEDRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_LEDRemoteObject_INCLUDED
#define IoT_Devices_LEDRemoteObject_INCLUDED


#include "IoT/Devices/ILED.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class LEDRemoteObject: public IoT::Devices::ILED, public Poco::RemotingNG::RemoteObject
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
	typedef Poco::AutoPtr<LEDRemoteObject> Ptr;

	LEDRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::LED> pServiceObject);
		/// Creates a LEDRemoteObject.

	virtual ~LEDRemoteObject();
		/// Destroys the LEDRemoteObject.

	virtual void blink(int onMilliseconds, int offMilliseconds);
		/// Turns on blinking of the LED.
		///
		/// May not be supported by all implementations.

	virtual double getBrightness() const;
		/// Returns the current brightness of the LED in range 0.0 to 1.0.
		///
		/// 0.0 means off, every value > 0.0 means on, with 1.0 being 
		/// the maximum brightness level.
		///
		/// Note that most LED devices do not support different brightness levels
		/// and can only be turned on or off.

	virtual bool getFeature(const std::string& name) const;
		/// Returns true if the feature with the given name
		/// is enabled, or false otherwise.

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

	virtual void off();
		/// Convenience method that turns the LED off by
		/// calling setBrightness(0.0).

	virtual void on();
		/// Convenience method that turns the LED on by
		/// calling setBrightness(1.0).

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setBrightness(double brightness);
		/// Sets the brightness of the LED.
		///
		/// 0.0 means off, every value > 0.0 means on, with 1.0 being 
		/// the maximum brightness level.
		///
		/// Note that most LED devices do not support different brightness levels
		/// and can only be turned on or off.

	virtual void setFeature(const std::string& name, bool enable);
		/// Enables or disables the feature with the given name.
		///
		/// Which features are supported is defined by the
		/// actual device implementation.

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

private:
	Poco::SharedPtr<IoT::Devices::LED> _pServiceObject;
};


inline void LEDRemoteObject::blink(int onMilliseconds, int offMilliseconds)
{
	_pServiceObject->blink(onMilliseconds, offMilliseconds);
}


inline double LEDRemoteObject::getBrightness() const
{
	return _pServiceObject->getBrightness();
}


inline bool LEDRemoteObject::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool LEDRemoteObject::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double LEDRemoteObject::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int LEDRemoteObject::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string LEDRemoteObject::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool LEDRemoteObject::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool LEDRemoteObject::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline void LEDRemoteObject::off()
{
	_pServiceObject->off();
}


inline void LEDRemoteObject::on()
{
	_pServiceObject->on();
}


inline const Poco::RemotingNG::Identifiable::TypeId& LEDRemoteObject::remoting__typeId() const
{
	return ILED::remoting__typeId();
}


inline void LEDRemoteObject::setBrightness(double brightness)
{
	_pServiceObject->setBrightness(brightness);
}


inline void LEDRemoteObject::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void LEDRemoteObject::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void LEDRemoteObject::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void LEDRemoteObject::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void LEDRemoteObject::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_LEDRemoteObject_INCLUDED

