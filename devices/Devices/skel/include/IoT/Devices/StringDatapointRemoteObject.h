//
// StringDatapointRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  StringDatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_StringDatapointRemoteObject_INCLUDED
#define IoT_Devices_StringDatapointRemoteObject_INCLUDED


#include "IoT/Devices/IStringDatapoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class StringDatapointRemoteObject: public IoT::Devices::IStringDatapoint, public Poco::RemotingNG::RemoteObject
	/// The base class for datapoints holding a string value.
	///
	/// In addition to the methods defined in this interface,
	/// a StringDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Ptr = Poco::AutoPtr<StringDatapointRemoteObject>;

	StringDatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::StringDatapoint> pServiceObject);
		/// Creates a StringDatapointRemoteObject.

	virtual ~StringDatapointRemoteObject();
		/// Destroys the StringDatapointRemoteObject.

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

	virtual Poco::Int16 getPropertyInt16(const std::string& name) const;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual Poco::Int64 getPropertyInt64(const std::string& name) const;
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

	virtual Poco::Timestamp getPropertyTimestamp(const std::string& name) const;
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

	virtual void invalidate();
		/// Invalidates the datapoint's value.
		///
		/// Subsequent calls to valid() will return false,
		/// until a new value has been set.

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

	virtual void setPropertyInt16(const std::string& name, Poco::Int16 value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyInt64(const std::string& name, Poco::Int64 value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyString(const std::string& name, const std::string& value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyTimestamp(const std::string& name, Poco::Timestamp value);
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void update(const std::string& value);
		/// Updates the value of the datapoint and makes it valid.
		///
		/// Not all Datapoint implementations may support
		/// this method.

	virtual bool valid() const;
		/// Returns true if a valid value is available.
		///
		/// Note that between the time valid() is called and
		/// a subsequent call to value() or similar method, the
		/// validity may change. Use validValue() or similar methods
		/// of subclasses to atomically get validity and value.

	virtual Poco::Optional < std::string > validValue() const;
		/// Returns the current value of the datapoint if
		/// it is valid, otherwise an empty value.

	virtual std::string value() const;
		/// Returns the current value of the datapoint,
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

protected:
	void event__invalidated();

	void event__statusChanged(const IoT::Devices::DeviceStatusChange& data);

	void event__validated(const std::string& data);

	void event__valueChanged(const std::string& data);

	void event__valueUpdated(const std::string& data);

private:
	Poco::SharedPtr<IoT::Devices::StringDatapoint> _pServiceObject;
};


inline bool StringDatapointRemoteObject::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool StringDatapointRemoteObject::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double StringDatapointRemoteObject::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int StringDatapointRemoteObject::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline Poco::Int16 StringDatapointRemoteObject::getPropertyInt16(const std::string& name) const
{
	return _pServiceObject->getPropertyInt16(name);
}


inline Poco::Int64 StringDatapointRemoteObject::getPropertyInt64(const std::string& name) const
{
	return _pServiceObject->getPropertyInt64(name);
}


inline std::string StringDatapointRemoteObject::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline Poco::Timestamp StringDatapointRemoteObject::getPropertyTimestamp(const std::string& name) const
{
	return _pServiceObject->getPropertyTimestamp(name);
}


inline bool StringDatapointRemoteObject::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool StringDatapointRemoteObject::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline void StringDatapointRemoteObject::invalidate()
{
	_pServiceObject->invalidate();
}


inline const Poco::RemotingNG::Identifiable::TypeId& StringDatapointRemoteObject::remoting__typeId() const
{
	return IStringDatapoint::remoting__typeId();
}


inline void StringDatapointRemoteObject::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void StringDatapointRemoteObject::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void StringDatapointRemoteObject::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void StringDatapointRemoteObject::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void StringDatapointRemoteObject::setPropertyInt16(const std::string& name, Poco::Int16 value)
{
	_pServiceObject->setPropertyInt16(name, value);
}


inline void StringDatapointRemoteObject::setPropertyInt64(const std::string& name, Poco::Int64 value)
{
	_pServiceObject->setPropertyInt64(name, value);
}


inline void StringDatapointRemoteObject::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


inline void StringDatapointRemoteObject::setPropertyTimestamp(const std::string& name, Poco::Timestamp value)
{
	_pServiceObject->setPropertyTimestamp(name, value);
}


inline void StringDatapointRemoteObject::update(const std::string& value)
{
	_pServiceObject->update(value);
}


inline bool StringDatapointRemoteObject::valid() const
{
	return _pServiceObject->valid();
}


inline Poco::Optional < std::string > StringDatapointRemoteObject::validValue() const
{
	return _pServiceObject->validValue();
}


inline std::string StringDatapointRemoteObject::value() const
{
	return _pServiceObject->value();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_StringDatapointRemoteObject_INCLUDED

