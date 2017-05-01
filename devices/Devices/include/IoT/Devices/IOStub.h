//
// IOStub.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IOStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IOStub_INCLUDED
#define IoT_Devices_IOStub_INCLUDED


#include "IoT/Devices/IORemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class IOStub: public IoT::Devices::IORemoteObject
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
	typedef Poco::AutoPtr<IOStub> Ptr;

	IOStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::IO> pServiceObject);
		/// Creates a IOStub.

	virtual ~IOStub();
		/// Destroys the IOStub.

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

	virtual void set(bool state);
		/// Sets the state of an output pin to the given state.

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

	virtual bool state() const;
		/// Returns the current state of the pin.

protected:
	void event__stateChanged(const bool& data);

private:
	Poco::SharedPtr<IoT::Devices::IO> _pServiceObject;
};


inline bool IOStub::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool IOStub::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double IOStub::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int IOStub::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string IOStub::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool IOStub::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool IOStub::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline const Poco::RemotingNG::Identifiable::TypeId& IOStub::remoting__typeId() const
{
	return IIO::remoting__typeId();
}


inline void IOStub::set(bool state)
{
	_pServiceObject->set(state);
}


inline void IOStub::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void IOStub::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void IOStub::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void IOStub::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void IOStub::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


inline bool IOStub::state() const
{
	return _pServiceObject->state();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IOStub_INCLUDED

