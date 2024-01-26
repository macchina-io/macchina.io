//
// WebEventNotifierEventDispatcher.cpp
//
// Library: IoT/WebEvent
// Package: Generated
// Module:  WebEventNotifierEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/WebEvent/WebEventNotifierEventDispatcher.h"
#include "IoT/WebEvent/EventNotificationDeserializer.h"
#include "IoT/WebEvent/EventNotificationSerializer.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"


namespace IoT {
namespace WebEvent {


WebEventNotifierEventDispatcher::WebEventNotifierEventDispatcher(WebEventNotifierRemoteObject* pRemoteObject, const std::string& protocol):
	Poco::RemotingNG::EventDispatcher(protocol),
	_pRemoteObject(pRemoteObject)
{
	_pRemoteObject->event += Poco::delegate(this, &WebEventNotifierEventDispatcher::event__event);
}


WebEventNotifierEventDispatcher::~WebEventNotifierEventDispatcher()
{
	try
	{
		_pRemoteObject->event -= Poco::delegate(this, &WebEventNotifierEventDispatcher::event__event);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void WebEventNotifierEventDispatcher::event__event(const void* pSender, const IoT::WebEvent::EventNotification& data)
{
	static const std::string REMOTING__EVENT_NAME("event");
	if (pSender)
	{
		Poco::Clock now;
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
					if (accept(it->second->filters, REMOTING__EVENT_NAME, data))
					{
						event__eventImpl(it->first, data);
					}
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


void WebEventNotifierEventDispatcher::event__eventImpl(const std::string& subscriberURI, const IoT::WebEvent::EventNotification& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"event"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::WebEvent::EventNotification >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


const std::string WebEventNotifierEventDispatcher::DEFAULT_NS("");
} // namespace WebEvent
} // namespace IoT

