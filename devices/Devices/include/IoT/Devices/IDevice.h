//
// IDevice.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IDevice
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IDevice_INCLUDED
#define IoT_Devices_IDevice_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IDevice: public Poco::OSP::Service
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
{
public:
	typedef Poco::AutoPtr<IDevice> Ptr;

	IDevice();
		/// Creates a IDevice.

	virtual ~IDevice();
		/// Destroys the IDevice.

	virtual bool getFeature(const std::string& name) const = 0;
		/// Returns true if the feature with the given name
		/// is enabled, or false otherwise.

	virtual bool getPropertyBool(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual double getPropertyDouble(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual int getPropertyInt(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual std::string getPropertyString(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual bool hasFeature(const std::string& name) const = 0;
		/// Returns true if the feature with the given name
		/// is known, or false otherwise.

	virtual bool hasProperty(const std::string& name) const = 0;
		/// Returns true if the property with the given name
		/// exists, or false otherwise.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void setFeature(const std::string& name, bool enable) = 0;
		/// Enables or disables the feature with the given name.
		///
		/// Which features are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyBool(const std::string& name, bool value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyDouble(const std::string& name, double value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyInt(const std::string& name, int value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual void setPropertyString(const std::string& name, const std::string& value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const DeviceStatusChange > statusChanged;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IDevice_INCLUDED

