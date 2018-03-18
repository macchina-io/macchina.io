//
// Device.h
//
// Library: IoT/Devices
// Package: Devices
// Module:  Device
//
// Definition of the Device interface.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Device_INCLUDED
#define IoT_Devices_Device_INCLUDED


#include "IoT/Devices/Devices.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


enum DeviceStatus
	/// Current operating status of a device or sensor.
{
	DEVICE_STATUS_UNKNOWN  = 0, /// The status is unknown.
	DEVICE_STATUS_DISABLED = 1, /// The device has been disabled.
	DEVICE_STATUS_ENABLED  = 2, /// The device has been enabled, but is not ready yet.
	DEVICE_STATUS_READY    = 3, /// The device is functioning properly and providing data.
	DEVICE_STATUS_ERROR    = 4  /// The device is not functioning properly.
};


//@ serialize
struct DeviceStatusChange
	/// Event argument for statusChanged event.
{
	DeviceStatus previous; /// Previous (old) device status
	DeviceStatus current;  /// Current (new) device status
};


//@ remote
class IoTDevices_API Device
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
	Poco::BasicEvent<const DeviceStatusChange> statusChanged;
		/// Fired when the status of the device changes.
		///
		/// Implementing this event is optional.
		/// A device implementation should document if this event
		/// is supported.

	Device();
		/// Creates the Device.

	virtual ~Device();
		/// Destroys the Device.

	virtual void setPropertyString(const std::string& name, const std::string& value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual std::string getPropertyString(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual void setPropertyInt(const std::string& name, int value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual int getPropertyInt(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual void setPropertyDouble(const std::string& name, double value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual double getPropertyDouble(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual void setPropertyBool(const std::string& name, bool value) = 0;
		/// Sets a device property.
		///
		/// Which properties are supported is defined by the
		/// actual device implementation.

	virtual bool getPropertyBool(const std::string& name) const = 0;
		/// Returns the value of the device property with
		/// the given name.
		///
		/// Throws a Poco::NotFoundException if the property
		/// with the given name is unknown.

	virtual bool hasProperty(const std::string& name) const = 0;
		/// Returns true if the property with the given name
		/// exists, or false otherwise.

	virtual void setFeature(const std::string& name, bool enable) = 0;
		/// Enables or disables the feature with the given name.
		///
		/// Which features are supported is defined by the
		/// actual device implementation.

	virtual bool getFeature(const std::string& name) const = 0;
		/// Returns true if the feature with the given name
		/// is enabled, or false otherwise.

	virtual bool hasFeature(const std::string& name) const = 0;
		/// Returns true if the feature with the given name
		/// is known, or false otherwise.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Device_INCLUDED
