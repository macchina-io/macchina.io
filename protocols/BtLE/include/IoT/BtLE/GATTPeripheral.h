//
// GATTPeripheral.h
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  GATTPeripheral
//
// Definition of the GATTPeripheral class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_GATTPeripheral_INCLUDED
#define IoT_BtLE_GATTPeripheral_INCLUDED


#include "IoT/BtLE/Peripheral.h"
#include "IoT/BtLE/GATTClient.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"
#include <vector>


namespace IoT {
namespace BtLE {


class IoTBtLE_API GATTPeripheral: public Peripheral
	/// This class provides a high-level interface to a Bt LE peripheral
	/// device using the Bt Generic Attribute Profile (GATT).
{
public:
	GATTPeripheral(const std::string& address, GATTClient::Ptr pGATTClient);
		/// Creates the GATTPeripheral.

	~GATTPeripheral();
		/// Destroys the GATTPeripheral.

	// Peripheral
	void connect();
	void connectAsync();
	void disconnect();
	bool isConnected() const;
	std::string address() const;
	std::vector<Poco::UUID> services();
	Poco::UUID serviceUUIDForAssignedNumber(Poco::UInt32 assignedNumber);
	std::vector<Poco::UUID> characteristics(const Poco::UUID& serviceUUID);
	Characteristic characteristic(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID);
	Characteristic characteristicForAssignedNumber(const Poco::UUID& serviceUUID, Poco::UInt32 assignedNumber);
	Handle handleForDescriptor(const Poco::UUID& serviceUUID, const Poco::UUID& characteristicUUID, const Poco::UUID& descriptorUUID);
	Poco::UInt8 readUInt8(Handle valueHandle);
	Poco::Int8 readInt8(Handle valueHandle);
	Poco::UInt16 readUInt16(Handle valueHandle);
	Poco::Int16 readInt16(Handle valueHandle);
	Poco::UInt32 readUInt32(Handle valueHandle);
	Poco::Int32 readInt32(Handle valueHandle);
	Poco::UInt64 readUInt64(Handle valueHandle);
	Poco::Int64 readInt64(Handle valueHandle);
	float readFloat(Handle valueHandle);
	double readDouble(Handle valueHandle);
	std::string readString(Handle valueHandle);
	std::string readString0(Handle valueHandle);
	std::vector<char> readBytes(Handle valueHandle);
	void writeUInt8(Handle valueHandle, Poco::UInt8 value, bool withResponse);
	void writeInt8(Handle valueHandle, Poco::Int8 value, bool withResponse);
	void writeUInt16(Handle valueHandle, Poco::UInt16 value, bool withResponse);
	void writeInt16(Handle valueHandle, Poco::Int16 value, bool withResponse);
	void writeUInt32(Handle valueHandle, Poco::UInt32 value, bool withResponse);
	void writeInt32(Handle valueHandle, Poco::Int32 value, bool withResponse);
	void writeUInt64(Handle valueHandle, Poco::UInt64 value, bool withResponse);
	void writeInt64(Handle valueHandle, Poco::Int64 value, bool withResponse);
	void writeFloat(Handle valueHandle, float value, bool withResponse);
	void writeDouble(Handle valueHandle, double value, bool withResponse);
	void writeString(Handle valueHandle, const std::string& value, bool withResponse);
	void writeBytes(Handle valueHandle, const std::vector<char>& value, bool withResponse);
	std::string deviceName();
	std::string manufacturerName();
	std::string modelNumber();
	std::string serialNumber();
	std::string hardwareRevision();
	std::string firmwareRevision();
	std::string softwareRevision();
	Poco::UUID expandUUID(Poco::UInt32 uuid);

protected:
	void onConnected();
	void onDisconnected();
	void onError(const std::string& error);
	void onIndication(const GATTClient::Indication& ind);
	void onNotification(const GATTClient::Notification& nf);
	std::string readDeviceInformation(Poco::UInt32 assignedNumber);
	
	template <typename T>
	T readValue(Handle valueHandle);

	template <typename T>
	void writeValue(Handle valueHandle, T value, bool withResponse);

private:
	std::string _address;
	GATTClient::Ptr _pGATTClient;
	std::string _deviceName;
	std::string _manufacturerName;
	std::string _modelNumber;
	std::string _serialNumber;
	std::string _hardwareRevision;
	std::string _firmwareRevision;
	std::string _softwareRevision;
	Poco::Logger& _logger;
	mutable Poco::Mutex _mutex;
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_GATTPeripheral_INCLUDED
