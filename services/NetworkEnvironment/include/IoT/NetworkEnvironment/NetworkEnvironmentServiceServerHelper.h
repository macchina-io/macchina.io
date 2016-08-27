//
// NetworkEnvironmentServiceServerHelper.h
//
// Library: IoT/NetworkEnvironment
// Package: Generated
// Module:  NetworkEnvironmentServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_NetworkEnvironment_NetworkEnvironmentServiceServerHelper_INCLUDED
#define IoT_NetworkEnvironment_NetworkEnvironmentServiceServerHelper_INCLUDED


#include "IoT/NetworkEnvironment/INetworkEnvironmentService.h"
#include "IoT/NetworkEnvironment/NetworkEnvironmentService.h"
#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace NetworkEnvironment {


class NetworkEnvironmentServiceServerHelper
	/// The NetworkEnvironmentService can be used to get notifications
	/// about network address and network interface changes.
{
public:
	typedef IoT::NetworkEnvironment::NetworkEnvironmentService Service;

	NetworkEnvironmentServiceServerHelper();
		/// Creates a NetworkEnvironmentServiceServerHelper.

	~NetworkEnvironmentServiceServerHelper();
		/// Destroys the NetworkEnvironmentServiceServerHelper.

	static Poco::AutoPtr<IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::NetworkEnvironment::NetworkEnvironmentService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::NetworkEnvironment::NetworkEnvironmentService instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::NetworkEnvironment::NetworkEnvironmentService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::NetworkEnvironment::NetworkEnvironmentService instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::NetworkEnvironment::NetworkEnvironmentService from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::NetworkEnvironment::NetworkEnvironmentService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static NetworkEnvironmentServiceServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject> NetworkEnvironmentServiceServerHelper::createRemoteObject(Poco::SharedPtr<IoT::NetworkEnvironment::NetworkEnvironmentService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return NetworkEnvironmentServiceServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void NetworkEnvironmentServiceServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	NetworkEnvironmentServiceServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string NetworkEnvironmentServiceServerHelper::registerObject(Poco::SharedPtr<IoT::NetworkEnvironment::NetworkEnvironmentService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return NetworkEnvironmentServiceServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string NetworkEnvironmentServiceServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return NetworkEnvironmentServiceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void NetworkEnvironmentServiceServerHelper::unregisterObject(const std::string& uri)
{
	NetworkEnvironmentServiceServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace NetworkEnvironment
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::NetworkEnvironment, NetworkEnvironmentService)


#endif // IoT_NetworkEnvironment_NetworkEnvironmentServiceServerHelper_INCLUDED

