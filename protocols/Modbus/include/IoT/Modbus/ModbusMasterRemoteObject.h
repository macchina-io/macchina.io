//
// ModbusMasterRemoteObject.h
//
// Library: IoT/Modbus
// Package: Generated
// Module:  ModbusMasterRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Modbus_ModbusMasterRemoteObject_INCLUDED
#define IoT_Modbus_ModbusMasterRemoteObject_INCLUDED


#include "IoT/Modbus/IModbusMaster.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Modbus {


class ModbusMasterRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Modbus::IModbusMaster
	/// This class defines the interface for Modbus clients.
	///
	/// The interface supports two basic modes of operation:
	///    - Asynchronous requests: One of the sendXXXRequest() methods is used
	///      to send a request to the device. The method returns as soon as the
	///      request has been sent over the wire. The device's response is
	///      reported asynchronously via an appropriate XXXResponseReceived event.
	///    - Synchronous requests: After sending the request, the method waits
	///      for the response from the device and directly returns it to the caller.
	///      In case no response is received within the specified timeout, a
	///      Poco::TimeoutException is thrown. If an exception message is received
	///      from the device, a ModbusException is thrown. If an incomplete or invalid
	///      message is received, a Poco::ProtocolException is thrown.
	///
	/// Note that asynchronous and synchronous (blocking) mode cannot be used
	/// simultaneously. Calling one of the asynchronous request methods will enable
	/// asynchronous mode. Calling one of the synchronous request methods will
	/// disable asynchronous mode. Switching to synchronous mode while a response
	/// to an asynchronous request is pending will lead to undefined results,
	/// including possible mismatch of requests and responses.
	///
	/// In asynchronous operation, requests are associated with a transaction ID,
	/// to tell apart multiple concurrent transactions. Transaction IDs are not guaranteed
	/// to be unique for subsequent requests. In fact, for Modbus RTU, which does not
	/// allow multiple simultaneous requests, the transaction ID will always be zero.
{
public:
	typedef Poco::AutoPtr<ModbusMasterRemoteObject> Ptr;

	ModbusMasterRemoteObject();
		/// Creates a ModbusMasterRemoteObject.

	virtual ~ModbusMasterRemoteObject();
		/// Destroys the ModbusMasterRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& ModbusMasterRemoteObject::remoting__typeId() const
{
	return IModbusMaster::remoting__typeId();
}


} // namespace Modbus
} // namespace IoT


#endif // IoT_Modbus_ModbusMasterRemoteObject_INCLUDED

