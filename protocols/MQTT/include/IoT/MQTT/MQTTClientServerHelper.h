//
// MQTTClientServerHelper.h
//
// Library: IoT/MQTT
// Package: Generated
// Module:  MQTTClientServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MQTT_MQTTClientServerHelper_INCLUDED
#define IoT_MQTT_MQTTClientServerHelper_INCLUDED


#include "IoT/MQTT/IMQTTClient.h"
#include "IoT/MQTT/MQTTClient.h"
#include "IoT/MQTT/MQTTClientRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace MQTT {


class MQTTClientServerHelper
	/// The interface for MQTT clients.
	///
	/// Implementations are expected to receive their client ID and
	/// server URI via an implementation defined configuration mechanism.
	/// Once configured, a MQTTClient always uses the same client ID and
	/// connects to the same server. A MQTT client should automatically
	/// attempt to reconnect if the connection to the server is lost.
{
public:
	typedef IoT::MQTT::MQTTClient Service;

	MQTTClientServerHelper();
		/// Creates a MQTTClientServerHelper.

	~MQTTClientServerHelper();
		/// Destroys the MQTTClientServerHelper.

	static Poco::AutoPtr<IoT::MQTT::MQTTClientRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::MQTT::MQTTClient> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::MQTT::MQTTClient instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::MQTT::MQTTClient> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::MQTT::MQTTClient instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::MQTT::MQTTClientRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::MQTT::MQTTClient from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::MQTT::MQTTClientRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::MQTT::MQTTClient> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static MQTTClientServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::MQTT::MQTTClientRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::MQTT::MQTTClientRemoteObject> MQTTClientServerHelper::createRemoteObject(Poco::SharedPtr<IoT::MQTT::MQTTClient> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return MQTTClientServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void MQTTClientServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	MQTTClientServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string MQTTClientServerHelper::registerObject(Poco::SharedPtr<IoT::MQTT::MQTTClient> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return MQTTClientServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string MQTTClientServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::MQTT::MQTTClientRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return MQTTClientServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void MQTTClientServerHelper::unregisterObject(const std::string& uri)
{
	MQTTClientServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace MQTT
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::MQTT, MQTTClient)


#endif // IoT_MQTT_MQTTClientServerHelper_INCLUDED

