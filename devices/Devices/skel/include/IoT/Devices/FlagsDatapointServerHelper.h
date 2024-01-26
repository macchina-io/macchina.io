//
// FlagsDatapointServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  FlagsDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_FlagsDatapointServerHelper_INCLUDED
#define IoT_Devices_FlagsDatapointServerHelper_INCLUDED


#include "IoT/Devices/FlagsDatapoint.h"
#include "IoT/Devices/FlagsDatapointRemoteObject.h"
#include "IoT/Devices/IFlagsDatapoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class FlagsDatapointServerHelper
	/// The base class for datapoints holding a variable number of
	/// flag bits, internally stored as a std::vector<bool>.
	///
	/// An implementation should handle conversion between a
	/// flag bit and the corresponding symbolic name of
	/// a flag.
	///
	/// In addition to the methods defined in this interface,
	/// a FlagsDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Service = IoT::Devices::FlagsDatapoint;

	FlagsDatapointServerHelper();
		/// Creates a FlagsDatapointServerHelper.

	~FlagsDatapointServerHelper();
		/// Destroys the FlagsDatapointServerHelper.

	static Poco::AutoPtr<IoT::Devices::FlagsDatapointRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::FlagsDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::FlagsDatapoint instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::FlagsDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::FlagsDatapoint instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::FlagsDatapointRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::FlagsDatapoint from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::FlagsDatapointRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::FlagsDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static FlagsDatapointServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::FlagsDatapointRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::FlagsDatapointRemoteObject> FlagsDatapointServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::FlagsDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return FlagsDatapointServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void FlagsDatapointServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	FlagsDatapointServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string FlagsDatapointServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::FlagsDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return FlagsDatapointServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string FlagsDatapointServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::FlagsDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return FlagsDatapointServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void FlagsDatapointServerHelper::unregisterObject(const std::string& uri)
{
	FlagsDatapointServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, FlagsDatapoint)


#endif // IoT_Devices_FlagsDatapointServerHelper_INCLUDED

