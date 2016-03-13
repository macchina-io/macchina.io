//
// GNSSSensorRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  GNSSSensorRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GNSSSensorRemoteObject_INCLUDED
#define IoT_Devices_GNSSSensorRemoteObject_INCLUDED


#include "IoT/Devices/IGNSSSensor.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class GNSSSensorRemoteObject: public IoT::Devices::IGNSSSensor, public Poco::RemotingNG::RemoteObject
	/// The interface for GNSS/GPS receivers.
	///
	/// Implementations of this class should also support the
	/// following (optional) properties for configuration:
	///
	///   - positionChangedPeriod (int): the minimum time interval
	///     in milliseconds between firings of the positionUpdate event.
	///   - positionChangedDelta (int): the minimum distance (in meters)
	///     the receiver must move before the positionUpdate event
	///     is fired again.
	///   - positionTimeout (int): Timeout in milliseconds after which the
	///     positionLost event is fired if no valid position has been
	///     received from the GNSS receiver.
{
public:
	typedef Poco::AutoPtr<GNSSSensorRemoteObject> Ptr;

	GNSSSensorRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::GNSSSensor> pServiceObject);
		/// Creates a GNSSSensorRemoteObject.

	virtual ~GNSSSensorRemoteObject();
		/// Destroys the GNSSSensorRemoteObject.

	virtual double altitude() const;
		/// Returns the current altitude above sea level in meters.
		/// Returns -9999 if no altitude is available.

	virtual double course() const;
		/// Returns the current course in degrees [0, 360).

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

	virtual double hdop() const;
		/// Returns the Horizontal Dilution Of Precision (HDOP) in meters,
		/// or -9999 if no HDOP value is available.

	virtual double magneticVariation() const;
		/// Returns the current magnetic variation in degrees [0, 360).
		/// Returns -1 if no magnetic variation is available.

	IoT::Devices::LatLon position() const;
		/// Returns the last obtained position.
		///
		/// If no position is available, latitude and longitude will both be 0.
		/// To disambiguate with a real position, also check positionAvailable().

	virtual bool positionAvailable() const;
		/// Returns true if a valid position is available.

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

	virtual double speed() const;
		/// Returns the current speed in nautical knots.
		/// If no speed is available, returns -1.

protected:
	void event__positionLost();

	void event__positionUpdate(const IoT::Devices::PositionUpdate& data);

private:
	Poco::SharedPtr<IoT::Devices::GNSSSensor> _pServiceObject;
};


inline double GNSSSensorRemoteObject::altitude() const
{
	return _pServiceObject->altitude();
}


inline double GNSSSensorRemoteObject::course() const
{
	return _pServiceObject->course();
}


inline bool GNSSSensorRemoteObject::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool GNSSSensorRemoteObject::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double GNSSSensorRemoteObject::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int GNSSSensorRemoteObject::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string GNSSSensorRemoteObject::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool GNSSSensorRemoteObject::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool GNSSSensorRemoteObject::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline double GNSSSensorRemoteObject::hdop() const
{
	return _pServiceObject->hdop();
}


inline double GNSSSensorRemoteObject::magneticVariation() const
{
	return _pServiceObject->magneticVariation();
}


inline IoT::Devices::LatLon GNSSSensorRemoteObject::position() const
{
	return _pServiceObject->position();
}


inline bool GNSSSensorRemoteObject::positionAvailable() const
{
	return _pServiceObject->positionAvailable();
}


inline const Poco::RemotingNG::Identifiable::TypeId& GNSSSensorRemoteObject::remoting__typeId() const
{
	return IGNSSSensor::remoting__typeId();
}


inline void GNSSSensorRemoteObject::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void GNSSSensorRemoteObject::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void GNSSSensorRemoteObject::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void GNSSSensorRemoteObject::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void GNSSSensorRemoteObject::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


inline double GNSSSensorRemoteObject::speed() const
{
	return _pServiceObject->speed();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_GNSSSensorRemoteObject_INCLUDED

