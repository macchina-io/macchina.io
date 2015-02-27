//
// MQTTClientEventDispatcher.h
//
// Library: IoT/MQTT
// Package: Generated
// Module:  MQTTClientEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MQTT_MQTTClientEventDispatcher_INCLUDED
#define IoT_MQTT_MQTTClientEventDispatcher_INCLUDED


#include "IoT/MQTT/MQTTClientRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace MQTT {


class MQTTClientEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The interface for MQTT clients.
{
public:
	MQTTClientEventDispatcher(MQTTClientRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a MQTTClientEventDispatcher.

	virtual ~MQTTClientEventDispatcher();
		/// Destroys the MQTTClientEventDispatcher.

	void event__connectionLost(const void* pSender, const IoT::MQTT::ConnectionLostEvent& data);

	void event__messageArrived(const void* pSender, const IoT::MQTT::MessageArrivedEvent& data);

	void event__messageDelivered(const void* pSender, const IoT::MQTT::MessageDeliveredEvent& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__connectionLostImpl(const std::string& subscriberURI, const IoT::MQTT::ConnectionLostEvent& data);

	void event__messageArrivedImpl(const std::string& subscriberURI, const IoT::MQTT::MessageArrivedEvent& data);

	void event__messageDeliveredImpl(const std::string& subscriberURI, const IoT::MQTT::MessageDeliveredEvent& data);

	static const std::string DEFAULT_NS;
	MQTTClientRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& MQTTClientEventDispatcher::remoting__typeId() const
{
	return IMQTTClient::remoting__typeId();
}


} // namespace MQTT
} // namespace IoT


#endif // IoT_MQTT_MQTTClientEventDispatcher_INCLUDED

