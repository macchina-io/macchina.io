//
// DatapointServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  DatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_DatapointServerHelper_INCLUDED
#define IoT_Devices_DatapointServerHelper_INCLUDED


#include "IoT/Devices/Datapoint.h"
#include "IoT/Devices/DatapointRemoteObject.h"
#include "IoT/Devices/IDatapoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class DatapointServerHelper
	/// The base class for datapoints.
	/// Datapoints typically represent the result of
	/// sensor measurements, or data obtained from monitoring
	/// processes.
	///
	/// The main difference between a Datapoint and a Sensor is
	/// that a Sensor is typically an interface to a specific
	/// device (i.e., a temperature sensor), whereas a Datapoint 
	/// holds a value that has been acquired from another
	/// device (via a network or bus system) or computed
	/// from other data points.
	///
	/// In addition to the methods defined in this interface,
	/// a Sensor implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
	///   - updated (timestamp, optional): The point in time when the
	///     datapoint's value was last updated.
	///   - access (string, optional): Access permissions ("rw" - read/write,
	///     "ro" - read-only, "wo" - write-only).
	///
	/// Subclasses of Datapoint implement specific value types.
{
public:
	using Service = IoT::Devices::Datapoint;

	DatapointServerHelper();
		/// Creates a DatapointServerHelper.

	~DatapointServerHelper();
		/// Destroys the DatapointServerHelper.

	static Poco::AutoPtr<IoT::Devices::DatapointRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::Datapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::Datapoint instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::Datapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::Datapoint instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::DatapointRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::Datapoint from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::DatapointRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Datapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static DatapointServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::DatapointRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::DatapointRemoteObject> DatapointServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::Datapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return DatapointServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void DatapointServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	DatapointServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string DatapointServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::Datapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return DatapointServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string DatapointServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::DatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return DatapointServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void DatapointServerHelper::unregisterObject(const std::string& uri)
{
	DatapointServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, Datapoint)


#endif // IoT_Devices_DatapointServerHelper_INCLUDED

