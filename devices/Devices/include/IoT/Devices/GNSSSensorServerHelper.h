//
// GNSSSensorServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  GNSSSensorServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GNSSSensorServerHelper_INCLUDED
#define IoT_Devices_GNSSSensorServerHelper_INCLUDED


#include "IoT/Devices/GNSSSensor.h"
#include "IoT/Devices/GNSSSensorRemoteObject.h"
#include "IoT/Devices/IGNSSSensor.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class GNSSSensorServerHelper
	/// The interface for GNSS/GPS receivers.
	///
	/// Implementations of this class should also support the
	/// following (optional) properties for configuration:
	///
	///   - positionChangedPeriod (int): the minimum time interval
	///     in milliseconds between firings of the positionUpdate event.
	///   - positionChangedDelta (int): the minimum distance (in meters)
	///     the receiver must move before the positionUpdate event
	///     is fired again.
	///   - positionTimeout (int): Timeout in milliseconds after which the
	///     positionLost event is fired if no valid position has been
	///     received from the GNSS receiver.
{
public:
	typedef IoT::Devices::GNSSSensor Service;

	GNSSSensorServerHelper();
		/// Creates a GNSSSensorServerHelper.

	~GNSSSensorServerHelper();
		/// Destroys the GNSSSensorServerHelper.

	static Poco::AutoPtr<IoT::Devices::GNSSSensorRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::GNSSSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::GNSSSensor instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::GNSSSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::GNSSSensor instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::GNSSSensorRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::GNSSSensor from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::GNSSSensorRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::GNSSSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static GNSSSensorServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::GNSSSensorRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::GNSSSensorRemoteObject> GNSSSensorServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::GNSSSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return GNSSSensorServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void GNSSSensorServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	GNSSSensorServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string GNSSSensorServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::GNSSSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return GNSSSensorServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string GNSSSensorServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::GNSSSensorRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return GNSSSensorServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void GNSSSensorServerHelper::unregisterObject(const std::string& uri)
{
	GNSSSensorServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, GNSSSensor)


#endif // IoT_Devices_GNSSSensorServerHelper_INCLUDED

