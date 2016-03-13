//
// SensorRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SensorRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SensorRemoteObject_INCLUDED
#define IoT_Devices_SensorRemoteObject_INCLUDED


#include "IoT/Devices/ISensor.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class SensorRemoteObject: public IoT::Devices::ISensor, public Poco::RemotingNG::RemoteObject
	/// The base class for analog sensors, such as
	/// temperature or ambient light sensors.
	///
	/// In addition to the methods defined in this interface,
	/// a Sensor implementation should expose the following
	/// properties:
	///   - physicalQuantity (string): The physical quantity that is
	///     being measured by the sensor, e.g. "temperature".
	///   - physicalUnit (string): The physical unit the measured value
	///     is being represented in (e.g. "°C"), UTF-8 encoded.
	///     See the PHYSICAL_UNIT_* strings for predefined values.
	///   - displayValue (string, optional): The current value of the sensor,
	///     formatted as string for display purposes.
{
public:
	typedef Poco::AutoPtr<SensorRemoteObject> Ptr;

	SensorRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Sensor> pServiceObject);
		/// Creates a SensorRemoteObject.

	virtual ~SensorRemoteObject();
		/// Destroys the SensorRemoteObject.

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

	virtual bool ready() const;
		/// Returns true if a valid value is available.

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

	void setValueChangedHysteresisFilter(const std::string& subscriberURI, double lowerThreshold, double upperThreshold);
		/// Sets a Poco::RemotingNG::HysteresisFilter for the valueChanged event.

	void setValueChangedIsGreaterThanFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::GreaterThanFilter for the valueChanged event.

	void setValueChangedIsGreaterThanOrEqualToFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::GreaterThanFilter for the valueChanged event.

	void setValueChangedIsLessThanOrEqualToFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::LessThanOrEqualToFilter for the valueChanged event.

	void setValueChangedIsLessThanThanFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::LessThanFilter for the valueChanged event.

	void setValueChangedMinimumDeltaFilter(const std::string& subscriberURI, double delta);
		/// Sets a Poco::RemotingNG::MinimumDeltaFilter for the valueChanged event.

	void setValueChangedMinimumIntervalFilter(const std::string& subscriberURI, long milliseconds);
		/// Sets a Poco::RemotingNG::MinimumIntervalFilter for the valueChanged event.

	void setValueChangedMinimumIntervalOrDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta);
		/// Sets a Poco::RemotingNG::MinimumIntervalOrDeltaFilter for the valueChanged event.

	virtual double value() const;
		/// Returns the current value measured by the sensor.
		///
		/// Some sensors may not be able to immediately report
		/// a valid value. Therefore, before calling value() the first time, ready() 
		/// should be called to check if a valid value is available.

protected:
	void event__valueChanged(const double& data);

private:
	Poco::SharedPtr<IoT::Devices::Sensor> _pServiceObject;
};


inline void SensorRemoteObject::clearValueChangedFilter(const std::string& subscriberURI)
{
	_pServiceObject->clearValueChangedFilter(subscriberURI);
}


inline bool SensorRemoteObject::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool SensorRemoteObject::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double SensorRemoteObject::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int SensorRemoteObject::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string SensorRemoteObject::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool SensorRemoteObject::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool SensorRemoteObject::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline bool SensorRemoteObject::ready() const
{
	return _pServiceObject->ready();
}


inline const Poco::RemotingNG::Identifiable::TypeId& SensorRemoteObject::remoting__typeId() const
{
	return ISensor::remoting__typeId();
}


inline void SensorRemoteObject::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void SensorRemoteObject::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void SensorRemoteObject::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void SensorRemoteObject::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void SensorRemoteObject::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


inline void SensorRemoteObject::setValueChangedHysteresisFilter(const std::string& subscriberURI, double lowerThreshold, double upperThreshold)
{
	_pServiceObject->setValueChangedHysteresisFilter(subscriberURI, lowerThreshold, upperThreshold);
}


inline void SensorRemoteObject::setValueChangedIsGreaterThanFilter(const std::string& subscriberURI, double limit)
{
	_pServiceObject->setValueChangedIsGreaterThanFilter(subscriberURI, limit);
}


inline void SensorRemoteObject::setValueChangedIsGreaterThanOrEqualToFilter(const std::string& subscriberURI, double limit)
{
	_pServiceObject->setValueChangedIsGreaterThanOrEqualToFilter(subscriberURI, limit);
}


inline void SensorRemoteObject::setValueChangedIsLessThanOrEqualToFilter(const std::string& subscriberURI, double limit)
{
	_pServiceObject->setValueChangedIsLessThanOrEqualToFilter(subscriberURI, limit);
}


inline void SensorRemoteObject::setValueChangedIsLessThanThanFilter(const std::string& subscriberURI, double limit)
{
	_pServiceObject->setValueChangedIsLessThanThanFilter(subscriberURI, limit);
}


inline void SensorRemoteObject::setValueChangedMinimumDeltaFilter(const std::string& subscriberURI, double delta)
{
	_pServiceObject->setValueChangedMinimumDeltaFilter(subscriberURI, delta);
}


inline void SensorRemoteObject::setValueChangedMinimumIntervalFilter(const std::string& subscriberURI, long milliseconds)
{
	_pServiceObject->setValueChangedMinimumIntervalFilter(subscriberURI, milliseconds);
}


inline void SensorRemoteObject::setValueChangedMinimumIntervalOrDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta)
{
	_pServiceObject->setValueChangedMinimumIntervalOrDeltaFilter(subscriberURI, milliseconds, delta);
}


inline double SensorRemoteObject::value() const
{
	return _pServiceObject->value();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SensorRemoteObject_INCLUDED

