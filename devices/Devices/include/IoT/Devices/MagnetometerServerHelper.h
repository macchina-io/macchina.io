//
// MagnetometerServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  MagnetometerServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_MagnetometerServerHelper_INCLUDED
#define IoT_Devices_MagnetometerServerHelper_INCLUDED


#include "IoT/Devices/IMagnetometer.h"
#include "IoT/Devices/Magnetometer.h"
#include "IoT/Devices/MagnetometerRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class MagnetometerServerHelper
	/// The interface for three-axis Magnetometers.
{
public:
	typedef IoT::Devices::Magnetometer Service;

	MagnetometerServerHelper();
		/// Creates a MagnetometerServerHelper.

	~MagnetometerServerHelper();
		/// Destroys the MagnetometerServerHelper.

	static Poco::AutoPtr<IoT::Devices::MagnetometerRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::Magnetometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::Magnetometer instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::Magnetometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::Magnetometer instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::MagnetometerRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::Magnetometer from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::MagnetometerRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Magnetometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static MagnetometerServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::MagnetometerRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::MagnetometerRemoteObject> MagnetometerServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::Magnetometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return MagnetometerServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void MagnetometerServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	MagnetometerServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string MagnetometerServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::Magnetometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return MagnetometerServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string MagnetometerServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::MagnetometerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return MagnetometerServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void MagnetometerServerHelper::unregisterObject(const std::string& uri)
{
	MagnetometerServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, Magnetometer)


#endif // IoT_Devices_MagnetometerServerHelper_INCLUDED

