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
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
{
public:
	typedef Poco::AutoPtr<MQTTClientRemoteObject> Ptr;

	MQTTClientRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::MQTT::MQTTClient> pServiceObject);
		/// Creates a MQTTClientRemoteObject.

	virtual ~MQTTClientRemoteObject();
		/// Destroys the MQTTClientRemoteObject.

	virtual int publish(const std::string& topic, const std::string& payload, int qos);
		/// Publishes the given message on the given topic, using the given QoS.
		///
		/// Returns a delivery token which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.

	virtual int publishMessage(const std::string& topic, const IoT::MQTT::Message& message);
		/// Publishes the given message on the given topic.
		///
		/// Returns a delivery token which can be used with the messageDelivered
		/// event to verify that the message has been delivered.
		///
		/// Throws a Poco::IOException if the message cannot be published.

	virtual void remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void subscribe(const std::string& topic, int qos);
		/// This function attempts to subscribe the client to a single topic, 
		/// which may contain wildcards. This call also specifies the Quality of service 
		/// requested for the subscription.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscription.

	virtual void subscribeMany(const std::vector < IoT::MQTT::TopicQoS >& topicsAndQoS);
		/// This function attempts to subscribe the client to a list of topics (with
		/// associated QoS levels), which may contain wildcards.
		///
		/// Throws a Poco::IOException if there was a problem registering the
		/// subscriptions.

	virtual void unsubscribe(const std::string& topic);
		/// This function attempts to remove an existing subscription made by the client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscription.

	virtual void unsubscribeMany(const std::vector < std::string >& topics);
		/// This function attempts to remove existing subscriptions to a list of 
		/// topics made by the specified client.
		///
		/// Throws a Poco::IOException if there was a problem removing the
		/// subscriptions.

protected:
	void event__connectionLost(const IoT::MQTT::ConnectionLostEvent& data);

	void event__messageArrived(const IoT::MQTT::MessageArrivedEvent& data);

	void event__messageDelivered(const IoT::MQTT::MessageDeliveredEvent& data);

private:
	Poco::SharedPtr<IoT::MQTT::MQTTClient> _pServiceObject;
};


inline int MQTTClientRemoteObject::publish(const std::string& topic, const std::string& payload, int qos)
{
	return _pServiceObject->publish(topic, payload, qos);
}


inline int MQTTClientRemoteObject::publishMessage(const std::string& topic, const IoT::MQTT::Message& message)
{
	return _pServiceObject->publishMessage(topic, message);
}


inline const Poco::RemotingNG::Identifiable::TypeId& MQTTClientRemoteObject::remoting__typeId() const
{
	return IMQTTClient::remoting__typeId();
}


inline void MQTTClientRemoteObject::subscribe(const std::string& topic, int qos)
{
	_pServiceObject->subscribe(topic, qos);
}


inline void MQTTClientRemoteObject::subscribeMany(const std::vector < IoT::MQTT::TopicQoS >& topicsAndQoS)
{
	_pServiceObject->subscribeMany(topicsAndQoS);
}


inline void MQTTClientRemoteObject::unsubscribe(const std::string& topic)
{
	_pServiceObject->unsubscribe(topic);
}


inline void MQTTClientRemoteObject::unsubscribeMany(const std::vector < std::string >& topics)
{
	_pServiceObject->unsubscribeMany(topics);
}


} // namespace MQTT
} // namespace IoT


#endif // IoT_MQTT_MQTTClientRemoteObject_INCLUDED

