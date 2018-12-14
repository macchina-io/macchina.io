//
// DeviceRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_DeviceRemoteObject_INCLUDED
#define IoT_Devices_DeviceRemoteObject_INCLUDED


#include "IoT/Devices/IDevice.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class DeviceRemoteObject: public IoT::Devices::IDevice, public Poco::RemotingNG::RemoteObject
	/// The base class for all devices and sensors.
	///
	/// This class defines a generic interface for setting
	/// and querying device properties and features.
	///
	/// The class also defines an event for notifications
	/// about changes to the device status.
	///
	/// Every implementation of Device should expose the
	/// following properties:
	///   - symbolicName: A name in reverse DNS notation that identifies the
	///     specific implementation of the device type.
	///   - type (string): A name in reverse DNS notation
	///     that identifies the generic device type (e.g., "io.macchina.serial").
	///   - name (string): A human-readable device type (e.g., "Serial Port").
	///   - status (int): Current device status (DeviceStatus); optional.
	///
	/// The following generic device types are currently defined:
	///   - io.macchina.accelerometer (Accelerometer)
	///   - io.macchina.barcode (BarcodeReader)
	///   - io.macchina.gnss (GNSSSensor)
	///   - io.macchina.gyroscope (Gyroscope)
	///   - io.macchina.io (IO)
	///   - io.macchina.led (LED)
	///   - io.macchina.magnetometer (Magnetometer)
	///   - io.macchina.rotary (RotaryEncoder)
	///   - io.macchina.sensor (Sensor)
	///   - io.macchina.boolean (BooleanSensor)
	///   - io.macchina.counter (Counter)
	///   - io.macchina.serial (SerialDevice)
	///   - io.macchina.switch (Switch)
	///   - io.macchina.trigger (Trigger)
	///
	/// A device can also have an arbitrary number of sub devices, making
	/// complex device tree structures possible.
	///
	/// Every sub device is itself a subclass of Device. Sub devices
	/// are referenced by their service name only. All sub devices
	/// are therefore registered in the ServiceRegistry.
{
public:
	typedef Poco::AutoPtr<DeviceRemoteObject> Ptr;

	DeviceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Device> pServiceObject);
		/// Creates a DeviceRemoteObject.

	virtual ~DeviceRemoteObject();
		/// Destroys the DeviceRemoteObject.

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
	void event__statusChanged(const IoT::Devices::DeviceStatusChange& data);

private:
	Poco::SharedPtr<IoT::Devices::Device> _pServiceObject;
};


inline bool DeviceRemoteObject::getFeature(const std::string& name) const
{
	return _pServiceObject->getFeature(name);
}


inline bool DeviceRemoteObject::getPropertyBool(const std::string& name) const
{
	return _pServiceObject->getPropertyBool(name);
}


inline double DeviceRemoteObject::getPropertyDouble(const std::string& name) const
{
	return _pServiceObject->getPropertyDouble(name);
}


inline int DeviceRemoteObject::getPropertyInt(const std::string& name) const
{
	return _pServiceObject->getPropertyInt(name);
}


inline std::string DeviceRemoteObject::getPropertyString(const std::string& name) const
{
	return _pServiceObject->getPropertyString(name);
}


inline bool DeviceRemoteObject::hasFeature(const std::string& name) const
{
	return _pServiceObject->hasFeature(name);
}


inline bool DeviceRemoteObject::hasProperty(const std::string& name) const
{
	return _pServiceObject->hasProperty(name);
}


inline const Poco::RemotingNG::Identifiable::TypeId& DeviceRemoteObject::remoting__typeId() const
{
	return IDevice::remoting__typeId();
}


inline void DeviceRemoteObject::setFeature(const std::string& name, bool enable)
{
	_pServiceObject->setFeature(name, enable);
}


inline void DeviceRemoteObject::setPropertyBool(const std::string& name, bool value)
{
	_pServiceObject->setPropertyBool(name, value);
}


inline void DeviceRemoteObject::setPropertyDouble(const std::string& name, double value)
{
	_pServiceObject->setPropertyDouble(name, value);
}


inline void DeviceRemoteObject::setPropertyInt(const std::string& name, int value)
{
	_pServiceObject->setPropertyInt(name, value);
}


inline void DeviceRemoteObject::setPropertyString(const std::string& name, const std::string& value)
{
	_pServiceObject->setPropertyString(name, value);
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_DeviceRemoteObject_INCLUDED

