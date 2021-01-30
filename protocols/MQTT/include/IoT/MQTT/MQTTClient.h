//
// MQTTClient.h
//
// Library: IoT/MQTT
// Package: MQTTClient
// Module:  MQTTClient
//
// Definition of the MQTTClient interface.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_MQTT_MQTTClient_INCLUDED
#define IoT_MQTT_MQTTClient_INCLUDED


#include "IoT/MQTT/MQTT.h"
#include "IoT/MQTT/Types.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include <vector>


namespace IoT {
namespace MQTT {


//@ remote
class IoTMQTT_API MQTTClient
	/// The interface for MQTT clients.
	///
	/// Implementations are expected to receive their client ID and
	/// server URI via an implementation defined configuration mechanism.
	/// Once configured, a MQTTClient always uses the same client ID and
	/// connects to the same server. A MQTT client should automatically
	/// attempt to reconnect if the connection to the server is lost.
{
public:
	using Ptr = Poco::SharedPtr<MQTTClient>;

	Poco::BasicEvent<const MessageArrivedEvent> messageArrived;
		/// Fired when a message has been received for one of
		/// the subscribed topics.

	Poco::BasicEvent<const MessageDeliveredEvent> messageDelivered;
		/// Fired when a message has been delivered.

	Poco::BasicEvent<const ConnectionEstablishedEvent> connectionEstablished;
		/// Fired when a connection to the MQTT server has been established.

	Poco::BasicEvent<void> connectionClosed;
		/// Fired when the client has disconnected from the server.

	Poco::BasicEvent<const ConnectionLostEvent> connectionLost;
		/// Fired when the connection to the MQTT server has been lost.

	Poco::BasicEvent<const DisconnectedEvent> disconnected;
		/// Fired when a disconnect packed has been received from the server
		/// (MQTT V5 only).

	Poco::BasicEvent<const MessagePublishedEvent> messagePublished;
		/// Fired when a message has been delivered.
		/// This is the MQTT V5 version of messageDelivered.

	MQTTClient();
		/// Creates the MQTTClient.

	virtual ~MQTTClient();
		/// Destroys the MQTTClient.

	virtual const std::string& id() const = 0;
		/// Returns the configured client ID.

	virtual const std::string& serverURI() const = 0;
		/// Returns the configured server URI.

	virtual bool connected() const = 0;
		/// Returns true if the client is currently connected to the server.

	virtual ConnectionInfo connect() = 0;
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

	virtual ConnectionInfo connect5(const std::vector<Property>& connectProperties, const std::vector<Property>& willProperties) = 0;
		/// MQTT V5 version of connect().
		///
		/// Connects to the server if not already connected.
		///
		/// MQTT V5 connect and will properties can be specified.
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

	virtual void connectAsync5(const std::vector<Property>& connectProperties, const std::vector<Property>& willProperties) = 0;
		/// MQTT V5 version of connectAsync().
		///
		/// Connects to the server if not already connected.
		///
		/// MQTT V5 connect and will properties can be specified.
		///
		/// Connecting will be done asynchronously in a background thread.
		///
		/// A successful connection will be reported by firing the connected event.

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

	virtual void disconnect5(int timeout, ReasonCode reason, const std::vector<Property>& properties) = 0;
		/// MQTT V5 version of disconnect().
		///
		/// Disconnects from the server.
		///
		/// MQTT V5 reason code and properties can be given.
		///
		/// In order to allow the client time to complete handling of messages that are
		/// in-flight when this function is called, a timeout period is specified (in milliseconds).
		/// When the timeout period has expired, the client disconnects even if there
		/// are still outstanding message acknowledgements. The next time the client
		/// connects to the same server, any QoS 1 or 2 messages which have not completed
		/// will be retried depending on the clean session settings for both the previous
		/// and the new connection.

	virtual std::vector<TopicQoS> subscribedTopics() const = 0;
		/// Returns a vector containing all currently subscribed
		/// topics with their QoS level.

	virtual Statistics statistics() const = 0;
		/// Returns statistics about published and received topics and message counts.

	virtual int publish(const std::string& topic, const std::string& payload, int qos) = 0;
		/// Publishes the given message on the given topic, using the given QoS.
		///
		/// Returns a delivery token which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.

	virtual PublishResult publish5(const std::string& topic, const std::string& payload, int qos, bool retained, const std::vector<Property>& properties) = 0;
		/// MQTT V5 version of publish().
		///
		/// Publishes the given message on the given topic, using the given QoS.
		///
		/// Returns a PublishResult containing the result of the operation,
		/// as well as the delivery token, which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.

	virtual int publishMessage(const std::string& topic, const Message& message) = 0;
		/// Publishes the given message on the given topic.
		///
		/// Returns a delivery token which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.

	virtual PublishResult publishMessage5(const std::string& topic, const Message& message) = 0;
		/// MQTT V5 version of publishMessage().
		///
		/// Publishes the given message on the given topic.
		///
		/// Returns a PublishResult containing the result of the operation,
		/// as well as the delivery token, which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.

	virtual void subscribe(const std::string& topic, int qos) = 0;
		/// This function attempts to subscribe the client to a single topic,
		/// which may contain wildcards. This call also specifies the Quality of service
		/// requested for the subscription.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscription.

	virtual Response subscribe5(const std::string& topic, int qos, const SubscribeOptions& options, const std::vector<Property>& properties) = 0;
		/// MQTT V5 version of subscribe(), which allows to specify options and properties.
		///
		/// This function attempts to subscribe the client to a single topic,
		/// which may contain wildcards. This call also specifies the Quality of service
		/// requested for the subscription.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscription.

	virtual void unsubscribe(const std::string& topic) = 0;
		/// This function attempts to remove an existing subscription made by the client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscription.

	virtual Response unsubscribe5(const std::string& topic, const std::vector<Property>& properties) = 0;
		/// MQTT V5 version of unsubscribe(), which allows to specify properties.
		///
		/// This function attempts to remove an existing subscription made by the client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscription.

	virtual void subscribeMany(const std::vector<TopicQoS>& topicsAndQoS) = 0;
		/// This function attempts to subscribe the client to a list of topics (with
		/// associated QoS levels), which may contain wildcards.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscriptions.

	virtual Response subscribeMany5(const std::vector<TopicQoS>& topicsAndQoS, const SubscribeOptions& options, const std::vector<Property>& properties) = 0;
		/// MQTT V5 version of subscribeMany(), which allows to specify options and properties.
		///
		/// This function attempts to subscribe the client to a list of topics (with
		/// associated QoS levels), which may contain wildcards.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscriptions.

	virtual void unsubscribeMany(const std::vector<std::string>& topics) = 0;
		/// This function attempts to remove existing subscriptions to a list of
		/// topics made by the specified client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscriptions.

	virtual Response unsubscribeMany5(const std::vector<std::string>& topics, const std::vector<Property>& properties) = 0;
		/// MQTT V5 version of unsubscribeMany(), which allows to specify properties.
		///
		/// This function attempts to remove existing subscriptions to a list of
		/// topics made by the specified client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscriptions.

	virtual void waitForCompletion(int deliveryToken, int timeout) = 0;
		/// Waits for delivery of the message associated with the given deliveryToken.
		///
		/// Waits at most for the length of the given timeout in milliseconds.
		/// Throws a Poco::TimeoutException if timeout expires without the
		/// message delivery being completed.

	virtual std::vector<int> pendingDeliveryTokens() = 0;
		/// Returns a vector containing the delivery tokens for all messages
		/// still pending delivery.

	virtual ConnectionInfo connectionInfo() const = 0;
		/// Returns a ConnectionInfo structure describing the currently active
		/// connection. If not connected, the ConnectionInfo's serverURI will be empty.
};


} } // namespace IoT::MQTT


#endif // IoT_MQTT_MQTTClient_INCLUDED
