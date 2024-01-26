//
// BooleanDatapointServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  BooleanDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_BooleanDatapointServerHelper_INCLUDED
#define IoT_Devices_BooleanDatapointServerHelper_INCLUDED


#include "IoT/Devices/BooleanDatapoint.h"
#include "IoT/Devices/BooleanDatapointRemoteObject.h"
#include "IoT/Devices/IBooleanDatapoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class BooleanDatapointServerHelper
	/// The base class for datapoints holding a boolean value.
	///
	/// In addition to the methods defined in this interface,
	/// a BooleanDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Service = IoT::Devices::BooleanDatapoint;

	BooleanDatapointServerHelper();
		/// Creates a BooleanDatapointServerHelper.

	~BooleanDatapointServerHelper();
		/// Destroys the BooleanDatapointServerHelper.

	static Poco::AutoPtr<IoT::Devices::BooleanDatapointRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::BooleanDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::BooleanDatapoint instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::BooleanDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::BooleanDatapoint instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::BooleanDatapointRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::BooleanDatapoint from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::BooleanDatapointRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::BooleanDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static BooleanDatapointServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::BooleanDatapointRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::BooleanDatapointRemoteObject> BooleanDatapointServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::BooleanDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return BooleanDatapointServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void BooleanDatapointServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	BooleanDatapointServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string BooleanDatapointServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::BooleanDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return BooleanDatapointServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string BooleanDatapointServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::BooleanDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return BooleanDatapointServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void BooleanDatapointServerHelper::unregisterObject(const std::string& uri)
{
	BooleanDatapointServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, BooleanDatapoint)


#endif // IoT_Devices_BooleanDatapointServerHelper_INCLUDED

