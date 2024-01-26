//
// StringDatapointServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  StringDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_StringDatapointServerHelper_INCLUDED
#define IoT_Devices_StringDatapointServerHelper_INCLUDED


#include "IoT/Devices/IStringDatapoint.h"
#include "IoT/Devices/StringDatapoint.h"
#include "IoT/Devices/StringDatapointRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class StringDatapointServerHelper
	/// The base class for datapoints holding a string value.
	///
	/// In addition to the methods defined in this interface,
	/// a StringDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Service = IoT::Devices::StringDatapoint;

	StringDatapointServerHelper();
		/// Creates a StringDatapointServerHelper.

	~StringDatapointServerHelper();
		/// Destroys the StringDatapointServerHelper.

	static Poco::AutoPtr<IoT::Devices::StringDatapointRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::StringDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::StringDatapoint instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::StringDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::StringDatapoint instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::StringDatapointRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::StringDatapoint from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::StringDatapointRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::StringDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static StringDatapointServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::StringDatapointRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::StringDatapointRemoteObject> StringDatapointServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::StringDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return StringDatapointServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void StringDatapointServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	StringDatapointServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string StringDatapointServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::StringDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return StringDatapointServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string StringDatapointServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::StringDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return StringDatapointServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void StringDatapointServerHelper::unregisterObject(const std::string& uri)
{
	StringDatapointServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, StringDatapoint)


#endif // IoT_Devices_StringDatapointServerHelper_INCLUDED

