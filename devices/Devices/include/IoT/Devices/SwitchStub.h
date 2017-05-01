//
// SwitchStub.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SwitchStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SwitchStub_INCLUDED
#define IoT_Devices_SwitchStub_INCLUDED


#include "IoT/Devices/SwitchRemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class SwitchStub: public IoT::Devices::SwitchRemoteObject
	/// The base class for switchable things (that can
	/// be turned on and off).
	///
	/// A Switch has a current state and a target state.
	/// Depending upon the implementation, the current state
	/// and target state may be different for a short amount
	/// of time (e.g., while the device is powering on).
	///
	/// In addition to the methods defined in this interface,
	/// a Switch implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the Switch,
	///     formatted as string for display purposes.
{
public:
	typedef Poco::AutoPtr<SwitchStub> Ptr;

	SwitchStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Switch> pServiceObject);
		/// Creates a SwitchStub.

	virtual ~SwitchStub();
		/// Destroys the SwitchStub.

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

	virtual bool getTargetState() const;
		/// Returns the target state of the Switch.

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

	virtual void setTargetState(bool newState);
		/// Sets the target state of the Switch.

	virtual bool state() const;
		/// Returns the current state of the Switch.

protected:
	void event__stateChanged(const bool& data);

private:
	Poco::SharedPtr<IoT::Devices::Switch> _pServiceObject;
};


inline bool SwitchStub::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool SwitchStub::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double SwitchStub::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int SwitchStub::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string SwitchStub::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool SwitchStub::getTargetState() const
{
	return _pServiceObject->getTargetState();
}


inline bool SwitchStub::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool SwitchStub::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline const Poco::RemotingNG::Identifiable::TypeId& SwitchStub::remoting__typeId() const
{
	return ISwitch::remoting__typeId();
}


inline void SwitchStub::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void SwitchStub::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void SwitchStub::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void SwitchStub::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void SwitchStub::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


inline void SwitchStub::setTargetState(bool newState)
{
	_pServiceObject->setTargetState(newState);
}


inline bool SwitchStub::state() const
{
	return _pServiceObject->state();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SwitchStub_INCLUDED

