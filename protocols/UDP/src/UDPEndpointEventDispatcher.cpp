//
// UDPEndpointEventDispatcher.cpp
//
// Library: IoT/UDP
// Package: Generated
// Module:  UDPEndpointEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/UDP/UDPEndpointEventDispatcher.h"
#include "IoT/UDP/PacketDeserializer.h"
#include "IoT/UDP/PacketSerializer.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"


namespace IoT {
namespace UDP {


UDPEndpointEventDispatcher::UDPEndpointEventDispatcher(UDPEndpointRemoteObject* pRemoteObject, const std::string& protocol):
	Poco::RemotingNG::EventDispatcher(protocol),
	_pRemoteObject(pRemoteObject)
{
	_pRemoteObject->packetReceived += Poco::delegate(this, &UDPEndpointEventDispatcher::event__packetReceived);
}


UDPEndpointEventDispatcher::~UDPEndpointEventDispatcher()
{
	try
	{
		_pRemoteObject->packetReceived -= Poco::delegate(this, &UDPEndpointEventDispatcher::event__packetReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void UDPEndpointEventDispatcher::event__packetReceived(const void* pSender, const IoT::UDP::Packet& data)
{
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
					event__packetReceivedImpl(it->first, data);
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


void UDPEndpointEventDispatcher::event__packetReceivedImpl(const std::string& subscriberURI, const IoT::UDP::Packet& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"packetReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::UDP::Packet >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


const std::string UDPEndpointEventDispatcher::DEFAULT_NS("");
} // namespace UDP
} // namespace IoT

