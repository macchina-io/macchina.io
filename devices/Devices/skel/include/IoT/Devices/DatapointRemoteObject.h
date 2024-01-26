//
// DatapointRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  DatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_DatapointRemoteObject_INCLUDED
#define IoT_Devices_DatapointRemoteObject_INCLUDED


#include "IoT/Devices/IDatapoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class DatapointRemoteObject: public IoT::Devices::IDatapoint, public Poco::RemotingNG::RemoteObject
	/// The base class for datapoints.
	/// Datapoints typically represent the result of
	/// sensor measurements, or data obtained from monitoring
	/// processes.
	///
	/// The main difference between a Datapoint and a Sensor is
	/// that a Sensor is typically an interface to a specific
	/// device (i.e., a temperature sensor), whereas a Datapoint 
	/// holds a value that has been acquired from another
	/// device (via a network or bus system) or computed
	/// from other data points.
	///
	/// In addition to the methods defined in this interface,
	/// a Sensor implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
	///   - updated (timestamp, optional): The point in time when the
	///     datapoint's value was last updated.
	///   - access (string, optional): Access permissions ("rw" - read/write,
	///     "ro" - read-only, "wo" - write-only).
	///
	/// Subclasses of Datapoint implement specific value types.
{
public:
	using Ptr = Poco::AutoPtr<DatapointRemoteObject>;

	DatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Datapoint> pServiceObject);
		/// Creates a DatapointRemoteObject.

	virtual ~DatapointRemoteObject();
		/// Destroys the DatapointRemoteObject.

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

	virtual bool valid() const;
		/// Returns true if a valid value is available.
		///
		/// Note that between the time valid() is called and
		/// a subsequent call to value() or similar method, the
		/// validity may change. Use validValue() or similar methods
		/// of subclasses to atomically get validity and value.

protected:
	void event__invalidated();

	void event__statusChanged(const IoT::Devices::DeviceStatusChange& data);

private:
	Poco::SharedPtr<IoT::Devices::Datapoint> _pServiceObject;
};


inline bool DatapointRemoteObject::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool DatapointRemoteObject::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double DatapointRemoteObject::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int DatapointRemoteObject::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline Poco::Int16 DatapointRemoteObject::getPropertyInt16(const std::string& name) const
{
	return _pServiceObject->getPropertyInt16(name);
}


inline Poco::Int64 DatapointRemoteObject::getPropertyInt64(const std::string& name) const
{
	return _pServiceObject->getPropertyInt64(name);
}


inline std::string DatapointRemoteObject::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline Poco::Timestamp DatapointRemoteObject::getPropertyTimestamp(const std::string& name) const
{
	return _pServiceObject->getPropertyTimestamp(name);
}


inline bool DatapointRemoteObject::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool DatapointRemoteObject::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline void DatapointRemoteObject::invalidate()
{
	_pServiceObject->invalidate();
}


inline const Poco::RemotingNG::Identifiable::TypeId& DatapointRemoteObject::remoting__typeId() const
{
	return IDatapoint::remoting__typeId();
}


inline void DatapointRemoteObject::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void DatapointRemoteObject::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void DatapointRemoteObject::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void DatapointRemoteObject::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void DatapointRemoteObject::setPropertyInt16(const std::string& name, Poco::Int16 value)
{
	_pServiceObject->setPropertyInt16(name, value);
}


inline void DatapointRemoteObject::setPropertyInt64(const std::string& name, Poco::Int64 value)
{
	_pServiceObject->setPropertyInt64(name, value);
}


inline void DatapointRemoteObject::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


inline void DatapointRemoteObject::setPropertyTimestamp(const std::string& name, Poco::Timestamp value)
{
	_pServiceObject->setPropertyTimestamp(name, value);
}


inline bool DatapointRemoteObject::valid() const
{
	return _pServiceObject->valid();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_DatapointRemoteObject_INCLUDED

