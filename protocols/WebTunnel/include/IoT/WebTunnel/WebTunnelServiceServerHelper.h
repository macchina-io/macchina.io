//
// WebTunnelServiceServerHelper.h
//
// Library: IoT/WebTunnel
// Package: Generated
// Module:  WebTunnelServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2019-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_WebTunnel_WebTunnelServiceServerHelper_INCLUDED
#define IoT_WebTunnel_WebTunnelServiceServerHelper_INCLUDED


#include "IoT/WebTunnel/IWebTunnelService.h"
#include "IoT/WebTunnel/WebTunnelService.h"
#include "IoT/WebTunnel/WebTunnelServiceRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace WebTunnel {


class WebTunnelServiceServerHelper
	/// The interface for WebTunnel clients.
{
public:
	using Service = IoT::WebTunnel::WebTunnelService;

	WebTunnelServiceServerHelper();
		/// Creates a WebTunnelServiceServerHelper.

	~WebTunnelServiceServerHelper();
		/// Destroys the WebTunnelServiceServerHelper.

	static Poco::AutoPtr<IoT::WebTunnel::WebTunnelServiceRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::WebTunnel::WebTunnelService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::WebTunnel::WebTunnelService instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::WebTunnel::WebTunnelService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::WebTunnel::WebTunnelService instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::WebTunnel::WebTunnelServiceRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::WebTunnel::WebTunnelService from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::WebTunnel::WebTunnelServiceRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::WebTunnel::WebTunnelService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static WebTunnelServiceServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::WebTunnel::WebTunnelServiceRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::WebTunnel::WebTunnelServiceRemoteObject> WebTunnelServiceServerHelper::createRemoteObject(Poco::SharedPtr<IoT::WebTunnel::WebTunnelService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return WebTunnelServiceServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void WebTunnelServiceServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	WebTunnelServiceServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string WebTunnelServiceServerHelper::registerObject(Poco::SharedPtr<IoT::WebTunnel::WebTunnelService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return WebTunnelServiceServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string WebTunnelServiceServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::WebTunnel::WebTunnelServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return WebTunnelServiceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void WebTunnelServiceServerHelper::unregisterObject(const std::string& uri)
{
	WebTunnelServiceServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace WebTunnel
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::WebTunnel, WebTunnelService)


#endif // IoT_WebTunnel_WebTunnelServiceServerHelper_INCLUDED

