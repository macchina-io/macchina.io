//
// RotaryEncoderServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  RotaryEncoderServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_RotaryEncoderServerHelper_INCLUDED
#define IoT_Devices_RotaryEncoderServerHelper_INCLUDED


#include "IoT/Devices/IRotaryEncoder.h"
#include "IoT/Devices/RotaryEncoder.h"
#include "IoT/Devices/RotaryEncoderRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class RotaryEncoderServerHelper
	/// A rotary encoder with an optional push button.
{
public:
	typedef IoT::Devices::RotaryEncoder Service;

	RotaryEncoderServerHelper();
		/// Creates a RotaryEncoderServerHelper.

	~RotaryEncoderServerHelper();
		/// Destroys the RotaryEncoderServerHelper.

	static Poco::AutoPtr<IoT::Devices::RotaryEncoderRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::RotaryEncoder> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::RotaryEncoder instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::RotaryEncoder> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::RotaryEncoder instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::RotaryEncoderRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::RotaryEncoder from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::RotaryEncoderRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::RotaryEncoder> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static RotaryEncoderServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::RotaryEncoderRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::RotaryEncoderRemoteObject> RotaryEncoderServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::RotaryEncoder> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return RotaryEncoderServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void RotaryEncoderServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	RotaryEncoderServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string RotaryEncoderServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::RotaryEncoder> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return RotaryEncoderServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string RotaryEncoderServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::RotaryEncoderRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return RotaryEncoderServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void RotaryEncoderServerHelper::unregisterObject(const std::string& uri)
{
	RotaryEncoderServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, RotaryEncoder)


#endif // IoT_Devices_RotaryEncoderServerHelper_INCLUDED

