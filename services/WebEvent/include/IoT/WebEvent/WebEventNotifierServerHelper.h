//
// WebEventNotifierServerHelper.h
//
// Library: IoT/WebEvent
// Package: Generated
// Module:  WebEventNotifierServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_WebEvent_WebEventNotifierServerHelper_INCLUDED
#define IoT_WebEvent_WebEventNotifierServerHelper_INCLUDED


#include "IoT/WebEvent/IWebEventNotifier.h"
#include "IoT/WebEvent/WebEventNotifier.h"
#include "IoT/WebEvent/WebEventNotifierRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace WebEvent {


class WebEventNotifierServerHelper
	/// A simplified Remoting-capable interface to the 
	/// Poco::OSP::WebEvent::WebEventService,
	/// usable from both C++ and JavaScript.
{
public:
	typedef IoT::WebEvent::WebEventNotifier Service;

	WebEventNotifierServerHelper();
		/// Creates a WebEventNotifierServerHelper.

	~WebEventNotifierServerHelper();
		/// Destroys the WebEventNotifierServerHelper.

	static Poco::AutoPtr<IoT::WebEvent::WebEventNotifierRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::WebEvent::WebEventNotifier instance.

	static std::string registerObject(Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::WebEvent::WebEventNotifier instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::WebEvent::WebEventNotifierRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::WebEvent::WebEventNotifier from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::WebEvent::WebEventNotifierRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	static WebEventNotifierServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::WebEvent::WebEventNotifierRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::WebEvent::WebEventNotifierRemoteObject> WebEventNotifierServerHelper::createRemoteObject(Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return WebEventNotifierServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline std::string WebEventNotifierServerHelper::registerObject(Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return WebEventNotifierServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string WebEventNotifierServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::WebEvent::WebEventNotifierRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return WebEventNotifierServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void WebEventNotifierServerHelper::unregisterObject(const std::string& uri)
{
	WebEventNotifierServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace WebEvent
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::WebEvent, WebEventNotifier)


#endif // IoT_WebEvent_WebEventNotifierServerHelper_INCLUDED

