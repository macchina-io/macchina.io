//
// MQTTClient.h
//
// $Id$
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
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MQTT_MQTTClient_INCLUDED
#define IoT_MQTT_MQTTClient_INCLUDED


#include "IoT/MQTT/MQTT.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include <vector>


namespace IoT {
namespace MQTT {


//@ serialize
struct Message
	/// This structure encapsulates a MQTT message.
{
	Message(int q = 0):
		qos(q),
		retained(false)
	{
	}
	
	Message(const std::string& p, int q):
		payload(p),
		qos(q),
		retained(false)
	{
	}
	
#if __cplusplus >= 201103L || (defined(_MSC_VER) && MSC_VER >= 1700)
	Message(std::string&& p, int q) :
		payload(p),
		qos(q),
		retained(false)
	{
	}
#endif

	std::string payload; 
		/// The payload of the MQTT message.

	int qos;
		/// The quality of service (QoS) assigned to the message. 
		/// There are three levels of QoS:
		///   * 0: Fire and forget - the message may not be delivered.
		///   * 1: At least once - the message will be delivered, but may be 
		///        delivered more than once in some circumstances.
		///   * 2: Once and one only - the message will be delivered exactly once.

	//@ mandatory=false
	bool retained;
		/// The retained flag serves two purposes depending on whether the message 
		/// it is associated with is being published or received.
		///
		///   * retained = true: For messages being published, a true setting 
		///     indicates that the MQTT server should retain a copy of the message. 
		///     The message will then be transmitted to new subscribers to a topic 
		///     that matches the message topic. For subscribers registering a new 
		///     subscription, the flag being true indicates that the received message 
		///     is not a new one, but one that has been retained by the MQTT server.
		///
		///   * retained = false: For publishers, this indicates that this message 
		///     should not be retained by the MQTT server. For subscribers, a false 
		///     setting indicates this is a normal message, received as a result of it 
		///     being published to the server.
};


//@ serialize
struct MessageArrivedEvent
	/// Event arguments for MQTTClient::messageArrived.
{
	std::string topic;   
		/// The topic the message has been published to.

	Message message; 
		/// The published message.

	bool dup;
		/// The dup flag indicates whether or not this message is a duplicate. 
		/// It is only meaningful when receiving QoS1 messages. 
		/// When true, the client application should take appropriate action to 
		/// deal with the duplicate message.
		
	bool handled;
		/// The handled flag must be set by the event delegate after processing
		/// of the message to indicate whether the message has been successfully
		/// processed. If set to false, the MQTT client will attempt to deliver
		/// the message again. The handled flag defaults to true. If the event delegate
		/// throws, the handled flag will be set to false by the framework. This 
		/// means that in most cases the delegate does not need to concern itself with 
		/// this flag.
};


//@ serialize
struct MessageDeliveredEvent
	/// Event arguments for MQTTClient::messageDelivered.
{
	int token;
		/// The delivery token.
};


//@ serialize
struct ConnectionLostEvent
	/// Event arguments for MQTTClient::connectionLost.
{
	std::string cause;
};


//@ serialize
struct ConnectionInfo
{
	std::string serverURI;
		/// URI of server the client is connected to.
		
	bool sessionPresent;
		/// True if a previously set up session is present on the server.
};


//@ serialize
struct ConnectionEstablishedEvent
	/// Event arguments for MQTTClient::connected.
{
	ConnectionInfo connectionInfo;	
};


//@ serialize
struct TopicQoS
	/// A vector of these is given to MQTTClient::subscribeMany.
{
	TopicQoS():
		qos(0)
	{
	}
	
	TopicQoS(const std::string& t, int q = 0):
		topic(t),
		qos(q)
	{
	}
	
	std::string topic;
		/// The topic name, which may contain wildcards.
		
	int qos;
		/// The QoS level (0, 1 or 2).
};


//@ serialize
struct TopicCount
{
	TopicCount():
		messageCount(0)
	{
	}
	
	TopicCount(const std::string& t, int c):
		topic(t),
		messageCount(c)
	{
	}

	std::string topic;
		/// The topic name.

	int messageCount;
		/// The number of messages published or received on this topic.
};


//@ serialize
struct Statistics
{
	std::vector<TopicCount> receivedMessages;
	std::vector<TopicCount> publishedMessages;
};


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
	typedef Poco::SharedPtr<MQTTClient> Ptr;

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
		
	virtual void connectAsync() = 0;
		/// Connects to the server if not already connected.
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

	virtual int publishMessage(const std::string& topic, const Message& message) = 0;
		/// Publishes the given message on the given topic.
		///
		/// Returns a delivery token which can be used with the messageDelivered
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
		
	virtual void unsubscribe(const std::string& topic) = 0;
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
		
	virtual void unsubscribeMany(const std::vector<std::string>& topics) = 0;
		/// This function attempts to remove existing subscriptions to a list of 
		/// topics made by the specified client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscriptions.
		
	virtual ConnectionInfo connectionInfo() const = 0;
		/// Returns a ConnectionInfo structure describing the currently active
		/// connection. If not connected, the ConnectionInfo's serverURI will be empty.
};


} } // namespace IoT::MQTT


#endif // IoT_MQTT_MQTTClient_INCLUDED
