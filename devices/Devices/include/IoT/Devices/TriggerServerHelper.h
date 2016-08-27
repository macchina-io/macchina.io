//
// TriggerServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  TriggerServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_TriggerServerHelper_INCLUDED
#define IoT_Devices_TriggerServerHelper_INCLUDED


#include "IoT/Devices/ITrigger.h"
#include "IoT/Devices/Trigger.h"
#include "IoT/Devices/TriggerRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class TriggerServerHelper
	/// The base class for triggers, such as
	/// push buttons or motion detectors.
	///
	/// In addition to the methods defined in this interface,
	/// a Trigger implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the trigger,
	///     formatted as string for display purposes.
{
public:
	typedef IoT::Devices::Trigger Service;

	TriggerServerHelper();
		/// Creates a TriggerServerHelper.

	~TriggerServerHelper();
		/// Destroys the TriggerServerHelper.

	static Poco::AutoPtr<IoT::Devices::TriggerRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::Trigger> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::Trigger instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::Trigger> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::Trigger instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::TriggerRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::Trigger from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::TriggerRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Trigger> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static TriggerServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::TriggerRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::TriggerRemoteObject> TriggerServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::Trigger> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return TriggerServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void TriggerServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	TriggerServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string TriggerServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::Trigger> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return TriggerServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string TriggerServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::TriggerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return TriggerServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void TriggerServerHelper::unregisterObject(const std::string& uri)
{
	TriggerServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, Trigger)


#endif // IoT_Devices_TriggerServerHelper_INCLUDED

