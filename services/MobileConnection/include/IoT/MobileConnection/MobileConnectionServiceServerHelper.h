//
// MobileConnectionServiceServerHelper.h
//
// Library: IoT/MobileConnection
// Package: Generated
// Module:  MobileConnectionServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MobileConnection_MobileConnectionServiceServerHelper_INCLUDED
#define IoT_MobileConnection_MobileConnectionServiceServerHelper_INCLUDED


#include "IoT/MobileConnection/IMobileConnectionService.h"
#include "IoT/MobileConnection/MobileConnectionService.h"
#include "IoT/MobileConnection/MobileConnectionServiceRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace MobileConnection {


class MobileConnectionServiceServerHelper
	/// The MobileConnectionService interface is used to configure
	/// and establish a mobile data connection.
{
public:
	using Service = IoT::MobileConnection::MobileConnectionService;

	MobileConnectionServiceServerHelper();
		/// Creates a MobileConnectionServiceServerHelper.

	~MobileConnectionServiceServerHelper();
		/// Destroys the MobileConnectionServiceServerHelper.

	static Poco::AutoPtr<IoT::MobileConnection::MobileConnectionServiceRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::MobileConnection::MobileConnectionService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::MobileConnection::MobileConnectionService instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::MobileConnection::MobileConnectionService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::MobileConnection::MobileConnectionService instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::MobileConnection::MobileConnectionServiceRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::MobileConnection::MobileConnectionService from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::MobileConnection::MobileConnectionServiceRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::MobileConnection::MobileConnectionService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static MobileConnectionServiceServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::MobileConnection::MobileConnectionServiceRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::MobileConnection::MobileConnectionServiceRemoteObject> MobileConnectionServiceServerHelper::createRemoteObject(Poco::SharedPtr<IoT::MobileConnection::MobileConnectionService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return MobileConnectionServiceServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void MobileConnectionServiceServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	MobileConnectionServiceServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string MobileConnectionServiceServerHelper::registerObject(Poco::SharedPtr<IoT::MobileConnection::MobileConnectionService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return MobileConnectionServiceServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string MobileConnectionServiceServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::MobileConnection::MobileConnectionServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return MobileConnectionServiceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void MobileConnectionServiceServerHelper::unregisterObject(const std::string& uri)
{
	MobileConnectionServiceServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace MobileConnection
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::MobileConnection, MobileConnectionService)


#endif // IoT_MobileConnection_MobileConnectionServiceServerHelper_INCLUDED

