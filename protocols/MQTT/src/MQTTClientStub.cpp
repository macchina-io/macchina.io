//
// MQTTClientStub.cpp
//
// Library: IoT/MQTT
// Package: Generated
// Module:  MQTTClientStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/MQTT/MQTTClientStub.h"
#include "IoT/MQTT/MQTTClientEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace MQTT {


MQTTClientStub::MQTTClientStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::MQTT::MQTTClient> pServiceObject):
	IoT::MQTT::MQTTClientRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->connectionClosed += Poco::delegate(this, &MQTTClientStub::event__connectionClosed);
	_pServiceObject->connectionEstablished += Poco::delegate(this, &MQTTClientStub::event__connectionEstablished);
	_pServiceObject->connectionLost += Poco::delegate(this, &MQTTClientStub::event__connectionLost);
	_pServiceObject->messageArrived += Poco::delegate(this, &MQTTClientStub::event__messageArrived);
	_pServiceObject->messageDelivered += Poco::delegate(this, &MQTTClientStub::event__messageDelivered);
}


MQTTClientStub::~MQTTClientStub()
{
	try
	{
		_pServiceObject->connectionClosed -= Poco::delegate(this, &MQTTClientStub::event__connectionClosed);
		_pServiceObject->connectionEstablished -= Poco::delegate(this, &MQTTClientStub::event__connectionEstablished);
		_pServiceObject->connectionLost -= Poco::delegate(this, &MQTTClientStub::event__connectionLost);
		_pServiceObject->messageArrived -= Poco::delegate(this, &MQTTClientStub::event__messageArrived);
		_pServiceObject->messageDelivered -= Poco::delegate(this, &MQTTClientStub::event__messageDelivered);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string MQTTClientStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void MQTTClientStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new MQTTClientEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool MQTTClientStub::remoting__hasEvents() const
{
	return true;
}


void MQTTClientStub::event__connectionClosed()
{
	connectionClosed(this);
}


void MQTTClientStub::event__connectionEstablished(const IoT::MQTT::ConnectionEstablishedEvent& data)
{
	connectionEstablished(this, data);
}


void MQTTClientStub::event__connectionLost(const IoT::MQTT::ConnectionLostEvent& data)
{
	connectionLost(this, data);
}


void MQTTClientStub::event__messageArrived(const IoT::MQTT::MessageArrivedEvent& data)
{
	messageArrived(this, data);
}


void MQTTClientStub::event__messageDelivered(const IoT::MQTT::MessageDeliveredEvent& data)
{
	messageDelivered(this, data);
}


} // namespace MQTT
} // namespace IoT

