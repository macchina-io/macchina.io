//
// EnumDatapointServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  EnumDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_EnumDatapointServerHelper_INCLUDED
#define IoT_Devices_EnumDatapointServerHelper_INCLUDED


#include "IoT/Devices/EnumDatapoint.h"
#include "IoT/Devices/EnumDatapointRemoteObject.h"
#include "IoT/Devices/IEnumDatapoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class EnumDatapointServerHelper
	/// The base class for datapoints holding an enumeration
	/// value (based on an int).
	///
	/// An implementation should handle conversion between an
	/// integer value and the corresponding symbolic name.
	///
	/// In addition to the methods defined in this interface,
	/// a EnumDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Service = IoT::Devices::EnumDatapoint;

	EnumDatapointServerHelper();
		/// Creates a EnumDatapointServerHelper.

	~EnumDatapointServerHelper();
		/// Destroys the EnumDatapointServerHelper.

	static Poco::AutoPtr<IoT::Devices::EnumDatapointRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::EnumDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::EnumDatapoint instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::EnumDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::EnumDatapoint instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::EnumDatapointRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::EnumDatapoint from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::EnumDatapointRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::EnumDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static EnumDatapointServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::EnumDatapointRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::EnumDatapointRemoteObject> EnumDatapointServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::EnumDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return EnumDatapointServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void EnumDatapointServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	EnumDatapointServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string EnumDatapointServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::EnumDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return EnumDatapointServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string EnumDatapointServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::EnumDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return EnumDatapointServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void EnumDatapointServerHelper::unregisterObject(const std::string& uri)
{
	EnumDatapointServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, EnumDatapoint)


#endif // IoT_Devices_EnumDatapointServerHelper_INCLUDED

