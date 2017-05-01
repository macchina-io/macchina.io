//
// RotaryEncoderStub.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  RotaryEncoderStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_RotaryEncoderStub_INCLUDED
#define IoT_Devices_RotaryEncoderStub_INCLUDED


#include "IoT/Devices/RotaryEncoderRemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class RotaryEncoderStub: public IoT::Devices::RotaryEncoderRemoteObject
	/// A rotary encoder with an optional push button.
{
public:
	typedef Poco::AutoPtr<RotaryEncoderStub> Ptr;

	RotaryEncoderStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::RotaryEncoder> pServiceObject);
		/// Creates a RotaryEncoderStub.

	virtual ~RotaryEncoderStub();
		/// Destroys the RotaryEncoderStub.

	virtual bool buttonState() const;
		/// Returns the current state of the button.

	virtual Poco::Int32 count() const;
		/// Returns the current value of the counter.

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

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual Poco::Int32 reset();
		/// Returns the current value of the counter and
		/// sets the counter to 0.

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

protected:
	void event__buttonStateChanged(const bool& data);

	void event__countChanged(const Poco::Int32& data);

private:
	Poco::SharedPtr<IoT::Devices::RotaryEncoder> _pServiceObject;
};


inline bool RotaryEncoderStub::buttonState() const
{
	return _pServiceObject->buttonState();
}


inline Poco::Int32 RotaryEncoderStub::count() const
{
	return _pServiceObject->count();
}


inline bool RotaryEncoderStub::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool RotaryEncoderStub::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double RotaryEncoderStub::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int RotaryEncoderStub::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string RotaryEncoderStub::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool RotaryEncoderStub::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool RotaryEncoderStub::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline const Poco::RemotingNG::Identifiable::TypeId& RotaryEncoderStub::remoting__typeId() const
{
	return IRotaryEncoder::remoting__typeId();
}


inline Poco::Int32 RotaryEncoderStub::reset()
{
	return _pServiceObject->reset();
}


inline void RotaryEncoderStub::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void RotaryEncoderStub::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void RotaryEncoderStub::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void RotaryEncoderStub::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void RotaryEncoderStub::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_RotaryEncoderStub_INCLUDED

