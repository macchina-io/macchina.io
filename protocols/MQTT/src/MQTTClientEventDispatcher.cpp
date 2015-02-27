//
// MQTTClientEventDispatcher.cpp
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


#include "IoT/MQTT/MQTTClientEventDispatcher.h"
#include "IoT/MQTT/ConnectionLostEventDeserializer.h"
#include "IoT/MQTT/ConnectionLostEventSerializer.h"
#include "IoT/MQTT/MessageArrivedEventDeserializer.h"
#include "IoT/MQTT/MessageArrivedEventSerializer.h"
#include "IoT/MQTT/MessageDeliveredEventDeserializer.h"
#include "IoT/MQTT/MessageDeliveredEventSerializer.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"


namespace IoT {
namespace MQTT {


MQTTClientEventDispatcher::MQTTClientEventDispatcher(MQTTClientRemoteObject* pRemoteObject, const std::string& protocol):
	Poco::RemotingNG::EventDispatcher(protocol),
	_pRemoteObject(pRemoteObject)
{
	_pRemoteObject->connectionLost += Poco::delegate(this, &MQTTClientEventDispatcher::event__connectionLost);
	_pRemoteObject->messageArrived += Poco::delegate(this, &MQTTClientEventDispatcher::event__messageArrived);
	_pRemoteObject->messageDelivered += Poco::delegate(this, &MQTTClientEventDispatcher::event__messageDelivered);
}


MQTTClientEventDispatcher::~MQTTClientEventDispatcher()
{
	try
	{
		_pRemoteObject->connectionLost -= Poco::delegate(this, &MQTTClientEventDispatcher::event__connectionLost);
		_pRemoteObject->messageArrived -= Poco::delegate(this, &MQTTClientEventDispatcher::event__messageArrived);
		_pRemoteObject->messageDelivered -= Poco::delegate(this, &MQTTClientEventDispatcher::event__messageDelivered);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void MQTTClientEventDispatcher::event__connectionLost(const void* pSender, const IoT::MQTT::ConnectionLostEvent& data)
{
	if (pSender)
	{
		Poco::Timestamp now;
		Poco::FastMutex::ScopedLock lock(_mutex);
		SubscriberMap::iterator it = _subscribers.begin();
		while (it != _subscribers.end())
		{
			if (it->second->expireTime != 0 && it->second->expireTime < now)
			{
				SubscriberMap::iterator itDel(it++);
				_subscribers.erase(itDel);
			}
			else
			{
				try
				{
					event__connectionLostImpl(it->first, data);
				}
				catch (Poco::RemotingNG::RemoteException&)
				{
					throw;
				}
				catch (Poco::Exception&)
				{
				}
				++it;
			}
		}
	}
}


void MQTTClientEventDispatcher::event__messageArrived(const void* pSender, const IoT::MQTT::MessageArrivedEvent& data)
{
	if (pSender)
	{
		Poco::Timestamp now;
		Poco::FastMutex::ScopedLock lock(_mutex);
		SubscriberMap::iterator it = _subscribers.begin();
		while (it != _subscribers.end())
		{
			if (it->second->expireTime != 0 && it->second->expireTime < now)
			{
				SubscriberMap::iterator itDel(it++);
				_subscribers.erase(itDel);
			}
			else
			{
				try
				{
					event__messageArrivedImpl(it->first, data);
				}
				catch (Poco::RemotingNG::RemoteException&)
				{
					throw;
				}
				catch (Poco::Exception&)
				{
				}
				++it;
			}
		}
	}
}


void MQTTClientEventDispatcher::event__messageDelivered(const void* pSender, const IoT::MQTT::MessageDeliveredEvent& data)
{
	if (pSender)
	{
		Poco::Timestamp now;
		Poco::FastMutex::ScopedLock lock(_mutex);
		SubscriberMap::iterator it = _subscribers.begin();
		while (it != _subscribers.end())
		{
			if (it->second->expireTime != 0 && it->second->expireTime < now)
			{
				SubscriberMap::iterator itDel(it++);
				_subscribers.erase(itDel);
			}
			else
			{
				try
				{
					event__messageDeliveredImpl(it->first, data);
				}
				catch (Poco::RemotingNG::RemoteException&)
				{
					throw;
				}
				catch (Poco::Exception&)
				{
				}
				++it;
			}
		}
	}
}


void MQTTClientEventDispatcher::event__connectionLostImpl(const std::string& subscriberURI, const IoT::MQTT::ConnectionLostEvent& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"connectionLost","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::MQTT::ConnectionLostEvent >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void MQTTClientEventDispatcher::event__messageArrivedImpl(const std::string& subscriberURI, const IoT::MQTT::MessageArrivedEvent& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"messageArrived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::MQTT::MessageArrivedEvent >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void MQTTClientEventDispatcher::event__messageDeliveredImpl(const std::string& subscriberURI, const IoT::MQTT::MessageDeliveredEvent& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"messageDelivered","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::MQTT::MessageDeliveredEvent >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


const std::string MQTTClientEventDispatcher::DEFAULT_NS("");
} // namespace MQTT
} // namespace IoT

