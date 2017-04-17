//
// IPeripheral.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  IPeripheral
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_IPeripheral_INCLUDED
#define IoT_BtLE_IPeripheral_INCLUDED


#include "IoT/BtLE/Peripheral.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace BtLE {


class IPeripheral: public Poco::OSP::Service
	/// This class provides a high-level interface to a Bluetooth LE peripheral
	/// device using the Bluetooth Generic Attribute Profile (GATT).
{
public:
	typedef Poco::AutoPtr<IPeripheral> Ptr;

	IPeripheral();
		/// Creates a IPeripheral.

	virtual ~IPeripheral();
		/// Destroys the IPeripheral.

	virtual std::string address() const = 0;
		/// Returns the address of the device.

	virtual IoT::BtLE::Characteristic characteristic(const std::string& serviceUUID, const std::string& characteristicUUID) = 0;
		/// Returns the properties and handle for accessing the value of the given characteristic.

	virtual IoT::BtLE::Characteristic characteristicForAssignedNumber(const std::string& serviceUUID, Poco::UInt32 assignedNumber) = 0;
		/// Returns the properties and handle for accessing the value of the given characteristic.

	virtual std::vector < std::string > characteristics(const std::string& serviceUUID) = 0;
		/// Returns a vector containing the UUIDs of all available characteristics
		/// of the service identified by the given serviceUUID.

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

	virtual std::string firmwareRevision() = 0;
		/// Returns the peripheral's firmware revision string obtained from the Device Information service.

	virtual Poco::UInt16 handleForDescriptor(const std::string& serviceUUID, const std::string& descriptorUUID) = 0;
		/// Returns the handle with the given descriptor UUID for the service with the given serviceUUID.

	virtual std::string hardwareRevision() = 0;
		/// Returns the peripheral's hardware revision string obtained from the Device Information service.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual bool isConnected() const = 0;
		/// Returns true if the device is connected.

	virtual std::string manufacturerName() = 0;
		/// Returns the peripheral's manufacturer name obtained from the Device Information service.

	virtual std::string modelNumber() = 0;
		/// Returns the peripheral's model number string obtained from the Device Information service.

	virtual std::vector < char > readBytes(Poco::UInt16 valueHandle) = 0;
		/// Reads a raw byte string from the given value handle.	

	virtual Poco::Int16 readInt16(Poco::UInt16 valueHandle) = 0;
		/// Reads a signed 16-bit integer value from the given value handle.

	virtual Poco::Int32 readInt32(Poco::UInt16 valueHandle) = 0;
		/// Reads a signed 32-bit integer value from the given value handle.

	virtual Poco::Int8 readInt8(Poco::UInt16 valueHandle) = 0;
		/// Reads a signed byte value from the given value handle.

	virtual std::string readString(Poco::UInt16 valueHandle) = 0;
		/// Reads a raw byte string from the given value handle.	

	virtual Poco::UInt16 readUInt16(Poco::UInt16 valueHandle) = 0;
		/// Reads an unsigned 16-bit integer value from the given value handle.

	virtual Poco::UInt32 readUInt32(Poco::UInt16 valueHandle) = 0;
		/// Reads an unsigned 32-bit integer value from the given value handle.

	virtual Poco::UInt8 readUInt8(Poco::UInt16 valueHandle) = 0;
		/// Reads an unsigned byte value from the given value handle.

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

	virtual std::string serialNumber() = 0;
		/// Returns the peripheral's serial number string obtained from the Device Information service.

	virtual std::string serviceUUIDForAssignedNumber(Poco::UInt32 assignedNumber) = 0;
		/// Returns the UUID of the service with the given 32-bit assigned number, 
		/// or an empty string if no such service is available.

	virtual std::vector < std::string > services() = 0;
		/// Returns a vector containing the UUIDs of all available services.

	virtual std::string softwareRevision() = 0;
		/// Returns the peripheral's software revision string obtained from the Device Information service.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual void writeBytes(Poco::UInt16 valueHandle, const std::vector < char >& value, bool withResponse) = 0;
		/// Writes a raw byte string to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt16(Poco::UInt16 valueHandle, Poco::Int16 value, bool withResponse) = 0;
		/// Writes a signed 16-bit integer value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse) = 0;
		/// Writes a signed 32-bit integer value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt8(Poco::UInt16 valueHandle, Poco::Int8 value, bool withResponse) = 0;
		/// Writes a signed byte value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeString(Poco::UInt16 valueHandle, const std::string& value, bool withResponse) = 0;
		/// Writes a raw byte string to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt16(Poco::UInt16 valueHandle, Poco::UInt16 value, bool withResponse) = 0;
		/// Writes an unsigned 16-bit integer value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse) = 0;
		/// Writes an unsigned 32-bit integer value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt8(Poco::UInt16 valueHandle, Poco::UInt8 value, bool withResponse) = 0;
		/// Writes an unsigned byte value to the given value handle.
		/// 
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	Poco::BasicEvent < void > connected;
	Poco::BasicEvent < void > disconnected;
	Poco::BasicEvent < const std::string > error;
	Poco::BasicEvent < const Indication > indicationReceived;
	Poco::BasicEvent < const Notification > notificationReceived;
};


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_IPeripheral_INCLUDED

