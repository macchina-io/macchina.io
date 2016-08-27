//
// AccelerometerServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  AccelerometerServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_AccelerometerServerHelper_INCLUDED
#define IoT_Devices_AccelerometerServerHelper_INCLUDED


#include "IoT/Devices/Accelerometer.h"
#include "IoT/Devices/AccelerometerRemoteObject.h"
#include "IoT/Devices/IAccelerometer.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class AccelerometerServerHelper
	/// The interface for three-axis Accelerometers.
{
public:
	typedef IoT::Devices::Accelerometer Service;

	AccelerometerServerHelper();
		/// Creates a AccelerometerServerHelper.

	~AccelerometerServerHelper();
		/// Destroys the AccelerometerServerHelper.

	static Poco::AutoPtr<IoT::Devices::AccelerometerRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::Accelerometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::Accelerometer instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::Accelerometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::Accelerometer instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::AccelerometerRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::Accelerometer from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::AccelerometerRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Accelerometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static AccelerometerServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::AccelerometerRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::AccelerometerRemoteObject> AccelerometerServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::Accelerometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return AccelerometerServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void AccelerometerServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	AccelerometerServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string AccelerometerServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::Accelerometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return AccelerometerServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string AccelerometerServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::AccelerometerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return AccelerometerServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void AccelerometerServerHelper::unregisterObject(const std::string& uri)
{
	AccelerometerServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, Accelerometer)


#endif // IoT_Devices_AccelerometerServerHelper_INCLUDED

