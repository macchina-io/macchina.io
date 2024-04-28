//
// Peripheral.h
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  Peripheral
//
// Definition of the Peripheral class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_Peripheral_INCLUDED
#define IoT_BtLE_Peripheral_INCLUDED


#include "IoT/BtLE/BtLE.h"
#include "IoT/BtLE/GATTClient.h"
#include "Poco/UUID.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include <vector>


namespace IoT {
namespace BtLE {


using Handle = Poco::UInt16;

//@ serialize
struct Characteristic
{
	Poco::UInt16 properties;
	Handle valueHandle;
};


//@ serialize
struct Indication
{
	Indication():
		handle(0)
	{
	}

	Handle handle;
	std::vector<char> data;
};


//@ serialize
struct Notification
{
	Notification():
		handle(0)
	{
	}

	Handle handle;
	std::vector<char> data;
};


//@ remote
class IoTBtLE_API Peripheral
	/// This class provides a high-level interface to a Bt LE peripheral
	/// device using the Bt Generic Attribute Profile (GATT).
{
public:
	using Ptr = Poco::SharedPtr<Peripheral>;

	Poco::BasicEvent<void> connected;
		/// Fired when a connection with the peripheral has been established.

	Poco::BasicEvent<void> disconnected;
		/// Fired when the connection with the peripheral has been disconnected.

	Poco::BasicEvent<const std::string> error;
		/// Fired when the connection attempt with the peripheral has failed.
		/// The event argument contains more information about the error.

	Poco::BasicEvent<const Indication> indicationReceived;
		/// Fired when an Indication has been received from the peripheral.

	Poco::BasicEvent<const Notification> notificationReceived;
		/// Fired when a Notification has been received from the peripheral.

	virtual void connect() = 0;
		/// Connects to the Bt LE peripheral.
		///
		/// Waits for successful connection or error.

	virtual void connectAsync() = 0;
		/// Connects to the Bt LE peripheral.
		///
		/// Successful connection or error will be reported through connected
		/// and error events.

	virtual void disconnect() = 0;
		/// Disconnects from the Bt LE peripheral.

	virtual bool isConnected() const = 0;
		/// Returns true if the device is connected.

	virtual std::string address() const = 0;
		/// Returns the address of the device.

	virtual std::vector<Poco::UUID> services() = 0;
		/// Returns a vector containing the UUIDs of all available services.

	virtual Poco::UUID serviceUUIDForAssignedNumber(Poco::UInt32 assignedNumber) = 0;
		/// Returns the UUID of the service with the given 32-bit assigned number,
		/// or null UUID if no such service is available.

	virtual std::vector<Poco::UUID> characteristics(const Poco::UUID& serviceUUID) = 0;
		/// Returns a vector containing the UUIDs of all available characteristics
		/// of the service identified by the given serviceUUID.

	virtual Characteristic characteristic(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID) = 0;
		/// Returns the properties and handle for accessing the value of the given characteristic.

	virtual Characteristic characteristicForAssignedNumber(const Poco::UUID& serviceUUID, Poco::UInt32 assignedNumber) = 0;
		/// Returns the properties and handle for accessing the value of the given characteristic.

	virtual Handle handleForDescriptor(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID, const Poco::UUID& descriptorUUID) = 0;
		/// Returns the handle with the given descriptor UUID for given characteristic and service.

	virtual Poco::UInt8 readUInt8(Handle valueHandle) = 0;
		/// Reads an unsigned byte value from the given value handle.

	virtual Poco::Int8 readInt8(Handle valueHandle) = 0;
		/// Reads a signed byte value from the given value handle.

	virtual Poco::UInt16 readUInt16(Handle valueHandle) = 0;
		/// Reads an unsigned 16-bit integer value (little endian) from the given value handle.

	virtual Poco::Int16 readInt16(Handle valueHandle) = 0;
		/// Reads a signed 16-bit integer value (little endian) from the given value handle.

	virtual Poco::UInt32 readUInt32(Handle valueHandle) = 0;
		/// Reads an unsigned 32-bit integer value (little endian) from the given value handle.

	virtual Poco::Int32 readInt32(Handle valueHandle) = 0;
		/// Reads a signed 32-bit integer value (little endian) from the given value handle.

	virtual Poco::UInt64 readUInt64(Handle valueHandle) = 0;
		/// Reads an unsigned 64-bit integer value (little endian) from the given value handle.

	virtual Poco::Int64 readInt64(Handle valueHandle) = 0;
		/// Reads a signed 64-bit integer value (little endian) from the given value handle.

	virtual float readFloat(Handle valueHandle) = 0;
		/// Reads a 32-bit float value (little endian) from the given value handle.

	virtual double readDouble(Handle valueHandle) = 0;
		/// Reads a 64-bit double value (little endian) from the given value handle.

	virtual std::string readString(Handle valueHandle) = 0;
		/// Reads a raw byte string from the given value handle.

	virtual std::string readString0(Handle valueHandle) = 0;
		/// Reads a 0-terminated character string from the given value handle.

	virtual std::vector<char> readBytes(Handle valueHandle) = 0;
		/// Reads a raw byte string from the given value handle.

	virtual void writeUInt8(Handle valueHandle, Poco::UInt8 value, bool withResponse) = 0;
		/// Writes an unsigned byte value to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt8(Handle valueHandle, Poco::Int8 value, bool withResponse) = 0;
		/// Writes a signed byte value to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt16(Handle valueHandle, Poco::UInt16 value, bool withResponse) = 0;
		/// Writes an unsigned 16-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt16(Handle valueHandle, Poco::Int16 value, bool withResponse) = 0;
		/// Writes a signed 16-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt32(Handle valueHandle, Poco::UInt32 value, bool withResponse) = 0;
		/// Writes an unsigned 32-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt32(Handle valueHandle, Poco::Int32 value, bool withResponse) = 0;
		/// Writes a signed 32-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt64(Handle valueHandle, Poco::UInt64 value, bool withResponse) = 0;
		/// Writes an unsigned 32-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt64(Handle valueHandle, Poco::Int64 value, bool withResponse) = 0;
		/// Writes a signed 32-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeFloat(Handle valueHandle, float value, bool withResponse) = 0;
		/// Writes a signed 32-bit float value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeDouble(Handle valueHandle, double value, bool withResponse) = 0;
		/// Writes a signed 64-bit double value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeString(Handle valueHandle, const std::string& value, bool withResponse) = 0;
		/// Writes a raw byte string to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeBytes(Handle valueHandle, const std::vector<char>& value, bool withResponse) = 0;
		/// Writes a raw byte string to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual std::string deviceName() = 0;
		/// Returns the peripheral's device name obtained from the Generic Access Profile.

	virtual std::string manufacturerName() = 0;
		/// Returns the peripheral's manufacturer name obtained from the Device Information service.

	virtual std::string modelNumber() = 0;
		/// Returns the peripheral's model number string obtained from the Device Information service.

	virtual std::string serialNumber() = 0;
		/// Returns the peripheral's serial number string obtained from the Device Information service.

	virtual std::string hardwareRevision() = 0;
		/// Returns the peripheral's hardware revision string obtained from the Device Information service.

	virtual std::string firmwareRevision() = 0;
		/// Returns the peripheral's firmware revision string obtained from the Device Information service.

	virtual std::string softwareRevision() = 0;
		/// Returns the peripheral's software revision string obtained from the Device Information service.

	virtual Poco::UUID expandUUID(Poco::UInt32 uuid) = 0;
		/// Expands the given 16-bit or 32-bit UUID to a full UUID.

	virtual ~Peripheral();
		/// Destroys the Peripheral.
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_Peripheral_INCLUDED
