//
// ModbusMasterServerHelper.h
//
// Library: IoT/Modbus
// Package: Generated
// Module:  ModbusMasterServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Modbus_ModbusMasterServerHelper_INCLUDED
#define IoT_Modbus_ModbusMasterServerHelper_INCLUDED


#include "IoT/Modbus/IModbusMaster.h"
#include "IoT/Modbus/ModbusMaster.h"
#include "IoT/Modbus/ModbusMasterRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Modbus {


class ModbusMasterServerHelper
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
	typedef IoT::Modbus::ModbusMaster Service;

	ModbusMasterServerHelper();
		/// Creates a ModbusMasterServerHelper.

	~ModbusMasterServerHelper();
		/// Destroys the ModbusMasterServerHelper.

	static Poco::AutoPtr<IoT::Modbus::ModbusMasterRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Modbus::ModbusMaster> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Modbus::ModbusMaster instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Modbus::ModbusMaster> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Modbus::ModbusMaster instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Modbus::ModbusMasterRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Modbus::ModbusMaster from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Modbus::ModbusMasterRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Modbus::ModbusMaster> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static ModbusMasterServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Modbus::ModbusMasterRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Modbus::ModbusMasterRemoteObject> ModbusMasterServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Modbus::ModbusMaster> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return ModbusMasterServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void ModbusMasterServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	ModbusMasterServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string ModbusMasterServerHelper::registerObject(Poco::SharedPtr<IoT::Modbus::ModbusMaster> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return ModbusMasterServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string ModbusMasterServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Modbus::ModbusMasterRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return ModbusMasterServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void ModbusMasterServerHelper::unregisterObject(const std::string& uri)
{
	ModbusMasterServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Modbus
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Modbus, ModbusMaster)


#endif // IoT_Modbus_ModbusMasterServerHelper_INCLUDED

