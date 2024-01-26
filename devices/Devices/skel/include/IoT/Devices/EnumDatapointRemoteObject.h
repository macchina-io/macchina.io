//
// EnumDatapointRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  EnumDatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_EnumDatapointRemoteObject_INCLUDED
#define IoT_Devices_EnumDatapointRemoteObject_INCLUDED


#include "IoT/Devices/IEnumDatapoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class EnumDatapointRemoteObject: public IoT::Devices::IEnumDatapoint, public Poco::RemotingNG::RemoteObject
	/// The base class for datapoints holding an enumeration
	/// value (based on an int).
	///
	/// An implementation should handle conversion between an
	/// integer value and the corresponding symbolic name.
	///
	/// In addition to the methods defined in this interface,
	/// a EnumDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Ptr = Poco::AutoPtr<EnumDatapointRemoteObject>;

	EnumDatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::EnumDatapoint> pServiceObject);
		/// Creates a EnumDatapointRemoteObject.

	virtual ~EnumDatapointRemoteObject();
		/// Destroys the EnumDatapointRemoteObject.

	std::vector < IoT::Devices::EnumValue > definedValues() const;
		/// Returns a vector containing the possible values
		/// and mappings to symbolic names.

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

	virtual std::string stringValue() const;
		/// Returns the symbolic name corresponding to the datapoint's current value,
		/// even if the datapoint has been invalidated.
		///
		/// Use validStringValue() to get a valid value only.

	virtual void update(int value);
		/// Updates the value of the enumeration.
		///
		/// Throws a Poco::InvalidArgumentException if the given value
		/// is not in the range of defined values.

	virtual void updateString(const std::string& symbolicName);
		/// Updates the value of the enumeration from
		/// the given symbolic name.
		///
		/// Throws a Poco::InvalidArgumentException if the given symbolicName
		/// is not in the range of defined values and their symbolic names.

	virtual bool valid() const;
		/// Returns true if a valid value is available.
		///
		/// Note that between the time valid() is called and
		/// a subsequent call to value() or similar method, the
		/// validity may change. Use validValue() or similar methods
		/// of subclasses to atomically get validity and value.

	virtual Poco::Optional < std::string > validStringValue() const;
		/// Returns the symbolic name corresponding to the datapoint's current value
		/// if the datapoint is valid, otherwise an empty value.

	virtual Poco::Optional < int > validValue() const;
		/// Returns the current integer value of the datapoint
		/// if it is valid, otherwise an empty value.

	virtual int value() const;
		/// Returns the current integer value of the datapoint,
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

protected:
	void event__invalidated();

	void event__statusChanged(const IoT::Devices::DeviceStatusChange& data);

	void event__validated(const int& data);

	void event__valueChanged(const int& data);

	void event__valueUpdated(const int& data);

private:
	Poco::SharedPtr<IoT::Devices::EnumDatapoint> _pServiceObject;
};


inline std::vector < IoT::Devices::EnumValue > EnumDatapointRemoteObject::definedValues() const
{
	return _pServiceObject->definedValues();
}


inline bool EnumDatapointRemoteObject::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool EnumDatapointRemoteObject::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double EnumDatapointRemoteObject::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int EnumDatapointRemoteObject::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline Poco::Int16 EnumDatapointRemoteObject::getPropertyInt16(const std::string& name) const
{
	return _pServiceObject->getPropertyInt16(name);
}


inline Poco::Int64 EnumDatapointRemoteObject::getPropertyInt64(const std::string& name) const
{
	return _pServiceObject->getPropertyInt64(name);
}


inline std::string EnumDatapointRemoteObject::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline Poco::Timestamp EnumDatapointRemoteObject::getPropertyTimestamp(const std::string& name) const
{
	return _pServiceObject->getPropertyTimestamp(name);
}


inline bool EnumDatapointRemoteObject::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool EnumDatapointRemoteObject::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline void EnumDatapointRemoteObject::invalidate()
{
	_pServiceObject->invalidate();
}


inline const Poco::RemotingNG::Identifiable::TypeId& EnumDatapointRemoteObject::remoting__typeId() const
{
	return IEnumDatapoint::remoting__typeId();
}


inline void EnumDatapointRemoteObject::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void EnumDatapointRemoteObject::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void EnumDatapointRemoteObject::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void EnumDatapointRemoteObject::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void EnumDatapointRemoteObject::setPropertyInt16(const std::string& name, Poco::Int16 value)
{
	_pServiceObject->setPropertyInt16(name, value);
}


inline void EnumDatapointRemoteObject::setPropertyInt64(const std::string& name, Poco::Int64 value)
{
	_pServiceObject->setPropertyInt64(name, value);
}


inline void EnumDatapointRemoteObject::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


inline void EnumDatapointRemoteObject::setPropertyTimestamp(const std::string& name, Poco::Timestamp value)
{
	_pServiceObject->setPropertyTimestamp(name, value);
}


inline std::string EnumDatapointRemoteObject::stringValue() const
{
	return _pServiceObject->stringValue();
}


inline void EnumDatapointRemoteObject::update(int value)
{
	_pServiceObject->update(value);
}


inline void EnumDatapointRemoteObject::updateString(const std::string& symbolicName)
{
	_pServiceObject->updateString(symbolicName);
}


inline bool EnumDatapointRemoteObject::valid() const
{
	return _pServiceObject->valid();
}


inline Poco::Optional < std::string > EnumDatapointRemoteObject::validStringValue() const
{
	return _pServiceObject->validStringValue();
}


inline Poco::Optional < int > EnumDatapointRemoteObject::validValue() const
{
	return _pServiceObject->validValue();
}


inline int EnumDatapointRemoteObject::value() const
{
	return _pServiceObject->value();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_EnumDatapointRemoteObject_INCLUDED

