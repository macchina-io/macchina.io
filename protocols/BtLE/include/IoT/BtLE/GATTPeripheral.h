//
// GATTPeripheral.h
//
// $Id$
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
// SPDX-License-Identifier: Apache-2.0
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
	/// This class provides a high-level interface to a Bluetooth LE peripheral
	/// device using the Bluetooth Generic Attribute Profile (GATT).
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
	std::vector<std::string> services();
	std::string serviceUUIDForAssignedNumber(Poco::UInt32 assignedNumber);
	std::vector<std::string> characteristics(const std::string& serviceUUID);
	Characteristic characteristic(const std::string& serviceUUID, const std::string& characteristicUUID);
	Characteristic characteristicForAssignedNumber(const std::string& serviceUUID, Poco::UInt32 assignedNumber);
	Poco::UInt16 handleForDescriptor(const std::string& serviceUUID, const std::string& descriptorUUID);
	Poco::UInt8 readUInt8(Poco::UInt16 valueHandle);	
	Poco::Int8 readInt8(Poco::UInt16 valueHandle);	
	Poco::UInt16 readUInt16(Poco::UInt16 valueHandle);	
	Poco::Int16 readInt16(Poco::UInt16 valueHandle);	
	Poco::UInt32 readUInt32(Poco::UInt16 valueHandle);	
	Poco::Int32 readInt32(Poco::UInt16 valueHandle);	
	std::string readString(Poco::UInt16 valueHandle);
	std::vector<char> readBytes(Poco::UInt16 valueHandle);
	void writeUInt8(Poco::UInt16 valueHandle, Poco::UInt8 value, bool withResponse);
	void writeInt8(Poco::UInt16 valueHandle, Poco::Int8 value, bool withResponse);
	void writeUInt16(Poco::UInt16 valueHandle, Poco::UInt16 value, bool withResponse);
	void writeInt16(Poco::UInt16 valueHandle, Poco::Int16 value, bool withResponse);
	void writeUInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse);
	void writeInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse);
	void writeString(Poco::UInt16 valueHandle, const std::string& value, bool withResponse);
	void writeBytes(Poco::UInt16 valueHandle, const std::vector<char>& value, bool withResponse);
	std::string manufacturerName();
	std::string modelNumber();
	std::string serialNumber();
	std::string hardwareRevision();
	std::string firmwareRevision();
	std::string softwareRevision();

protected:
	void onConnected();
	void onDisconnected();
	void onError(const std::string& error);
	void onIndication(const GATTClient::Indication& ind);
	void onNotification(const GATTClient::Notification& nf);
	std::string readDeviceInformation(Poco::UInt32 assignedNumber);

private:
	std::string _address;
	GATTClient::Ptr _pGATTClient;
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
