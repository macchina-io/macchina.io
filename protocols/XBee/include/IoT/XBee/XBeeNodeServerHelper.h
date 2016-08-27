//
// XBeeNodeServerHelper.h
//
// Library: IoT/XBee
// Package: Generated
// Module:  XBeeNodeServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_XBeeNodeServerHelper_INCLUDED
#define IoT_XBee_XBeeNodeServerHelper_INCLUDED


#include "IoT/XBee/IXBeeNode.h"
#include "IoT/XBee/XBeeNode.h"
#include "IoT/XBee/XBeeNodeRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace XBee {


class XBeeNodeServerHelper
	/// This class provides a high-level interface to a Digi XBee device
	/// using the Digi XBee API frame-based protocol. This class can be
	/// used with all XBee devices supporting the XBee API frame-based
	/// protocol, including ZigBee devices. Actually supported methods
	/// and events are depending on the kind of XBee device, e.g., an
	/// 802.15.4 module won't support ZigBee-specific API frames, and
	/// vice-versa. Please refer to the XBee product manual for detailed
	/// information about the API.
{
public:
	typedef IoT::XBee::XBeeNode Service;

	XBeeNodeServerHelper();
		/// Creates a XBeeNodeServerHelper.

	~XBeeNodeServerHelper();
		/// Destroys the XBeeNodeServerHelper.

	static Poco::AutoPtr<IoT::XBee::XBeeNodeRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::XBee::XBeeNode> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::XBee::XBeeNode instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::XBee::XBeeNode> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::XBee::XBeeNode instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::XBee::XBeeNodeRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::XBee::XBeeNode from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::XBee::XBeeNodeRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::XBee::XBeeNode> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static XBeeNodeServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::XBee::XBeeNodeRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::XBee::XBeeNodeRemoteObject> XBeeNodeServerHelper::createRemoteObject(Poco::SharedPtr<IoT::XBee::XBeeNode> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return XBeeNodeServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void XBeeNodeServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	XBeeNodeServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string XBeeNodeServerHelper::registerObject(Poco::SharedPtr<IoT::XBee::XBeeNode> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return XBeeNodeServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string XBeeNodeServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::XBee::XBeeNodeRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return XBeeNodeServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void XBeeNodeServerHelper::unregisterObject(const std::string& uri)
{
	XBeeNodeServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace XBee
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::XBee, XBeeNode)


#endif // IoT_XBee_XBeeNodeServerHelper_INCLUDED

