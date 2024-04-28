//
// PeripheralRemoteObject.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_PeripheralRemoteObject_INCLUDED
#define IoT_BtLE_PeripheralRemoteObject_INCLUDED


#include "IoT/BtLE/IPeripheral.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace BtLE {


class PeripheralRemoteObject: public IoT::BtLE::IPeripheral, public Poco::RemotingNG::RemoteObject
	/// This class provides a high-level interface to a Bt LE peripheral
	/// device using the Bt Generic Attribute Profile (GATT).
{
public:
	using Ptr = Poco::AutoPtr<PeripheralRemoteObject>;

	PeripheralRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::BtLE::Peripheral> pServiceObject);
		/// Creates a PeripheralRemoteObject.

	virtual ~PeripheralRemoteObject();
		/// Destroys the PeripheralRemoteObject.

	virtual std::string address() const;
		/// Returns the address of the device.

	IoT::BtLE::Characteristic characteristic(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID);
		/// Returns the properties and handle for accessing the value of the given characteristic.

	IoT::BtLE::Characteristic characteristicForAssignedNumber(const Poco::UUID& serviceUUID, Poco::UInt32 assignedNumber);
		/// Returns the properties and handle for accessing the value of the given characteristic.

	std::vector<Poco::UUID> characteristics(const Poco::UUID& serviceUUID);
		/// Returns a vector containing the UUIDs of all available characteristics
		/// of the service identified by the given serviceUUID.

	virtual void connect();
		/// Connects to the Bt LE peripheral.
		///
		/// Waits for successful connection or error.

	virtual void connectAsync();
		/// Connects to the Bt LE peripheral.
		///
		/// Successful connection or error will be reported through connected
		/// and error events.

	virtual std::string deviceName();
		/// Returns the peripheral's device name obtained from the Generic Access Profile.

	virtual void disconnect();
		/// Disconnects from the Bt LE peripheral.

	virtual Poco::UUID expandUUID(Poco::UInt32 uuid);
		/// Expands the given 16-bit or 32-bit UUID to a full UUID.

	virtual std::string firmwareRevision();
		/// Returns the peripheral's firmware revision string obtained from the Device Information service.

	Poco::UInt16 handleForDescriptor(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID, const Poco::UUID& descriptorUUID);
		/// Returns the handle with the given descriptor UUID for given characteristic and service.

	virtual std::string hardwareRevision();
		/// Returns the peripheral's hardware revision string obtained from the Device Information service.

	virtual bool isConnected() const;
		/// Returns true if the device is connected.

	virtual std::string manufacturerName();
		/// Returns the peripheral's manufacturer name obtained from the Device Information service.

	virtual std::string modelNumber();
		/// Returns the peripheral's model number string obtained from the Device Information service.

	std::vector<char> readBytes(Poco::UInt16 valueHandle);
		/// Reads a raw byte string from the given value handle.

	virtual double readDouble(Poco::UInt16 valueHandle);
		/// Reads a 64-bit double value (little endian) from the given value handle.

	virtual float readFloat(Poco::UInt16 valueHandle);
		/// Reads a 32-bit float value (little endian) from the given value handle.

	virtual Poco::Int16 readInt16(Poco::UInt16 valueHandle);
		/// Reads a signed 16-bit integer value (little endian) from the given value handle.

	virtual Poco::Int32 readInt32(Poco::UInt16 valueHandle);
		/// Reads a signed 32-bit integer value (little endian) from the given value handle.

	virtual Poco::Int64 readInt64(Poco::UInt16 valueHandle);
		/// Reads a signed 64-bit integer value (little endian) from the given value handle.

	virtual Poco::Int8 readInt8(Poco::UInt16 valueHandle);
		/// Reads a signed byte value from the given value handle.

	virtual std::string readString(Poco::UInt16 valueHandle);
		/// Reads a raw byte string from the given value handle.

	virtual std::string readString0(Poco::UInt16 valueHandle);
		/// Reads a 0-terminated character string from the given value handle.

	virtual Poco::UInt16 readUInt16(Poco::UInt16 valueHandle);
		/// Reads an unsigned 16-bit integer value (little endian) from the given value handle.

	virtual Poco::UInt32 readUInt32(Poco::UInt16 valueHandle);
		/// Reads an unsigned 32-bit integer value (little endian) from the given value handle.

	virtual Poco::UInt64 readUInt64(Poco::UInt16 valueHandle);
		/// Reads an unsigned 64-bit integer value (little endian) from the given value handle.

	virtual Poco::UInt8 readUInt8(Poco::UInt16 valueHandle);
		/// Reads an unsigned byte value from the given value handle.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual std::string serialNumber();
		/// Returns the peripheral's serial number string obtained from the Device Information service.

	virtual Poco::UUID serviceUUIDForAssignedNumber(Poco::UInt32 assignedNumber);
		/// Returns the UUID of the service with the given 32-bit assigned number,
		/// or null UUID if no such service is available.

	std::vector<Poco::UUID> services();
		/// Returns a vector containing the UUIDs of all available services.

	virtual std::string softwareRevision();
		/// Returns the peripheral's software revision string obtained from the Device Information service.

	virtual void writeBytes(Poco::UInt16 valueHandle, const std::vector<char>& value, bool withResponse);
		/// Writes a raw byte string to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeDouble(Poco::UInt16 valueHandle, double value, bool withResponse);
		/// Writes a signed 64-bit double value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeFloat(Poco::UInt16 valueHandle, float value, bool withResponse);
		/// Writes a signed 32-bit float value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt16(Poco::UInt16 valueHandle, Poco::Int16 value, bool withResponse);
		/// Writes a signed 16-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt32(Poco::UInt16 valueHandle, Poco::Int32 value, bool withResponse);
		/// Writes a signed 32-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt64(Poco::UInt16 valueHandle, Poco::Int64 value, bool withResponse);
		/// Writes a signed 32-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeInt8(Poco::UInt16 valueHandle, Poco::Int8 value, bool withResponse);
		/// Writes a signed byte value to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeString(Poco::UInt16 valueHandle, const std::string& value, bool withResponse);
		/// Writes a raw byte string to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt16(Poco::UInt16 valueHandle, Poco::UInt16 value, bool withResponse);
		/// Writes an unsigned 16-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse);
		/// Writes an unsigned 32-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt64(Poco::UInt16 valueHandle, Poco::UInt64 value, bool withResponse);
		/// Writes an unsigned 32-bit integer value (little endian) to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

	virtual void writeUInt8(Poco::UInt16 valueHandle, Poco::UInt8 value, bool withResponse);
		/// Writes an unsigned byte value to the given value handle.
		///
		/// If withResponse is false, uses a WriteWithoutResponse operation,
		/// otherwise a Write operation.

protected:
	void event__connected();

	void event__disconnected();

	void event__error(const std::string& data);

	void event__indicationReceived(const IoT::BtLE::Indication& data);

	void event__notificationReceived(const IoT::BtLE::Notification& data);

private:
	Poco::SharedPtr<IoT::BtLE::Peripheral> _pServiceObject;
};


inline std::string PeripheralRemoteObject::address() const
{
	return _pServiceObject->address();
}


inline IoT::BtLE::Characteristic PeripheralRemoteObject::characteristic(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID)
{
	return _pServiceObject->characteristic(serviceUUID, characteristicUUID);
}


inline IoT::BtLE::Characteristic PeripheralRemoteObject::characteristicForAssignedNumber(const Poco::UUID& serviceUUID, Poco::UInt32 assignedNumber)
{
	return _pServiceObject->characteristicForAssignedNumber(serviceUUID, assignedNumber);
}


inline std::vector<Poco::UUID> PeripheralRemoteObject::characteristics(const Poco::UUID& serviceUUID)
{
	return _pServiceObject->characteristics(serviceUUID);
}


inline void PeripheralRemoteObject::connect()
{
	_pServiceObject->connect();
}


inline void PeripheralRemoteObject::connectAsync()
{
	_pServiceObject->connectAsync();
}


inline std::string PeripheralRemoteObject::deviceName()
{
	return _pServiceObject->deviceName();
}


inline void PeripheralRemoteObject::disconnect()
{
	_pServiceObject->disconnect();
}


inline Poco::UUID PeripheralRemoteObject::expandUUID(Poco::UInt32 uuid)
{
	return _pServiceObject->expandUUID(uuid);
}


inline std::string PeripheralRemoteObject::firmwareRevision()
{
	return _pServiceObject->firmwareRevision();
}


inline Poco::UInt16 PeripheralRemoteObject::handleForDescriptor(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID, const Poco::UUID& descriptorUUID)
{
	return _pServiceObject->handleForDescriptor(serviceUUID, characteristicUUID, descriptorUUID);
}


inline std::string PeripheralRemoteObject::hardwareRevision()
{
	return _pServiceObject->hardwareRevision();
}


inline bool PeripheralRemoteObject::isConnected() const
{
	return _pServiceObject->isConnected();
}


inline std::string PeripheralRemoteObject::manufacturerName()
{
	return _pServiceObject->manufacturerName();
}


inline std::string PeripheralRemoteObject::modelNumber()
{
	return _pServiceObject->modelNumber();
}


inline std::vector<char> PeripheralRemoteObject::readBytes(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readBytes(valueHandle);
}


inline double PeripheralRemoteObject::readDouble(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readDouble(valueHandle);
}


inline float PeripheralRemoteObject::readFloat(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readFloat(valueHandle);
}


inline Poco::Int16 PeripheralRemoteObject::readInt16(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readInt16(valueHandle);
}


inline Poco::Int32 PeripheralRemoteObject::readInt32(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readInt32(valueHandle);
}


inline Poco::Int64 PeripheralRemoteObject::readInt64(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readInt64(valueHandle);
}


inline Poco::Int8 PeripheralRemoteObject::readInt8(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readInt8(valueHandle);
}


inline std::string PeripheralRemoteObject::readString(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readString(valueHandle);
}


inline std::string PeripheralRemoteObject::readString0(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readString0(valueHandle);
}


inline Poco::UInt16 PeripheralRemoteObject::readUInt16(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readUInt16(valueHandle);
}


inline Poco::UInt32 PeripheralRemoteObject::readUInt32(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readUInt32(valueHandle);
}


inline Poco::UInt64 PeripheralRemoteObject::readUInt64(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readUInt64(valueHandle);
}


inline Poco::UInt8 PeripheralRemoteObject::readUInt8(Poco::UInt16 valueHandle)
{
	return _pServiceObject->readUInt8(valueHandle);
}


inline const Poco::RemotingNG::Identifiable::TypeId& PeripheralRemoteObject::remoting__typeId() const
{
	return IPeripheral::remoting__typeId();
}


inline std::string PeripheralRemoteObject::serialNumber()
{
	return _pServiceObject->serialNumber();
}


inline Poco::UUID PeripheralRemoteObject::serviceUUIDForAssignedNumber(Poco::UInt32 assignedNumber)
{
	return _pServiceObject->serviceUUIDForAssignedNumber(assignedNumber);
}


inline std::vector<Poco::UUID> PeripheralRemoteObject::services()
{
	return _pServiceObject->services();
}


inline std::string PeripheralRemoteObject::softwareRevision()
{
	return _pServiceObject->softwareRevision();
}


inline void PeripheralRemoteObject::writeBytes(Poco::UInt16 valueHandle, const std::vector<char>& value, bool withResponse)
{
	_pServiceObject->writeBytes(valueHandle, value, withResponse);
}


inline void PeripheralRemoteObject::writeDouble(Poco::UInt16 valueHandle, double value, bool withResponse)
{
	_pServiceObject->writeDouble(valueHandle, value, withResponse);
}


inline void PeripheralRemoteObject::writeFloat(Poco::UInt16 valueHandle, float value, bool withResponse)
{
	_pServiceObject->writeFloat(valueHandle, value, withResponse);
}


inline void PeripheralRemoteObject::writeInt16(Poco::UInt16 valueHandle, Poco::Int16 value, bool withResponse)
{
	_pServiceObject->writeInt16(valueHandle, value, withResponse);
}


inline void PeripheralRemoteObject::writeInt32(Poco::UInt16 valueHandle, Poco::Int32 value, bool withResponse)
{
	_pServiceObject->writeInt32(valueHandle, value, withResponse);
}


inline void PeripheralRemoteObject::writeInt64(Poco::UInt16 valueHandle, Poco::Int64 value, bool withResponse)
{
	_pServiceObject->writeInt64(valueHandle, value, withResponse);
}


inline void PeripheralRemoteObject::writeInt8(Poco::UInt16 valueHandle, Poco::Int8 value, bool withResponse)
{
	_pServiceObject->writeInt8(valueHandle, value, withResponse);
}


inline void PeripheralRemoteObject::writeString(Poco::UInt16 valueHandle, const std::string& value, bool withResponse)
{
	_pServiceObject->writeString(valueHandle, value, withResponse);
}


inline void PeripheralRemoteObject::writeUInt16(Poco::UInt16 valueHandle, Poco::UInt16 value, bool withResponse)
{
	_pServiceObject->writeUInt16(valueHandle, value, withResponse);
}


inline void PeripheralRemoteObject::writeUInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse)
{
	_pServiceObject->writeUInt32(valueHandle, value, withResponse);
}


inline void PeripheralRemoteObject::writeUInt64(Poco::UInt16 valueHandle, Poco::UInt64 value, bool withResponse)
{
	_pServiceObject->writeUInt64(valueHandle, value, withResponse);
}


inline void PeripheralRemoteObject::writeUInt8(Poco::UInt16 valueHandle, Poco::UInt8 value, bool withResponse)
{
	_pServiceObject->writeUInt8(valueHandle, value, withResponse);
}


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_PeripheralRemoteObject_INCLUDED

