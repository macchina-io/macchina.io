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
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
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
	/// This class provides a high-level interface to a Bt LE peripheral
	/// device using the Bt Generic Attribute Profile (GATT).
{
public:
	using Ptr = Poco::AutoPtr<IPeripheral>;

	IPeripheral();
		/// Creates a IPeripheral.

	virtual ~IPeripheral();
		/// Destroys the IPeripheral.

	virtual std::string address() const = 0;
		/// Returns the address of the device.

	virtual IoT::BtLE::Characteristic characteristic(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID) = 0;
		/// Returns the properties and handle for accessing the value of the given characteristic.

	virtual IoT::BtLE::Characteristic characteristicForAssignedNumber(const Poco::UUID& serviceUUID, Poco::UInt32 assignedNumber) = 0;
		/// Returns the properties and handle for accessing the value of the given characteristic.

	virtual std::vector<Poco::UUID> characteristics(const Poco::UUID& serviceUUID) = 0;
		/// Returns a vector containing the UUIDs of all available characteristics
		/// of the service identified by the given serviceUUID.

	virtual void connect() = 0;
		/// Connects to the Bt LE peripheral.
		///
		/// Waits for successful connection or error.

	virtual void connectAsync() = 0;
		/// Connects to the Bt LE peripheral.
		///
		/// Successful connection or error will be reported through connected
		/// and error events.

	virtual std::string deviceName() = 0;
		/// Returns the peripheral's device name obtained from the Generic Access Profile.

	virtual void disconnect() = 0;
		/// Disconnects from the Bt LE peripheral.

	virtual Poco::UUID expandUUID(Poco::UInt32 uuid) = 0;
		/// Expands the given 16-bit or 32-bit UUID to a full UUID.

	virtual std::string firmwareRevision() = 0;
		/// Returns the peripheral's firmware revision string obtained from the Device Information service.

	virtual Poco::UInt16 handleForDescriptor(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID, const Poco::UUID& descriptorUUID) = 0;
		/// Returns the handle with the given descriptor UUID for given characteristic and service.

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

	virtual std::vector<char> readBytes(Poco::UInt16 valueHandle) = 0;
		/// Reads a raw byte string from the given value handle.

	virtual double readDouble(Poco::UInt16 valueHandle) = 0;
		/// Reads a 64-bit double value (little endian) from the given value handle.

	virtual float readFloat(Poco::UInt16 valueHandle) = 0;
		/// Reads a 32-bit float value (little endian) from the given value handle.

	virtual Poco::Int16 readInt16(Poco::UInt16 valueHandle) = 0;
		/// Reads a signed 16-bit integer value (little endian) from the given value handle.

	virtual Poco::Int32 readInt32(Poco::UInt16 valueHandle) = 0;
		/// Reads a signed 32-bit integer value (little endian) from the given value handle.

	virtual Poco::Int64 readInt64(Poco::UInt16 valueHandle) = 0;
		/// Reads a signed 64-bit integer value (little endian) from the given value handle.

	virtual Poco::Int8 readInt8(Poco::UInt16 valueHandle) = 0;
		/// Reads a signed byte value from the given value handle.

	virtual std::string readString(Poco::UInt16 valueHandle) = 0;
		/// Reads a raw byte string from the given value handle.

	virtual std::string readString0(Poco::UInt16 valueHandle) = 0;
		/// Reads a 0-terminated character string from the given value handle.

	virtual Poco::UInt16 readUInt16(Poco::UInt16 valueHandle) = 0;
		/// Reads an unsigned 16-bit integer value (little endian) from the given value handle.

	virtual Poco::UInt32 readUInt32(Poco::UInt16 valueHandle) = 0;
		/// Reads an unsigned 32-bit integer value (little endian) from the given value handle.

	virtual Poco::UInt64 readUInt64(Poco::UInt16 valueHandle) = 0;
		/// Reads an unsigned 64-bit integer value (little endian) from the given value handle.

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

	virtual Poco::UUID serviceUUIDForAssignedNumber(Poco::UInt32 assignedNumber) = 0;
		/// Returns the UUID of the service with the given 32-bit assigned number,
		/// or null UUID if no such service is available.

	virtual std::vector<Poco::UUID> services() = 0;
		/// Returns a vector containing the UUIDs of all available services.

	virtual std::string softwareRevision() = 0;
		/// Returns the peripheral's software revision string obtained from the Device Information service.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual void writeBytes(Poco::UInt16 valueHandle, const std::vector<char>& value, bool withResponse) = 0;
		/// Writes a raw byte string to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeDouble(Poco::UInt16 valueHandle, double value, bool withResponse) = 0;
		/// Writes a signed 64-bit double value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeFloat(Poco::UInt16 valueHandle, float value, bool withResponse) = 0;
		/// Writes a signed 32-bit float value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt16(Poco::UInt16 valueHandle, Poco::Int16 value, bool withResponse) = 0;
		/// Writes a signed 16-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt32(Poco::UInt16 valueHandle, Poco::Int32 value, bool withResponse) = 0;
		/// Writes a signed 32-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt64(Poco::UInt16 valueHandle, Poco::Int64 value, bool withResponse) = 0;
		/// Writes a signed 32-bit integer value (little endian) to the given value handle.
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
		/// Writes an unsigned 16-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse) = 0;
		/// Writes an unsigned 32-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt64(Poco::UInt16 valueHandle, Poco::UInt64 value, bool withResponse) = 0;
		/// Writes an unsigned 32-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt8(Poco::UInt16 valueHandle, Poco::UInt8 value, bool withResponse) = 0;
		/// Writes an unsigned byte value to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	Poco::BasicEvent<void> connected;
	Poco::BasicEvent<void> disconnected;
	Poco::BasicEvent<const std::string> error;
	Poco::BasicEvent<const IoT::BtLE::Indication> indicationReceived;
	Poco::BasicEvent<const IoT::BtLE::Notification> notificationReceived;
};


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_IPeripheral_INCLUDED

