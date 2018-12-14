//
// StateServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  StateServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_StateServerHelper_INCLUDED
#define IoT_Devices_StateServerHelper_INCLUDED


#include "IoT/Devices/IState.h"
#include "IoT/Devices/State.h"
#include "IoT/Devices/StateRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class StateServerHelper
	/// A State represents a sensor or device register that reports a state.
	///
	/// States are represented by unsigned int (Poco::UInt32) values.
	///
	/// An actual implementation should define possible states as
	/// an enum, and provide the read-only displayValue property
	/// that returns the current state as a string suitable for display.
{
public:
	typedef IoT::Devices::State Service;

	StateServerHelper();
		/// Creates a StateServerHelper.

	~StateServerHelper();
		/// Destroys the StateServerHelper.

	static Poco::AutoPtr<IoT::Devices::StateRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::State> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::State instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::State> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::State instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::StateRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::State from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::StateRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::State> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static StateServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::StateRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::StateRemoteObject> StateServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::State> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return StateServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void StateServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	StateServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string StateServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::State> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return StateServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string StateServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::StateRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return StateServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void StateServerHelper::unregisterObject(const std::string& uri)
{
	StateServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, State)


#endif // IoT_Devices_StateServerHelper_INCLUDED

