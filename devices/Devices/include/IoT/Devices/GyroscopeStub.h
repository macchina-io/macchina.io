//
// GyroscopeStub.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  GyroscopeStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GyroscopeStub_INCLUDED
#define IoT_Devices_GyroscopeStub_INCLUDED


#include "IoT/Devices/GyroscopeRemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class GyroscopeStub: public IoT::Devices::GyroscopeRemoteObject
	/// The interface for three-axis Gyroscopes.
{
public:
	typedef Poco::AutoPtr<GyroscopeStub> Ptr;

	GyroscopeStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Gyroscope> pServiceObject);
		/// Creates a GyroscopeStub.

	virtual ~GyroscopeStub();
		/// Destroys the GyroscopeStub.

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

	IoT::Devices::Rotation rotation() const;
		/// Returns the most recently measured rotation values.

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
	void event__rotationChanged(const IoT::Devices::Rotation& data);

private:
	Poco::SharedPtr<IoT::Devices::Gyroscope> _pServiceObject;
};


inline bool GyroscopeStub::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool GyroscopeStub::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double GyroscopeStub::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int GyroscopeStub::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string GyroscopeStub::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool GyroscopeStub::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool GyroscopeStub::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline const Poco::RemotingNG::Identifiable::TypeId& GyroscopeStub::remoting__typeId() const
{
	return IGyroscope::remoting__typeId();
}


inline IoT::Devices::Rotation GyroscopeStub::rotation() const
{
	return _pServiceObject->rotation();
}


inline void GyroscopeStub::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void GyroscopeStub::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void GyroscopeStub::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void GyroscopeStub::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void GyroscopeStub::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_GyroscopeStub_INCLUDED

