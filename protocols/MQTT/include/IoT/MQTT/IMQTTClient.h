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
	///
	/// Implementations are expected to receive their client ID and
	/// server URI via an implementation defined configuration mechanism.
	/// Once configured, a MQTTClient always uses the same client ID and
	/// connects to the same server. A MQTT client should automatically
	/// attempt to reconnect if the connection to the server is lost.
{
public:
	typedef Poco::AutoPtr<IMQTTClient> Ptr;

	IMQTTClient();
		/// Creates a IMQTTClient.

	virtual ~IMQTTClient();
		/// Destroys the IMQTTClient.

	virtual IoT::MQTT::ConnectionInfo connect() = 0;
		/// Connects to the server if not already connected.
		///
		/// Normally, the client connects automatically when a message is
		/// published or a topic is subscribed to.
		///
		/// Returns a ConnectionInfo object containing information about the
		/// connection.
		///
		/// Fires the connected event if successful.
		///
		/// Throws a Poco::IOException if the connection cannot be established.

	virtual void connectAsync() = 0;
		/// Connects to the server if not already connected.
		///
		/// Connecting will be done asynchronously in a background thread.
		///
		/// A successful connection will be reported by firing the connected event.

	virtual bool connected() const = 0;
		/// Returns true if the client is currently connected to the server.

	virtual IoT::MQTT::ConnectionInfo connectionInfo() const = 0;
		/// Returns a ConnectionInfo structure describing the currently active
		/// connection. If not connected, the ConnectionInfo's serverURI will be empty.

	virtual void disconnect(int timeout) = 0;
		/// Disconnects from the server.
		///
		/// In order to allow the client time to complete handling of messages that are 
		/// in-flight when this function is called, a timeout period is specified (in milliseconds). 
		/// When the timeout period has expired, the client disconnects even if there 
		/// are still outstanding message acknowledgements. The next time the client 
		/// connects to the same server, any QoS 1 or 2 messages which have not completed 
		/// will be retried depending on the clean session settings for both the previous 
		/// and the new connection.

	virtual const std::string& id() const = 0;
		/// Returns the configured client ID.

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

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual const std::string& serverURI() const = 0;
		/// Returns the configured server URI.

	virtual IoT::MQTT::Statistics statistics() const = 0;
		/// Returns statistics about published and received topics and message counts.

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

	virtual std::vector < IoT::MQTT::TopicQoS > subscribedTopics() const = 0;
		/// Returns a vector containing all currently subscribed
		/// topics with their QoS level.

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

	Poco::BasicEvent < void > connectionClosed;
	Poco::BasicEvent < const ConnectionEstablishedEvent > connectionEstablished;
	Poco::BasicEvent < const ConnectionLostEvent > connectionLost;
	Poco::BasicEvent < const MessageArrivedEvent > messageArrived;
	Poco::BasicEvent < const MessageDeliveredEvent > messageDelivered;
};


} // namespace MQTT
} // namespace IoT


#endif // IoT_MQTT_IMQTTClient_INCLUDED

