//
// Types.h
//
// Library: IoT/MQTT
// Package: MQTTClient
// Module:  Types
//
// Definition of MQTT types.
//
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_MQTT_Types_INCLUDED
#define IoT_MQTT_Types_INCLUDED


#include "IoT/MQTT/MQTT.h"
#include "Poco/Optional.h"
#include <vector>


namespace IoT {
namespace MQTT {


enum MQTTVersion
	/// MQTT protocol version numbers.
{
	MQTT_VERSION_DEFAULT = 0,
	MQTT_VERSION_3_1     = 3,
	MQTT_VERSION_3_1_1   = 4,
	MQTT_VERSION_5       = 5
};


enum ReasonCode
	/// MQTT V5 Reason Codes
{
	REASON_SUCCESS = 0,
	REASON_NORMAL_DISCONNECTION = 0,
	REASON_GRANTED_QOS_0 = 0,
	REASON_GRANTED_QOS_1 = 1,
	REASON_GRANTED_QOS_2 = 2,
	REASON_DISCONNECT_WITH_WILL_MESSAGE = 4,
	REASON_NO_MATCHING_SUBSCRIBERS = 16,
	REASON_NO_SUBSCRIPTION_FOUND = 17,
	REASON_CONTINUE_AUTHENTICATION = 24,
	REASON_RE_AUTHENTICATE = 25,
	REASON_UNSPECIFIED_ERROR = 128,
	REASON_MALFORMED_PACKET = 129,
	REASON_PROTOCOL_ERROR = 130,
	REASON_IMPLEMENTATION_SPECIFIC_ERROR = 131,
	REASON_UNSUPPORTED_PROTOCOL_VERSION = 132,
	REASON_CLIENT_IDENTIFIER_NOT_VALID = 133,
	REASON_BAD_USER_NAME_OR_PASSWORD = 134,
	REASON_NOT_AUTHORIZED = 135,
	REASON_SERVER_UNAVAILABLE = 136,
	REASON_SERVER_BUSY = 137,
	REASON_BANNED = 138,
	REASON_SERVER_SHUTTING_DOWN = 139,
	REASON_BAD_AUTHENTICATION_METHOD = 140,
	REASON_KEEP_ALIVE_TIMEOUT = 141,
	REASON_SESSION_TAKEN_OVER = 142,
	REASON_TOPIC_FILTER_INVALID = 143,
	REASON_TOPIC_NAME_INVALID = 144,
	REASON_PACKET_IDENTIFIER_IN_USE = 145,
	REASON_PACKET_IDENTIFIER_NOT_FOUND = 146,
	REASON_RECEIVE_MAXIMUM_EXCEEDED = 147,
	REASON_TOPIC_ALIAS_INVALID = 148,
	REASON_PACKET_TOO_LARGE = 149,
	REASON_MESSAGE_RATE_TOO_HIGH = 150,
	REASON_QUOTA_EXCEEDED = 151,
	REASON_ADMINISTRATIVE_ACTION = 152,
	REASON_PAYLOAD_FORMAT_INVALID = 153,
	REASON_RETAIN_NOT_SUPPORTED = 154,
	REASON_QOS_NOT_SUPPORTED = 155,
	REASON_USE_ANOTHER_SERVER = 156,
	REASON_SERVER_MOVED = 157,
	REASON_SHARED_SUBSCRIPTIONS_NOT_SUPPORTED = 158,
	REASON_CONNECTION_RATE_EXCEEDED = 159,
	REASON_MAXIMUM_CONNECT_TIME = 160,
	REASON_SUBSCRIPTION_IDENTIFIERS_NOT_SUPPORTED = 161,
	REASON_WILDCARD_SUBSCRIPTIONS_NOT_SUPPORTED = 162
};


enum PropertyID
	/// MQTT V5 Property Identifier
{
	PROP_PAYLOAD_FORMAT_INDICATOR = 1,
	PROP_MESSAGE_EXPIRY_INTERVAL = 2,
	PROP_CONTENT_TYPE = 3,
	PROP_RESPONSE_TOPIC = 8,
	PROP_CORRELATION_DATA = 9,
	PROP_SUBSCRIPTION_IDENTIFIER = 11,
	PROP_SESSION_EXPIRY_INTERVAL = 17,
	PROP_ASSIGNED_CLIENT_IDENTIFER = 18,
	PROP_SERVER_KEEP_ALIVE = 19,
	PROP_AUTHENTICATION_METHOD = 21,
	PROP_AUTHENTICATION_DATA = 22,
	PROP_REQUEST_PROBLEM_INFORMATION = 23,
	PROP_WILL_DELAY_INTERVAL = 24,
	PROP_REQUEST_RESPONSE_INFORMATION = 25,
	PROP_RESPONSE_INFORMATION = 26,
	PROP_SERVER_REFERENCE = 28,
	PROP_REASON_STRING = 31,
	PROP_RECEIVE_MAXIMUM = 33,
	PROP_TOPIC_ALIAS_MAXIMUM = 34,
	PROP_TOPIC_ALIAS = 35,
	PROP_MAXIMUM_QOS = 36,
	PROP_RETAIN_AVAILABLE = 37,
	PROP_USER_PROPERTY = 38,
	PROP_MAXIMUM_PACKET_SIZE = 39,
	PROP_WILDCARD_SUBSCRIPTION_AVAILABLE = 40,
	PROP_SUBSCRIPTION_IDENTIFIERS_AVAILABLE = 41,
	PROP_SHARED_SUBSCRIPTION_AVAILABLE = 42
};


//@ serialize
struct Property
	/// MQTT V5 Property
{
	PropertyID identifier = PROP_USER_PROPERTY;
	Poco::Optional<Poco::UInt8> byteValue;
	Poco::Optional<Poco::UInt16> uint16Value;
	Poco::Optional<Poco::UInt32> uint32Value;
	Poco::Optional<std::string> stringValue;
	Poco::Optional<std::string> name;
};


//@ serialize
struct SubscribeOptions
	/// MQTT V5 Subscribe Options
{
	bool noLocal = false;
		/// Set to true to not receive own publications.
		/// Set to false for original MQTT behaviour - all messages matching the subscription are received.

	bool retainAsPublished = false;
		/// To keep the retain flag as on the original publish message, set to true.
		/// If false, defaults to the original MQTT behaviour where the retain flag is only set on
	    /// publications sent by a broker if in response to a subscribe request.

	int retainHandling = 0;
		///   * 0 - send retained messages at the time of the subscribe (original MQTT behaviour)
		///   * 1 - send retained messages on subscribe only if the subscription is new
		///   * 2 - do not send retained messages at all
};


//@ serialize
struct Response
	/// MQTT V5 Response
{
	Poco::UInt8 reasonCode = REASON_SUCCESS;
	std::vector<Poco::UInt8> reasonCodes;
	std::vector<Property> properties;
};


//@ serialize
struct PublishResult
	/// The result of a MQTT V5 publish operation.
{
	Response response;
		/// The MQTT response.

	int deliveryToken = 0;
		/// The delivery token, which can be used with the MQTTClient::messageDelivered
		/// event to verify that the message has been delivered.
};


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

	Message(const std::vector<char>& p, int q):
		binaryPayload(p),
		qos(q),
		retained(false)
	{
	}

	Message(std::string&& p, int q) :
		payload(p),
		qos(q),
		retained(false)
	{
	}

	Message(std::vector<char>&& p, int q) :
		binaryPayload(p),
		qos(q),
		retained(false)
	{
	}

	//@ optional
	std::string payload;
		/// The payload of the MQTT message.

	//@ optional
	std::vector<char> binaryPayload;
		/// Alternative binary payload, considered if payload is empty.

	int qos;
		/// The quality of service (QoS) assigned to the message.
		/// There are three levels of QoS:
		///   * 0: Fire and forget - the message may not be delivered.
		///   * 1: At least once - the message will be delivered, but may be
		///        delivered more than once in some circumstances.
		///   * 2: Once and one only - the message will be delivered exactly once.

	//@ optional
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

	//@ optional
	std::vector<Property> properties;
		/// The MQTT V5 properties associated with this message.
};


//@ serialize
struct MessageArrivedEvent
	/// Event arguments for MQTTClient::messageArrived.
{
	std::string topic;
		/// The topic the message has been published to.

	Message message;
		/// The published message.

	bool dup = false;
		/// The dup flag indicates whether or not this message is a duplicate.
		/// It is only meaningful when receiving QoS1 messages.
		/// When true, the client application should take appropriate action to
		/// deal with the duplicate message.

	bool handled = false;
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
	int token = 0;
		/// The delivery token.
};


//@ serialize
struct ConnectionLostEvent
	/// Event arguments for MQTTClient::connectionLost.
{
	std::string cause;
};


//@ serialize
struct DisconnectedEvent
	/// Event arguments for MQTT5Client::disconnected.
{
	std::vector<Property> properties;
		/// The MQTT V5 properties associated with this event.

	ReasonCode reasonCode = REASON_SUCCESS;
		/// Reason code reported by server.
};


//@ serialize
struct MessagePublishedEvent
	/// The MQTT V5 version of MessageDeliveredEvent.
{
	std::vector<Property> properties;
		/// The MQTT V5 properties associated with this event.

	int token = 0;
		/// The delivery token.

	ReasonCode reasonCode = REASON_SUCCESS;
		/// Reason code returned by server.
};


//@ serialize
struct ConnectionInfo
{
	int mqttVersion = MQTT_VERSION_DEFAULT;
		/// The MQTT version used in the connection (see MQTTVersion).

	std::string serverURI;
		/// URI of server the client is connected to.

	bool sessionPresent = false;
		/// True if a previously set up session is present on the server.

	std::vector<Property> properties;
		/// MQTT V5 properties returned by the server.
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

	int messageCount = 0;
		/// The number of messages published or received on this topic.
};


//@ serialize
struct Statistics
{
	std::vector<TopicCount> receivedMessages;
	std::vector<TopicCount> publishedMessages;
};


} } // namespace IoT::MQTT


#endif // IoT_MQTT_Types_INCLUDED
