//
// BooleanSensorServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  BooleanSensorServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_BooleanSensorServerHelper_INCLUDED
#define IoT_Devices_BooleanSensorServerHelper_INCLUDED


#include "IoT/Devices/BooleanSensor.h"
#include "IoT/Devices/BooleanSensorRemoteObject.h"
#include "IoT/Devices/IBooleanSensor.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class BooleanSensorServerHelper
	/// The base class for two-state sensors measuring
	/// on/off or open/closed state.
	///
	/// In addition to the methods defined in this interface,
	/// a BooleanSensor implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the trigger,
	///     formatted as string for display purposes.
{
public:
	typedef IoT::Devices::BooleanSensor Service;

	BooleanSensorServerHelper();
		/// Creates a BooleanSensorServerHelper.

	~BooleanSensorServerHelper();
		/// Destroys the BooleanSensorServerHelper.

	static Poco::AutoPtr<IoT::Devices::BooleanSensorRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::BooleanSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::BooleanSensor instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::BooleanSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::BooleanSensor instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::BooleanSensorRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::BooleanSensor from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::BooleanSensorRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::BooleanSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static BooleanSensorServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::BooleanSensorRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::BooleanSensorRemoteObject> BooleanSensorServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::BooleanSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return BooleanSensorServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void BooleanSensorServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	BooleanSensorServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string BooleanSensorServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::BooleanSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return BooleanSensorServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string BooleanSensorServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::BooleanSensorRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return BooleanSensorServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void BooleanSensorServerHelper::unregisterObject(const std::string& uri)
{
	BooleanSensorServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, BooleanSensor)


#endif // IoT_Devices_BooleanSensorServerHelper_INCLUDED

