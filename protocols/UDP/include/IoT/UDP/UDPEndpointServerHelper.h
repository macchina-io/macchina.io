//
// UDPEndpointServerHelper.h
//
// Library: IoT/UDP
// Package: Generated
// Module:  UDPEndpointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_UDP_UDPEndpointServerHelper_INCLUDED
#define IoT_UDP_UDPEndpointServerHelper_INCLUDED


#include "IoT/UDP/IUDPEndpoint.h"
#include "IoT/UDP/UDPEndpoint.h"
#include "IoT/UDP/UDPEndpointRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace UDP {


class UDPEndpointServerHelper
	/// The UDPEndpoint is used to receive and send UDP packets.
{
public:
	typedef IoT::UDP::UDPEndpoint Service;

	UDPEndpointServerHelper();
		/// Creates a UDPEndpointServerHelper.

	~UDPEndpointServerHelper();
		/// Destroys the UDPEndpointServerHelper.

	static Poco::AutoPtr<IoT::UDP::UDPEndpointRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::UDP::UDPEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::UDP::UDPEndpoint instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::UDP::UDPEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::UDP::UDPEndpoint instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::UDP::UDPEndpointRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::UDP::UDPEndpoint from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::UDP::UDPEndpointRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::UDP::UDPEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static UDPEndpointServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::UDP::UDPEndpointRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::UDP::UDPEndpointRemoteObject> UDPEndpointServerHelper::createRemoteObject(Poco::SharedPtr<IoT::UDP::UDPEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return UDPEndpointServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void UDPEndpointServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	UDPEndpointServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string UDPEndpointServerHelper::registerObject(Poco::SharedPtr<IoT::UDP::UDPEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return UDPEndpointServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string UDPEndpointServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::UDP::UDPEndpointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return UDPEndpointServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void UDPEndpointServerHelper::unregisterObject(const std::string& uri)
{
	UDPEndpointServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace UDP
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::UDP, UDPEndpoint)


#endif // IoT_UDP_UDPEndpointServerHelper_INCLUDED

