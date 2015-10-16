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
#include "Poco/BasicEvent.h"
#include <vector>


namespace IoT {
namespace BtLE {


//@ serialize
struct Characteristic
{
	Poco::UInt16 properties;
	Poco::UInt16 valueHandle;
};


//@ remote
class IoTBtLE_API Peripheral
	/// This class provides a high-level interface to a Bluetooth LE peripheral
	/// device using the Bluetooth Generic Attribute Profile (GATT).
{
public:
	virtual void connect() = 0;
		/// Connects to the Bluetooth LE peripheral.
		
	virtual void disconnect() = 0;
		/// Disconnects from the Bluetooth LE peripheral.
		
	virtual bool connected() const = 0;
		/// Returns true if the device is connected.
	
	virtual std::string address() const = 0;
		/// Returns the address of the device.
		
	virtual std::vector<std::string> services() = 0;
		/// Returns a vector containing the UUIDs of all available services.
		
	virtual std::vector<std::string> characteristics(const std::string& serviceUUID) = 0;
		/// Returns a vector containing the UUIDs of all available characteristics
		/// of the service identified by the given serviceUUID.
		
	virtual Characteristic characteristic(const std::string& serviceUUID, const std::string& characteristicUUID) = 0;
		/// Returns the properties and handle for accessing the value of the given characteristic.

	virtual Poco::UInt8 readUInt8(Poco::UInt16 valueHandle) = 0;	
	virtual Poco::Int8 readInt8(Poco::UInt16 valueHandle) = 0;	
	virtual Poco::UInt16 readUInt16(Poco::UInt16 valueHandle) = 0;	
	virtual Poco::Int16 readInt16(Poco::UInt16 valueHandle) = 0;	
	virtual Poco::UInt32 readUInt32(Poco::UInt16 valueHandle) = 0;	
	virtual Poco::Int32 readInt32(Poco::UInt16 valueHandle) = 0;	
	virtual std::string read(Poco::UInt16 valueHandle) = 0;
	
	virtual void writeUInt8(Poco::UInt16 valueHandle, Poco::UInt8 value, bool withResponse) = 0;
	virtual void writeInt8(Poco::UInt16 valueHandle, Poco::Int8 value, bool withResponse) = 0;
	virtual void writeUInt16(Poco::UInt16 valueHandle, Poco::UInt16 value, bool withResponse) = 0;
	virtual void writeInt16(Poco::UInt16 valueHandle, Poco::Int16 value, bool withResponse) = 0;
	virtual void writeUInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse) = 0;
	virtual void writeInt32(Poco::UInt16 valueHandle, Poco::UInt32 value, bool withResponse) = 0;
	virtual void write(Poco::UInt16 valueHandle, const std::string& value, bool withResponse) = 0;
	
	virtual ~Peripheral();
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_Peripheral_INCLUDED
