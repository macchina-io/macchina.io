//
// Peripheral.h
//
// $Id$
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
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_Peripheral_INCLUDED
#define IoT_BtLE_Peripheral_INCLUDED


#include "IoT/BtLE/BtLE.h"
#include "IoT/BtLE/GATTClient.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include <vector>


namespace IoT {
namespace BtLE {


//@ serialize
struct Characteristic
{
	Poco::UInt16 properties;
	Poco::UInt16 valueHandle;
};


//@ serialize
struct Indication
{
	Indication():
		handle(0)
	{
	}
	
	Poco::UInt16 handle;
	std::string data;
};


//@ serialize
struct Notification
{
	Notification():
		handle(0)
	{
	}
	
	Poco::UInt16 handle;
	std::string data;
};


//@ remote
class IoTBtLE_API Peripheral
	/// This class provides a high-level interface to a Bluetooth LE peripheral
	/// device using the Bluetooth Generic Attribute Profile (GATT).
{
public:
	typedef Poco::SharedPtr<Peripheral> Ptr;

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
		/// Connects to the Bluetooth LE peripheral.
		///
		/// Waits for successful connection or error.

	virtual void connectAsync() = 0;
		/// Connects to the Bluetooth LE peripheral.
		///
		/// Successful connection or error will be reported through connected 
		/// and error events.
		
	virtual void disconnect() = 0;
		/// Disconnects from the Bluetooth LE peripheral.
		
	virtual bool isConnected() const = 0;
		/// Returns true if the device is connected.
	
	virtual std::string address() const = 0;
		/// Returns the address of the device.
		
	virtual std::vector<std::string> services() = 0;
		/// Returns a vector containing the UUIDs of all available services.

	virtual std::string serviceUUIDForAssignedNumber(Poco::UInt32 assignedNumber) = 0;
		/// Returns the UUID of the service with the given 32-bit assigned number, 
		/// or an empty string if no such service is available.

	virtual std::vector<std::string> characteristics(const std::string& serviceUUID) = 0;
		/// Returns a vector containing the UUIDs of all available characteristics
		/// of the service identified by the given serviceUUID.
		
	virtual Characteristic characteristic(const std::string& serviceUUID, const std::string& characteristicUUID) = 0;
		/// Returns the properties and handle for accessing the value of the given characteristic.

	virtual Characteristic characteristicForAssignedNumber(const std::string& serviceUUID, Poco::UInt32 assignedNumber) = 0;
		/// Returns the properties and handle for accessing the value of the given characteristic.

	virtual Poco::UInt16 handleForDescriptor(const std::string& serviceUUID, const std::string& descriptorUUID) = 0;
		/// Returns the handle with the given descriptor UUID for the service with the given serviceUUID.

	virtual Poco::UInt8 readUInt8(Poco::UInt16 valueHandle) = 0;
		/// Reads an unsigned byte value from the given value handle.

	virtual Poco::Int8 readInt8(Poco::UInt16 valueHandle) = 0;	
		/// Reads a signed byte value from the given value handle.

	virtual Poco::UInt16 readUInt16(Poco::UInt16 valueHandle) = 0;
		/// Reads an unsigned 16-bit integer value from the given value handle.

	virtual Poco::Int16 readInt16(Poco::UInt16 valueHandle) = 0;	
		/// Reads a signed 16-bit integer value from the given value handle.

	virtual Poco::UInt32 readUInt32(Poco::UInt16 valueHandle) = 0;	
		/// Reads an unsigned 32-bit integer value from the given value handle.

	virtual Poco::Int32 readInt32(Poco::UInt16 valueHandle) = 0;	
		/// Reads a signed 32-bit integer value from the given value handle.

	virtual std::string readString(Poco::UInt16 valueHandle) = 0;
		/// Reads a raw byte string from the given value handle.	

	virtual std::vector<char> readBytes(Poco::UInt16 valueHandle) = 0;
		/// Reads a raw byte string from the given value handle.	

	virtual void writeUInt8(Poco::UInt16 valueHandle, Poco::UInt8 value, bool withResponse) = 0;
		/// Writes an unsigned byte value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt8(Poco::UInt16 valueHandle, Poco::Int8 value, bool withResponse) = 0;
		/// Writes a signed byte value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt16(Poco::UInt16 valueHandle, Poco::UInt16 value, bool withResponse) = 0;
		/// Writes an unsigned 16-bit integer value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt16(Poco::UInt16 valueHandle, Poco::Int16 value, bool withResponse) = 0;
		/// Writes a signed 16-bit integer value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse) = 0;
		/// Writes an unsigned 32-bit integer value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse) = 0;
		/// Writes a signed 32-bit integer value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeString(Poco::UInt16 valueHandle, const std::string& value, bool withResponse) = 0;
		/// Writes a raw byte string to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeBytes(Poco::UInt16 valueHandle, const std::vector<char>& value, bool withResponse) = 0;
		/// Writes a raw byte string to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

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
	
	virtual ~Peripheral();
		/// Destroys the Peripheral.
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_Peripheral_INCLUDED
