//
// PeripheralBrowserServerHelper.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralBrowserServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralBrowserServerHelper_INCLUDED
#define IoT_BtLE_PeripheralBrowserServerHelper_INCLUDED


#include "IoT/BtLE/IPeripheralBrowser.h"
#include "IoT/BtLE/PeripheralBrowser.h"
#include "IoT/BtLE/PeripheralBrowserRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace BtLE {


class PeripheralBrowserServerHelper
	/// This class provides browsing for available Bluetooth LE devices.
{
public:
	typedef IoT::BtLE::PeripheralBrowser Service;

	PeripheralBrowserServerHelper();
		/// Creates a PeripheralBrowserServerHelper.

	~PeripheralBrowserServerHelper();
		/// Destroys the PeripheralBrowserServerHelper.

	static Poco::AutoPtr<IoT::BtLE::PeripheralBrowserRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::BtLE::PeripheralBrowser instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::BtLE::PeripheralBrowser instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::BtLE::PeripheralBrowserRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::BtLE::PeripheralBrowser from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::BtLE::PeripheralBrowserRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static PeripheralBrowserServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::BtLE::PeripheralBrowserRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::BtLE::PeripheralBrowserRemoteObject> PeripheralBrowserServerHelper::createRemoteObject(Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return PeripheralBrowserServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void PeripheralBrowserServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	PeripheralBrowserServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string PeripheralBrowserServerHelper::registerObject(Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return PeripheralBrowserServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string PeripheralBrowserServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::BtLE::PeripheralBrowserRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return PeripheralBrowserServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void PeripheralBrowserServerHelper::unregisterObject(const std::string& uri)
{
	PeripheralBrowserServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace BtLE
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::BtLE, PeripheralBrowser)


#endif // IoT_BtLE_PeripheralBrowserServerHelper_INCLUDED

