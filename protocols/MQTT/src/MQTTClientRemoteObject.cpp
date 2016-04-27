//
// MQTTClientRemoteObject.cpp
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


#include "IoT/MQTT/MQTTClientRemoteObject.h"
#include "IoT/MQTT/MQTTClientEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace MQTT {


MQTTClientRemoteObject::MQTTClientRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::MQTT::MQTTClient> pServiceObject):
	IoT::MQTT::IMQTTClient(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->connectionLost += Poco::delegate(this, &MQTTClientRemoteObject::event__connectionLost);
	_pServiceObject->messageArrived += Poco::delegate(this, &MQTTClientRemoteObject::event__messageArrived);
	_pServiceObject->messageDelivered += Poco::delegate(this, &MQTTClientRemoteObject::event__messageDelivered);
}


MQTTClientRemoteObject::~MQTTClientRemoteObject()
{
	try
	{
		_pServiceObject->connectionLost -= Poco::delegate(this, &MQTTClientRemoteObject::event__connectionLost);
		_pServiceObject->messageArrived -= Poco::delegate(this, &MQTTClientRemoteObject::event__messageArrived);
		_pServiceObject->messageDelivered -= Poco::delegate(this, &MQTTClientRemoteObject::event__messageDelivered);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string MQTTClientRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void MQTTClientRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new MQTTClientEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool MQTTClientRemoteObject::remoting__hasEvents() const
{
	return true;
}


void MQTTClientRemoteObject::event__connectionLost(const IoT::MQTT::ConnectionLostEvent& data)
{
	connectionLost(this, data);
}


void MQTTClientRemoteObject::event__messageArrived(const IoT::MQTT::MessageArrivedEvent& data)
{
	messageArrived(this, data);
}


void MQTTClientRemoteObject::event__messageDelivered(const IoT::MQTT::MessageDeliveredEvent& data)
{
	messageDelivered(this, data);
}


} // namespace MQTT
} // namespace IoT

