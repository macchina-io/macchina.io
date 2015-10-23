//
// GATTClient.h
//
// $Id$
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  GATTClient
//
// Definition of the GATTClient class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_GATTClient_INCLUDED
#define IoT_BtLE_GATTClient_INCLUDED


#include "IoT/BtLE/BtLE.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include <vector>
#include <map>


namespace IoT {
namespace BtLE {


class IoTBtLE_API GATTClient
	/// This class provides a low-level interface to a Bluetooth LE peripheral
	/// device using the Bluetooth Generic Attribute Profile (GATT).
{
public:
	typedef Poco::SharedPtr<GATTClient> Ptr;

	enum ConnectMode
		/// Connect mode - synchronous or asynchronous.
	{
		GATT_CONNECT_WAIT,
		GATT_CONNECT_NOWAIT
	};

	enum State
		/// State of the connection to the peripheral device.
	{
		GATT_STATE_DISCONNECTED,
		GATT_STATE_CONNECTING,
		GATT_STATE_CONNECTED,
		GATT_STATE_DISCONNECTING
	};
	
	enum SecurityLevel
		/// Security level of the connection to the peripheral device.
	{
		GATT_SECURITY_LOW,
		GATT_SECURITY_MEDIUM,
		GATT_SECURITY_HIGH
	};
	
	enum Property
		/// Characteristic property flags.
	{
		GATT_PROP_BROADCAST     = 0x01,
		GATT_PROP_READ          = 0x02,
        GATT_PROP_WRITE_NO_RESP = 0x04,
    	GATT_PROP_WRITE         = 0x08,
        GATT_PROP_NOTIFY        = 0x10,
        GATT_PROP_INDICATE      = 0x20,
        GATT_PROP_WRITE_SIGNED  = 0x40,
        GATT_PROP_EXTENDED      = 0x80
	};
	
	struct Service
		/// Service description.
	{
		Service():
			firstHandle(0),
			lastHandle(0)
		{
		}
		
		std::string uuid;
		Poco::UInt16 firstHandle;
		Poco::UInt16 lastHandle;
	};

	struct Descriptor
		/// Handle Descriptor
	{
		Descriptor():
			handle(0)
		{
		}

		Poco::UInt16 handle;
		std::string uuid;
	};
	
	struct Characteristic
		/// Characteristic description.
	{
		Characteristic():
			handle(0),
			properties(0),
			valueHandle(0)
		{
		}
		
		std::string uuid;
		Poco::UInt16 handle;
		Poco::UInt16 properties;
		Poco::UInt16 valueHandle;
	};
	
	struct Indication
	{
		Indication():
			handle(0)
		{
		}
		
		Poco::UInt16 handle;
		std::string data;
	};
	
	struct Notification
	{
		Notification():
			handle(0)
		{
		}
		
		Poco::UInt16 handle;
		std::string data;
	};

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
	
	virtual void connect(const std::string& address, ConnectMode mode = GATT_CONNECT_WAIT) = 0;
		/// Connects the GATTClient to the Bluetooth LE peripheral with the
		/// given address. The address consists of six hexadecimal byte values, 
		/// separated by a colon, e.g.: "68:C9:0B:06:23:09".
		///
		/// If mode is GATT_CONNECT_WAIT, waits for the connection to be established (or
		/// for an error to be reported). 
		///
		/// If wait is GATT_CONNECT_NOWAIT, returns immediately. The connection state is
		/// reported via the connected event.

	virtual void disconnect() = 0;
		/// Disconnects from the peripheral.
		
	virtual State state() const = 0;
		/// Returns the current state of the client.
		
	virtual std::string address() const = 0;
		/// Returns the address of the connected device, or an empty string
		/// if no device is connected.

	virtual std::vector<Service> services() = 0;
		/// Returns a list of all services supported by the peripheral.

	virtual std::vector<Service> includedServices(const std::string& serviceUUID) = 0;
		/// Returns a list of all services included by the service identified by the given handles.

	virtual std::vector<Characteristic> characteristics(const std::string& serviceUUID) = 0;
		/// Returns a list of all characteristics of the service with the given UUID.

	virtual std::vector<Descriptor> descriptors(const std::string& serviceUUID) = 0;
		/// Returns a list of all handle descriptors for the service with the given UUID.
		
	virtual std::string read(Poco::UInt16 handle) = 0;
		/// Reads the value of the characteristic's value with the given value handle.
		
	virtual void write(Poco::UInt16 handle, const std::string& value, bool withResponse = true) = 0;
		/// Writes the value of the characteristic's value with the given handle.
		/// If withResponse is true, expects a response from the peripheral device.

	virtual void setSecurityLevel(SecurityLevel level) = 0;
		/// Sets the connection's security level.
		
	virtual SecurityLevel getSecurityLevel() const = 0;
		/// Returns the connection's current security level.
		
	virtual void setMTU(Poco::UInt8 mtu) = 0;
		/// Sets the connection's MTU size.
		
	virtual Poco::UInt8 getMTU() const = 0;
		/// Returns the connection's MTU size, which may be 0 for 
		/// the default size.

	virtual void setTimeout(long milliseconds) = 0;
		/// Sets the timeout for communication with the peripheral device.

	virtual long getTimeout() const = 0;
		/// Returns the timeout for communication with the peripheral device.

	virtual ~GATTClient();
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_GATTClient_INCLUDED

