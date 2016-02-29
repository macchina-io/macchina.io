//
// EventDispatcher.cpp
//
// $Id: //poco/1.7/RemotingNG/src/EventDispatcher.cpp#1 $
//
// Library: RemotingNG
// Package: ORB
// Module:  EventDispatcher
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/EventDispatcher.h"
#include "Poco/RemotingNG/TransportFactoryManager.h"
#include "Poco/Exception.h"


namespace Poco {
namespace RemotingNG {


EventDispatcher::EventDispatcher(const std::string& protocol):
	_protocol(protocol)
{
}


EventDispatcher::~EventDispatcher()
{
}


void EventDispatcher::subscribe(const std::string& subscriberURI, const std::string& endpointURI, Poco::Timestamp expireTime)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	SubscriberMap::iterator it = _subscribers.find(subscriberURI);
	if (it == _subscribers.end())
	{
		SubscriberInfo::Ptr pInfo = new SubscriberInfo;
		pInfo->endpoint = endpointURI;
		pInfo->expireTime = expireTime;
		_subscribers[subscriberURI] = pInfo;
	}
	else 
	{
		it->second->expireTime = expireTime;
	}
}


void EventDispatcher::unsubscribe(const std::string& subscriberURI)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	SubscriberMap::iterator it = _subscribers.find(subscriberURI);
	if (it != _subscribers.end())
	{
		_subscribers.erase(it);
	}
	else throw Poco::NotFoundException("event subscriber", subscriberURI);
}


Transport& EventDispatcher::transportForSubscriber(const std::string& subscriberURI)
{
	// Note: the mutex will have already been locked by the caller
	
	static TransportFactoryManager& tfm = TransportFactoryManager::instance();
	
	SubscriberMap::iterator it = _subscribers.find(subscriberURI);
	if (it != _subscribers.end())
	{
		if (!it->second->pTransport)
		{
			it->second->pTransport = tfm.createTransport(_protocol, it->second->endpoint);
		}
		return *it->second->pTransport;
	}
	else throw Poco::NotFoundException("event subscriber", subscriberURI);
}


} } // namespace Poco::RemotingNG
