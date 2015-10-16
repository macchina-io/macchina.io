//
// PeripheralImpl.h
//
// $Id$
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  PeripheralImpl
//
// Definition of the PeripheralImpl class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralImpl_INCLUDED
#define IoT_BtLE_PeripheralImpl_INCLUDED


#include "IoT/BtLE/Peripheral.h"
#include "IoT/BtLE/GATTClient.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"
#include <vector>


namespace IoT {
namespace BtLE {


class IoTBtLE_API PeripheralImpl: public Peripheral
	/// This class provides a high-level interface to a Bluetooth LE peripheral
	/// device using the Bluetooth Generic Attribute Profile (GATT).
{
public:
	PeripheralImpl(const std::string& address, GATTClient::Ptr pGATTClient);
		/// Creates the PeripheralImpl.
		
	~PeripheralImpl();
		/// Destroys the PeripheralImpl.
	
	// Peripheral
	void connect();
	void disconnect();
	bool connected() const;
	std::string address() const;
	std::vector<std::string> services();
	std::vector<std::string> characteristics(const std::string& serviceUUID);
	Characteristic characteristic(const std::string& serviceUUID, const std::string& characteristicUUID);
	Poco::UInt8 readUInt8(Poco::UInt16 valueHandle);	
	Poco::Int8 readInt8(Poco::UInt16 valueHandle);	
	Poco::UInt16 readUInt16(Poco::UInt16 valueHandle);	
	Poco::Int16 readInt16(Poco::UInt16 valueHandle);	
	Poco::UInt32 readUInt32(Poco::UInt16 valueHandle);	
	Poco::Int32 readInt32(Poco::UInt16 valueHandle);	
	std::string read(Poco::UInt16 valueHandle);	
	void writeUInt8(Poco::UInt16 valueHandle, Poco::UInt8 value, bool withResponse);
	void writeInt8(Poco::UInt16 valueHandle, Poco::Int8 value, bool withResponse);
	void writeUInt16(Poco::UInt16 valueHandle, Poco::UInt16 value, bool withResponse);
	void writeInt16(Poco::UInt16 valueHandle, Poco::Int16 value, bool withResponse);
	void writeUInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse);
	void writeInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse);
	void write(Poco::UInt16 valueHandle, const std::string& value, bool withResponse);

private:
	std::string _address;
	GATTClient::Ptr _pGATTClient;
	Poco::Logger& _logger;
	mutable Poco::FastMutex _mutex;
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_PeripheralImpl_INCLUDED
