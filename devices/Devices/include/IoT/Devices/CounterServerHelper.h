//
// CounterServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  CounterServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_CounterServerHelper_INCLUDED
#define IoT_Devices_CounterServerHelper_INCLUDED


#include "IoT/Devices/Counter.h"
#include "IoT/Devices/CounterRemoteObject.h"
#include "IoT/Devices/ICounter.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class CounterServerHelper
	/// A counter counts events.
{
public:
	using Service = IoT::Devices::Counter;

	CounterServerHelper();
		/// Creates a CounterServerHelper.

	~CounterServerHelper();
		/// Destroys the CounterServerHelper.

	static Poco::AutoPtr<IoT::Devices::CounterRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::Counter> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::Counter instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::Counter> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::Counter instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::CounterRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::Counter from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::CounterRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Counter> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static CounterServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::CounterRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::CounterRemoteObject> CounterServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::Counter> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return CounterServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void CounterServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	CounterServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string CounterServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::Counter> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return CounterServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string CounterServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::CounterRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return CounterServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void CounterServerHelper::unregisterObject(const std::string& uri)
{
	CounterServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, Counter)


#endif // IoT_Devices_CounterServerHelper_INCLUDED

