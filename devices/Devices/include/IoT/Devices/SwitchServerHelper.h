//
// SwitchServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SwitchServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SwitchServerHelper_INCLUDED
#define IoT_Devices_SwitchServerHelper_INCLUDED


#include "IoT/Devices/ISwitch.h"
#include "IoT/Devices/Switch.h"
#include "IoT/Devices/SwitchRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class SwitchServerHelper
	/// The base class for switchable things (that can
	/// be turned on and off).
	///
	/// A Switch has a current state and a target state.
	/// Depending upon the implementation, the current state
	/// and target state may be different for a short amount
	/// of time (e.g., while the device is powering on).
	///
	/// In addition to the methods defined in this interface,
	/// a Switch implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the Switch,
	///     formatted as string for display purposes.
{
public:
	typedef IoT::Devices::Switch Service;

	SwitchServerHelper();
		/// Creates a SwitchServerHelper.

	~SwitchServerHelper();
		/// Destroys the SwitchServerHelper.

	static Poco::AutoPtr<IoT::Devices::SwitchRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::Switch> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::Switch instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::Switch> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::Switch instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::SwitchRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::Switch from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::SwitchRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Switch> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static SwitchServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::SwitchRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::SwitchRemoteObject> SwitchServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::Switch> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return SwitchServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void SwitchServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	SwitchServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string SwitchServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::Switch> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return SwitchServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string SwitchServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::SwitchRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return SwitchServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void SwitchServerHelper::unregisterObject(const std::string& uri)
{
	SwitchServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, Switch)


#endif // IoT_Devices_SwitchServerHelper_INCLUDED

