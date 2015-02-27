//
// IMQTTClient.h
//
// Library: IoT/MQTT
// Package: Generated
// Module:  IMQTTClient
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MQTT_IMQTTClient_INCLUDED
#define IoT_MQTT_IMQTTClient_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace MQTT {


class IMQTTClient: public Poco::OSP::Service
	/// The interface for MQTT clients.
{
public:
	typedef Poco::AutoPtr<IMQTTClient> Ptr;

	IMQTTClient();
		/// Creates a IMQTTClient.

	virtual ~IMQTTClient();
		/// Destroys the IMQTTClient.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual int publish(const std::string& topic, const std::string& payload, int qos) = 0;
		/// Publishes the given message on the given topic, using the given QoS.
		///
		/// Returns a delivery token which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.

	virtual int publishMessage(const std::string& topic, const IoT::MQTT::Message& message) = 0;
		/// Publishes the given message on the given topic.
		///
		/// Returns a delivery token which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.

	virtual void remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void subscribe(const std::string& topic, int qos) = 0;
		/// This function attempts to subscribe the client to a single topic, 
		/// which may contain wildcards. This call also specifies the Quality of service 
		/// requested for the subscription.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscription.

	virtual void subscribeMany(const std::vector < IoT::MQTT::TopicQoS >& topicsAndQoS) = 0;
		/// This function attempts to subscribe the client to a list of topics (with
		/// associated QoS levels), which may contain wildcards.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscriptions.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual void unsubscribe(const std::string& topic) = 0;
		/// This function attempts to remove an existing subscription made by the client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscription.

	virtual void unsubscribeMany(const std::vector < std::string >& topics) = 0;
		/// This function attempts to remove existing subscriptions to a list of 
		/// topics made by the specified client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscriptions.

	Poco::BasicEvent < const ConnectionLostEvent > connectionLost;
	Poco::BasicEvent < const MessageArrivedEvent > messageArrived;
	Poco::BasicEvent < const MessageDeliveredEvent > messageDelivered;
};


} // namespace MQTT
} // namespace IoT


#endif // IoT_MQTT_IMQTTClient_INCLUDED

