//
// DeviceStub.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_DeviceStub_INCLUDED
#define IoT_Devices_DeviceStub_INCLUDED


#include "IoT/Devices/DeviceRemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class DeviceStub: public IoT::Devices::DeviceRemoteObject
	/// The base class for all devices and sensors.
	///
	/// This class defines a generic interface for setting
	/// and querying device properties and features.
	///
	/// Every implementation of Device should expose the
	/// following properties:
	///   - symbolicName (string): A name in reverse DNS notation
	///     that identifies the device type (e.g., "io.macchina.serialport").
	///   - name (string): A human-readable device type (e.g., "Serial Port").
{
public:
	typedef Poco::AutoPtr<DeviceStub> Ptr;

	DeviceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Device> pServiceObject);
		/// Creates a DeviceStub.

	virtual ~DeviceStub();
		/// Destroys the DeviceStub.

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

private:
	Poco::SharedPtr<IoT::Devices::Device> _pServiceObject;
};


inline bool DeviceStub::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool DeviceStub::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double DeviceStub::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int DeviceStub::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string DeviceStub::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool DeviceStub::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool DeviceStub::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline const Poco::RemotingNG::Identifiable::TypeId& DeviceStub::remoting__typeId() const
{
	return IDevice::remoting__typeId();
}


inline void DeviceStub::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void DeviceStub::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void DeviceStub::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void DeviceStub::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void DeviceStub::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_DeviceStub_INCLUDED

