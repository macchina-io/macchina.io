//
// CANEndpointServerHelper.h
//
// Library: IoT/CAN
// Package: Generated
// Module:  CANEndpointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_CAN_CANEndpointServerHelper_INCLUDED
#define IoT_CAN_CANEndpointServerHelper_INCLUDED


#include "IoT/CAN/CANEndpoint.h"
#include "IoT/CAN/CANEndpointRemoteObject.h"
#include "IoT/CAN/ICANEndpoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace CAN {


class CANEndpointServerHelper
	/// The CANEndpoint is used to receive and send CAN and CAN-FD frames.
{
public:
	using Service = IoT::CAN::CANEndpoint;

	CANEndpointServerHelper();
		/// Creates a CANEndpointServerHelper.

	~CANEndpointServerHelper();
		/// Destroys the CANEndpointServerHelper.

	static Poco::AutoPtr<IoT::CAN::CANEndpointRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::CAN::CANEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::CAN::CANEndpoint instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::CAN::CANEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::CAN::CANEndpoint instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::CAN::CANEndpointRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::CAN::CANEndpoint from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::CAN::CANEndpointRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::CAN::CANEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static CANEndpointServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::CAN::CANEndpointRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::CAN::CANEndpointRemoteObject> CANEndpointServerHelper::createRemoteObject(Poco::SharedPtr<IoT::CAN::CANEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return CANEndpointServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void CANEndpointServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	CANEndpointServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string CANEndpointServerHelper::registerObject(Poco::SharedPtr<IoT::CAN::CANEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return CANEndpointServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string CANEndpointServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::CAN::CANEndpointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return CANEndpointServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void CANEndpointServerHelper::unregisterObject(const std::string& uri)
{
	CANEndpointServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace CAN
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::CAN, CANEndpoint)


#endif // IoT_CAN_CANEndpointServerHelper_INCLUDED

