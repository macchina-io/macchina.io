//
// ScalarDatapointRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ScalarDatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_ScalarDatapointRemoteObject_INCLUDED
#define IoT_Devices_ScalarDatapointRemoteObject_INCLUDED


#include "IoT/Devices/IScalarDatapoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class ScalarDatapointRemoteObject: public IoT::Devices::IScalarDatapoint, public Poco::RemotingNG::RemoteObject
	/// A scalar datapoint holding a single numeric (double) value.
	///
	/// In addition to the methods defined in this interface,
	/// a ScalarDatapoint implementation should expose the following
	/// properties:
	///   - physicalQuantity (string): The physical quantity that is
	///     being measured by the datapoint, e.g. "temperature".
	///   - physicalUnit (string): The physical unit the measured value
	///     is being represented in (e.g. "Cel" for degree Celsius).
	///     This should use the "c/s" symbols from the Unified Code for Units of Measure
	///     (http://unitsofmeasure.org/ucum.html).
	///     See the PHYSICAL_UNIT_* strings for predefined values.
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Ptr = Poco::AutoPtr<ScalarDatapointRemoteObject>;

	ScalarDatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::ScalarDatapoint> pServiceObject);
		/// Creates a ScalarDatapointRemoteObject.

	virtual ~ScalarDatapointRemoteObject();
		/// Destroys the ScalarDatapointRemoteObject.

	void clearValueChangedFilter(const std::string& subscriberURI);
		/// Clears the filter set for the valueChanged event.

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

	void setValueChangedHysteresisFilter(const std::string& subscriberURI, double lowerThreshold, double upperThreshold);
		/// Sets a Poco::RemotingNG::HysteresisFilter for the valueChanged event.

	void setValueChangedIsGreaterThanFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::GreaterThanFilter for the valueChanged event.

	void setValueChangedIsGreaterThanOrEqualToFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::GreaterThanFilter for the valueChanged event.

	void setValueChangedIsLessThanFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::LessThanFilter for the valueChanged event.

	void setValueChangedIsLessThanOrEqualToFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::LessThanOrEqualToFilter for the valueChanged event.

	void setValueChangedMinimumDeltaFilter(const std::string& subscriberURI, double delta);
		/// Sets a Poco::RemotingNG::MinimumDeltaFilter for the valueChanged event.

	void setValueChangedMinimumIntervalAndDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta);
		/// Sets a Poco::RemotingNG::MinimumIntervalAndDeltaFilter for the valueChanged event.

	void setValueChangedMinimumIntervalFilter(const std::string& subscriberURI, long milliseconds);
		/// Sets a Poco::RemotingNG::MinimumIntervalFilter for the valueChanged event.

	void setValueChangedMinimumIntervalOrDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta);
		/// Sets a Poco::RemotingNG::MinimumIntervalOrDeltaFilter for the valueChanged event.

	virtual void update(double value);
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

	Poco::Optional<double> validValue() const;
		/// Returns the current value held by the datapoint if
		/// it is valid, otherwise an empty value.

	virtual double value() const;
		/// Returns the current value held by the datapoint,
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

protected:
	void event__invalidated();

	void event__statusChanged(const IoT::Devices::DeviceStatusChange& data);

	void event__validated(const double& data);

	void event__valueChanged(const double& data);

	void event__valueUpdated(const double& data);

private:
	Poco::SharedPtr<IoT::Devices::ScalarDatapoint> _pServiceObject;
};


inline void ScalarDatapointRemoteObject::clearValueChangedFilter(const std::string& subscriberURI)
{
	_pServiceObject->clearValueChangedFilter(subscriberURI);
}


inline bool ScalarDatapointRemoteObject::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool ScalarDatapointRemoteObject::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double ScalarDatapointRemoteObject::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int ScalarDatapointRemoteObject::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline Poco::Int16 ScalarDatapointRemoteObject::getPropertyInt16(const std::string& name) const
{
	return _pServiceObject->getPropertyInt16(name);
}


inline Poco::Int64 ScalarDatapointRemoteObject::getPropertyInt64(const std::string& name) const
{
	return _pServiceObject->getPropertyInt64(name);
}


inline std::string ScalarDatapointRemoteObject::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline Poco::Timestamp ScalarDatapointRemoteObject::getPropertyTimestamp(const std::string& name) const
{
	return _pServiceObject->getPropertyTimestamp(name);
}


inline bool ScalarDatapointRemoteObject::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool ScalarDatapointRemoteObject::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline void ScalarDatapointRemoteObject::invalidate()
{
	_pServiceObject->invalidate();
}


inline const Poco::RemotingNG::Identifiable::TypeId& ScalarDatapointRemoteObject::remoting__typeId() const
{
	return IScalarDatapoint::remoting__typeId();
}


inline void ScalarDatapointRemoteObject::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void ScalarDatapointRemoteObject::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void ScalarDatapointRemoteObject::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void ScalarDatapointRemoteObject::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void ScalarDatapointRemoteObject::setPropertyInt16(const std::string& name, Poco::Int16 value)
{
	_pServiceObject->setPropertyInt16(name, value);
}


inline void ScalarDatapointRemoteObject::setPropertyInt64(const std::string& name, Poco::Int64 value)
{
	_pServiceObject->setPropertyInt64(name, value);
}


inline void ScalarDatapointRemoteObject::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


inline void ScalarDatapointRemoteObject::setPropertyTimestamp(const std::string& name, Poco::Timestamp value)
{
	_pServiceObject->setPropertyTimestamp(name, value);
}


inline void ScalarDatapointRemoteObject::setValueChangedHysteresisFilter(const std::string& subscriberURI, double lowerThreshold, double upperThreshold)
{
	_pServiceObject->setValueChangedHysteresisFilter(subscriberURI, lowerThreshold, upperThreshold);
}


inline void ScalarDatapointRemoteObject::setValueChangedIsGreaterThanFilter(const std::string& subscriberURI, double limit)
{
	_pServiceObject->setValueChangedIsGreaterThanFilter(subscriberURI, limit);
}


inline void ScalarDatapointRemoteObject::setValueChangedIsGreaterThanOrEqualToFilter(const std::string& subscriberURI, double limit)
{
	_pServiceObject->setValueChangedIsGreaterThanOrEqualToFilter(subscriberURI, limit);
}


inline void ScalarDatapointRemoteObject::setValueChangedIsLessThanFilter(const std::string& subscriberURI, double limit)
{
	_pServiceObject->setValueChangedIsLessThanFilter(subscriberURI, limit);
}


inline void ScalarDatapointRemoteObject::setValueChangedIsLessThanOrEqualToFilter(const std::string& subscriberURI, double limit)
{
	_pServiceObject->setValueChangedIsLessThanOrEqualToFilter(subscriberURI, limit);
}


inline void ScalarDatapointRemoteObject::setValueChangedMinimumDeltaFilter(const std::string& subscriberURI, double delta)
{
	_pServiceObject->setValueChangedMinimumDeltaFilter(subscriberURI, delta);
}


inline void ScalarDatapointRemoteObject::setValueChangedMinimumIntervalAndDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta)
{
	_pServiceObject->setValueChangedMinimumIntervalAndDeltaFilter(subscriberURI, milliseconds, delta);
}


inline void ScalarDatapointRemoteObject::setValueChangedMinimumIntervalFilter(const std::string& subscriberURI, long milliseconds)
{
	_pServiceObject->setValueChangedMinimumIntervalFilter(subscriberURI, milliseconds);
}


inline void ScalarDatapointRemoteObject::setValueChangedMinimumIntervalOrDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta)
{
	_pServiceObject->setValueChangedMinimumIntervalOrDeltaFilter(subscriberURI, milliseconds, delta);
}


inline void ScalarDatapointRemoteObject::update(double value)
{
	_pServiceObject->update(value);
}


inline bool ScalarDatapointRemoteObject::valid() const
{
	return _pServiceObject->valid();
}


inline Poco::Optional<double> ScalarDatapointRemoteObject::validValue() const
{
	return _pServiceObject->validValue();
}


inline double ScalarDatapointRemoteObject::value() const
{
	return _pServiceObject->value();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_ScalarDatapointRemoteObject_INCLUDED

