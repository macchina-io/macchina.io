//
// ScalarDatapointServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ScalarDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_ScalarDatapointServerHelper_INCLUDED
#define IoT_Devices_ScalarDatapointServerHelper_INCLUDED


#include "IoT/Devices/IScalarDatapoint.h"
#include "IoT/Devices/ScalarDatapoint.h"
#include "IoT/Devices/ScalarDatapointRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class ScalarDatapointServerHelper
	/// A scalar datapoint holding a single numeric (double) value.
	///
	/// In addition to the methods defined in this interface,
	/// a ScalarDatapoint implementation should expose the following
	/// properties:
	///   - physicalQuantity (string): The physical quantity that is
	///     being measured by the datapoint, e.g. "temperature".
	///   - physicalUnit (string): The physical unit the measured value
	///     is being represented in (e.g. "Cel" for degree Celsius).
	///     This should use the "c/s" symbols from the Unified Code for Units of Measure
	///     (http://unitsofmeasure.org/ucum.html).
	///     See the PHYSICAL_UNIT_* strings for predefined values.
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	using Service = IoT::Devices::ScalarDatapoint;

	ScalarDatapointServerHelper();
		/// Creates a ScalarDatapointServerHelper.

	~ScalarDatapointServerHelper();
		/// Destroys the ScalarDatapointServerHelper.

	static Poco::AutoPtr<IoT::Devices::ScalarDatapointRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::ScalarDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::ScalarDatapoint instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::ScalarDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::ScalarDatapoint instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::ScalarDatapointRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::ScalarDatapoint from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::ScalarDatapointRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::ScalarDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static ScalarDatapointServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::ScalarDatapointRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::ScalarDatapointRemoteObject> ScalarDatapointServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::ScalarDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return ScalarDatapointServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void ScalarDatapointServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	ScalarDatapointServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string ScalarDatapointServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::ScalarDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return ScalarDatapointServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string ScalarDatapointServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::ScalarDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return ScalarDatapointServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void ScalarDatapointServerHelper::unregisterObject(const std::string& uri)
{
	ScalarDatapointServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, ScalarDatapoint)


#endif // IoT_Devices_ScalarDatapointServerHelper_INCLUDED

