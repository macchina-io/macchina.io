//
// MQTTClientRemoteObject.h
//
// Library: IoT/MQTT
// Package: Generated
// Module:  MQTTClientRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_MQTT_MQTTClientRemoteObject_INCLUDED
#define IoT_MQTT_MQTTClientRemoteObject_INCLUDED


#include "IoT/MQTT/IMQTTClient.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace MQTT {


class MQTTClientRemoteObject: public IoT::MQTT::IMQTTClient, public Poco::RemotingNG::RemoteObject
	/// The interface for MQTT clients.
	///
	/// Implementations are expected to receive their client ID and
	/// server URI via an implementation defined configuration mechanism.
	/// Once configured, a MQTTClient always uses the same client ID and
	/// connects to the same server. A MQTT client should automatically
	/// attempt to reconnect if the connection to the server is lost.
	///
	/// A single client instance can either support MQTT version 3.1/3.1.1
	/// or version 5. Which MQTT version is supported by the client is
	/// determined when configuring the client.
	///
	/// Users of the class must call the appropriate methods supporting
	/// the client's configured MQTT version.
{
public:
	using Ptr = Poco::AutoPtr<MQTTClientRemoteObject>;

	MQTTClientRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::MQTT::MQTTClient> pServiceObject);
		/// Creates a MQTTClientRemoteObject.

	virtual ~MQTTClientRemoteObject();
		/// Destroys the MQTTClientRemoteObject.

	IoT::MQTT::ConnectionInfo connect();
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
		///
		/// This method is only supported for MQTT 3.1 and 3.1.1.

	IoT::MQTT::ConnectionInfo connect5(const std::vector < IoT::MQTT::Property >& connectProperties, const std::vector < IoT::MQTT::Property >& willProperties);
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
		///
		/// This method is only supported for MQTT 5.

	virtual void connectAsync();
		/// Connects to the server if not already connected.
		///
		/// Connecting will be done asynchronously in a background thread.
		///
		/// A successful connection will be reported by firing the connected event.
		///
		/// This method is only supported for MQTT 3.1 and 3.1.1.

	virtual void connectAsync5(const std::vector < IoT::MQTT::Property >& connectProperties, const std::vector < IoT::MQTT::Property >& willProperties);
		/// MQTT V5 version of connectAsync().
		///
		/// Connects to the server if not already connected.
		///
		/// MQTT V5 connect and will properties can be specified.
		///
		/// Connecting will be done asynchronously in a background thread.
		///
		/// A successful connection will be reported by firing the connected event.
		///
		/// This method is only supported for MQTT 5.

	virtual bool connected() const;
		/// Returns true if the client is currently connected to the server.
		///
		/// This method is supported for all MQTT versions.

	IoT::MQTT::ConnectionInfo connectionInfo() const;
		/// Returns a ConnectionInfo structure describing the currently active
		/// connection. If not connected, the ConnectionInfo's serverURI will be empty.
		///
		/// This method is only supported for all MQTT versions.

	virtual void disconnect(int timeout);
		/// Disconnects from the server.
		///
		/// In order to allow the client time to complete handling of messages that are
		/// in-flight when this function is called, a timeout period is specified (in milliseconds).
		/// When the timeout period has expired, the client disconnects even if there
		/// are still outstanding message acknowledgements. The next time the client
		/// connects to the same server, any QoS 1 or 2 messages which have not completed
		/// will be retried depending on the clean session settings for both the previous
		/// and the new connection.
		///
		/// This method is only supported for MQTT 3.1 and 3.1.1.

	virtual void disconnect5(int timeout, IoT::MQTT::ReasonCode reason, const std::vector < IoT::MQTT::Property >& properties);
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
		///
		/// This method is only supported for MQTT 5.

	const std::string& id() const;
		/// Returns the configured client ID.
		///
		/// This method is only supported for all MQTT versions.

	virtual int mqttVersion() const;
		/// Returns the MQTT version supported by this client.
		///
		/// Possible return values are:
		///   - 0: client supports version 3.1 and 3.1.1
		///   - 3: client supports only version 3.1
		///   - 4: client supports only version 3.1.1
		///   - 5: client supports only version 5

	virtual std::vector < int > pendingDeliveryTokens();
		/// Returns a vector containing the delivery tokens for all messages
		/// still pending delivery.
		///
		/// This method is only supported for all MQTT versions.

	virtual int publish(const std::string& topic, const std::string& payload, int qos);
		/// Publishes the given message on the given topic, using the given QoS.
		///
		/// Returns a delivery token which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.
		///
		/// This method is only supported for MQTT 3.1 and 3.1.1.

	IoT::MQTT::PublishResult publish5(const std::string& topic, const std::string& payload, int qos, bool retained, const std::vector < IoT::MQTT::Property >& properties);
		/// MQTT V5 version of publish().
		///
		/// Publishes the given message on the given topic, using the given QoS.
		///
		/// Returns a PublishResult containing the result of the operation,
		/// as well as the delivery token, which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.
		///
		/// This method is only supported for MQTT 5.

	virtual int publishMessage(const std::string& topic, const IoT::MQTT::Message& message);
		/// Publishes the given message on the given topic.
		///
		/// Returns a delivery token which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.
		///
		/// This method is only supported for MQTT 3.1 and 3.1.1.

	IoT::MQTT::PublishResult publishMessage5(const std::string& topic, const IoT::MQTT::Message& message);
		/// MQTT V5 version of publishMessage().
		///
		/// Publishes the given message on the given topic.
		///
		/// Returns a PublishResult containing the result of the operation,
		/// as well as the delivery token, which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.
		///
		/// This method is only supported for MQTT 5.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	const std::string& serverURI() const;
		/// Returns the configured server URI.
		///
		/// This method is only supported for all MQTT versions.

	IoT::MQTT::Statistics statistics() const;
		/// Returns statistics about published and received topics and message counts.
		///
		/// This method is only supported for all MQTT versions.

	virtual void subscribe(const std::string& topic, int qos);
		/// This function attempts to subscribe the client to a single topic,
		/// which may contain wildcards. This call also specifies the Quality of service
		/// requested for the subscription.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscription.
		///
		/// This method is only supported for MQTT 3.1 and 3.1.1.

	IoT::MQTT::Response subscribe5(const std::string& topic, int qos, const IoT::MQTT::SubscribeOptions& options, const std::vector < IoT::MQTT::Property >& properties);
		/// MQTT V5 version of subscribe(), which allows to specify options and properties.
		///
		/// This function attempts to subscribe the client to a single topic,
		/// which may contain wildcards. This call also specifies the Quality of service
		/// requested for the subscription.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscription.
		///
		/// This method is only supported for MQTT 5.

	virtual void subscribeMany(const std::vector < IoT::MQTT::TopicQoS >& topicsAndQoS);
		/// This function attempts to subscribe the client to a list of topics (with
		/// associated QoS levels), which may contain wildcards.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscriptions.
		///
		/// This method is only supported for MQTT 3.1 and 3.1.1.

	IoT::MQTT::Response subscribeMany5(const std::vector < IoT::MQTT::TopicQoS >& topicsAndQoS, const IoT::MQTT::SubscribeOptions& options, const std::vector < IoT::MQTT::Property >& properties);
		/// MQTT V5 version of subscribeMany(), which allows to specify options and properties.
		///
		/// This function attempts to subscribe the client to a list of topics (with
		/// associated QoS levels), which may contain wildcards.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscriptions.
		///
		/// This method is only supported for MQTT 5.

	std::vector < IoT::MQTT::TopicQoS > subscribedTopics() const;
		/// Returns a vector containing all currently subscribed
		/// topics with their QoS level.
		///
		/// This method is supported for all MQTT versions.

	virtual void unsubscribe(const std::string& topic);
		/// This function attempts to remove an existing subscription made by the client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscription.
		///
		/// This method is only supported for MQTT 3.1 and 3.1.1.

	IoT::MQTT::Response unsubscribe5(const std::string& topic, const std::vector < IoT::MQTT::Property >& properties);
		/// MQTT V5 version of unsubscribe(), which allows to specify properties.
		///
		/// This function attempts to remove an existing subscription made by the client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscription.
		///
		/// This method is only supported for MQTT 5.

	virtual void unsubscribeMany(const std::vector < std::string >& topics);
		/// This function attempts to remove existing subscriptions to a list of
		/// topics made by the specified client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscriptions.
		///
		/// This method is only supported for MQTT 3.1 and 3.1.1.

	IoT::MQTT::Response unsubscribeMany5(const std::vector < std::string >& topics, const std::vector < IoT::MQTT::Property >& properties);
		/// MQTT V5 version of unsubscribeMany(), which allows to specify properties.
		///
		/// This function attempts to remove existing subscriptions to a list of
		/// topics made by the specified client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscriptions.
		///
		/// This method is only supported for MQTT 5.

	virtual void waitForCompletion(int deliveryToken, int timeout);
		/// Waits for delivery of the message associated with the given deliveryToken.
		///
		/// Waits at most for the length of the given timeout in milliseconds.
		/// Throws a Poco::TimeoutException if timeout expires without the
		/// message delivery being completed.
		///
		/// This method is only supported for all MQTT versions.

protected:
	void event__connectionClosed();

	void event__connectionEstablished(const IoT::MQTT::ConnectionEstablishedEvent& data);

	void event__connectionLost(const IoT::MQTT::ConnectionLostEvent& data);

	void event__disconnected(const IoT::MQTT::DisconnectedEvent& data);

	void event__messageArrived(const IoT::MQTT::MessageArrivedEvent& data);

	void event__messageDelivered(const IoT::MQTT::MessageDeliveredEvent& data);

	void event__messagePublished(const IoT::MQTT::MessagePublishedEvent& data);

private:
	Poco::SharedPtr<IoT::MQTT::MQTTClient> _pServiceObject;
};


inline IoT::MQTT::ConnectionInfo MQTTClientRemoteObject::connect()
{
	return _pServiceObject->connect();
}


inline IoT::MQTT::ConnectionInfo MQTTClientRemoteObject::connect5(const std::vector < IoT::MQTT::Property >& connectProperties, const std::vector < IoT::MQTT::Property >& willProperties)
{
	return _pServiceObject->connect5(connectProperties, willProperties);
}


inline void MQTTClientRemoteObject::connectAsync()
{
	_pServiceObject->connectAsync();
}


inline void MQTTClientRemoteObject::connectAsync5(const std::vector < IoT::MQTT::Property >& connectProperties, const std::vector < IoT::MQTT::Property >& willProperties)
{
	_pServiceObject->connectAsync5(connectProperties, willProperties);
}


inline bool MQTTClientRemoteObject::connected() const
{
	return _pServiceObject->connected();
}


inline IoT::MQTT::ConnectionInfo MQTTClientRemoteObject::connectionInfo() const
{
	return _pServiceObject->connectionInfo();
}


inline void MQTTClientRemoteObject::disconnect(int timeout)
{
	_pServiceObject->disconnect(timeout);
}


inline void MQTTClientRemoteObject::disconnect5(int timeout, IoT::MQTT::ReasonCode reason, const std::vector < IoT::MQTT::Property >& properties)
{
	_pServiceObject->disconnect5(timeout, reason, properties);
}


inline const std::string& MQTTClientRemoteObject::id() const
{
	return _pServiceObject->id();
}


inline int MQTTClientRemoteObject::mqttVersion() const
{
	return _pServiceObject->mqttVersion();
}


inline std::vector < int > MQTTClientRemoteObject::pendingDeliveryTokens()
{
	return _pServiceObject->pendingDeliveryTokens();
}


inline int MQTTClientRemoteObject::publish(const std::string& topic, const std::string& payload, int qos)
{
	return _pServiceObject->publish(topic, payload, qos);
}


inline IoT::MQTT::PublishResult MQTTClientRemoteObject::publish5(const std::string& topic, const std::string& payload, int qos, bool retained, const std::vector < IoT::MQTT::Property >& properties)
{
	return _pServiceObject->publish5(topic, payload, qos, retained, properties);
}


inline int MQTTClientRemoteObject::publishMessage(const std::string& topic, const IoT::MQTT::Message& message)
{
	return _pServiceObject->publishMessage(topic, message);
}


inline IoT::MQTT::PublishResult MQTTClientRemoteObject::publishMessage5(const std::string& topic, const IoT::MQTT::Message& message)
{
	return _pServiceObject->publishMessage5(topic, message);
}


inline const Poco::RemotingNG::Identifiable::TypeId& MQTTClientRemoteObject::remoting__typeId() const
{
	return IMQTTClient::remoting__typeId();
}


inline const std::string& MQTTClientRemoteObject::serverURI() const
{
	return _pServiceObject->serverURI();
}


inline IoT::MQTT::Statistics MQTTClientRemoteObject::statistics() const
{
	return _pServiceObject->statistics();
}


inline void MQTTClientRemoteObject::subscribe(const std::string& topic, int qos)
{
	_pServiceObject->subscribe(topic, qos);
}


inline IoT::MQTT::Response MQTTClientRemoteObject::subscribe5(const std::string& topic, int qos, const IoT::MQTT::SubscribeOptions& options, const std::vector < IoT::MQTT::Property >& properties)
{
	return _pServiceObject->subscribe5(topic, qos, options, properties);
}


inline void MQTTClientRemoteObject::subscribeMany(const std::vector < IoT::MQTT::TopicQoS >& topicsAndQoS)
{
	_pServiceObject->subscribeMany(topicsAndQoS);
}


inline IoT::MQTT::Response MQTTClientRemoteObject::subscribeMany5(const std::vector < IoT::MQTT::TopicQoS >& topicsAndQoS, const IoT::MQTT::SubscribeOptions& options, const std::vector < IoT::MQTT::Property >& properties)
{
	return _pServiceObject->subscribeMany5(topicsAndQoS, options, properties);
}


inline std::vector < IoT::MQTT::TopicQoS > MQTTClientRemoteObject::subscribedTopics() const
{
	return _pServiceObject->subscribedTopics();
}


inline void MQTTClientRemoteObject::unsubscribe(const std::string& topic)
{
	_pServiceObject->unsubscribe(topic);
}


inline IoT::MQTT::Response MQTTClientRemoteObject::unsubscribe5(const std::string& topic, const std::vector < IoT::MQTT::Property >& properties)
{
	return _pServiceObject->unsubscribe5(topic, properties);
}


inline void MQTTClientRemoteObject::unsubscribeMany(const std::vector < std::string >& topics)
{
	_pServiceObject->unsubscribeMany(topics);
}


inline IoT::MQTT::Response MQTTClientRemoteObject::unsubscribeMany5(const std::vector < std::string >& topics, const std::vector < IoT::MQTT::Property >& properties)
{
	return _pServiceObject->unsubscribeMany5(topics, properties);
}


inline void MQTTClientRemoteObject::waitForCompletion(int deliveryToken, int timeout)
{
	_pServiceObject->waitForCompletion(deliveryToken, timeout);
}


} // namespace MQTT
} // namespace IoT


#endif // IoT_MQTT_MQTTClientRemoteObject_INCLUDED

