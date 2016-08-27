//
// GyroscopeServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  GyroscopeServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GyroscopeServerHelper_INCLUDED
#define IoT_Devices_GyroscopeServerHelper_INCLUDED


#include "IoT/Devices/Gyroscope.h"
#include "IoT/Devices/GyroscopeRemoteObject.h"
#include "IoT/Devices/IGyroscope.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class GyroscopeServerHelper
	/// The interface for three-axis Gyroscopes.
{
public:
	typedef IoT::Devices::Gyroscope Service;

	GyroscopeServerHelper();
		/// Creates a GyroscopeServerHelper.

	~GyroscopeServerHelper();
		/// Destroys the GyroscopeServerHelper.

	static Poco::AutoPtr<IoT::Devices::GyroscopeRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::Gyroscope> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::Gyroscope instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::Gyroscope> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::Gyroscope instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::GyroscopeRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::Gyroscope from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::GyroscopeRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Gyroscope> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static GyroscopeServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::GyroscopeRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::GyroscopeRemoteObject> GyroscopeServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::Gyroscope> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return GyroscopeServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void GyroscopeServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	GyroscopeServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string GyroscopeServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::Gyroscope> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return GyroscopeServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string GyroscopeServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::GyroscopeRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return GyroscopeServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void GyroscopeServerHelper::unregisterObject(const std::string& uri)
{
	GyroscopeServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, Gyroscope)


#endif // IoT_Devices_GyroscopeServerHelper_INCLUDED

