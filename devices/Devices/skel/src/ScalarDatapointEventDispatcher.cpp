//
// ScalarDatapointEventDispatcher.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  ScalarDatapointEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/ScalarDatapointEventDispatcher.h"
#include "IoT/Devices/DeviceStatusChangeDeserializer.h"
#include "IoT/Devices/DeviceStatusChangeSerializer.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"


namespace IoT {
namespace Devices {


ScalarDatapointEventDispatcher::ScalarDatapointEventDispatcher(IScalarDatapoint* pInterface, const Poco::RemotingNG::Identifiable::ObjectId& objectId, const std::string& protocol):
	Poco::RemotingNG::EventDispatcher(protocol),
	_objectId(objectId),
	_pInterface(pInterface)
{
	_pInterface->validated += Poco::delegate(this, &ScalarDatapointEventDispatcher::event__validated);
	_pInterface->valueChanged += Poco::delegate(this, &ScalarDatapointEventDispatcher::event__valueChanged);
	_pInterface->valueUpdated += Poco::delegate(this, &ScalarDatapointEventDispatcher::event__valueUpdated);
	_pInterface->invalidated += Poco::delegate(this, &ScalarDatapointEventDispatcher::event__invalidated);
	_pInterface->statusChanged += Poco::delegate(this, &ScalarDatapointEventDispatcher::event__statusChanged);
}


ScalarDatapointEventDispatcher::~ScalarDatapointEventDispatcher()
{
	try
	{
		_pInterface->validated -= Poco::delegate(this, &ScalarDatapointEventDispatcher::event__validated);
		_pInterface->valueChanged -= Poco::delegate(this, &ScalarDatapointEventDispatcher::event__valueChanged);
		_pInterface->valueUpdated -= Poco::delegate(this, &ScalarDatapointEventDispatcher::event__valueUpdated);
		_pInterface->invalidated -= Poco::delegate(this, &ScalarDatapointEventDispatcher::event__invalidated);
		_pInterface->statusChanged -= Poco::delegate(this, &ScalarDatapointEventDispatcher::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void ScalarDatapointEventDispatcher::event__invalidated(const void* pSender)
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
					event__invalidatedImpl(it->first);
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


void ScalarDatapointEventDispatcher::event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data)
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
					event__statusChangedImpl(it->first, data);
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


void ScalarDatapointEventDispatcher::event__validated(const void* pSender, const double& data)
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
					event__validatedImpl(it->first, data);
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


void ScalarDatapointEventDispatcher::event__valueChanged(const void* pSender, const double& data)
{
	static const std::string REMOTING__EVENT_NAME("valueChanged");
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
						event__valueChangedImpl(it->first, data);
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


void ScalarDatapointEventDispatcher::event__valueUpdated(const void* pSender, const double& data)
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
					event__valueUpdatedImpl(it->first, data);
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


void ScalarDatapointEventDispatcher::event__invalidatedImpl(const std::string& subscriberURI)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"invalidated"s,"subscriberURI"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ScalarDatapointEventDispatcher::event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"statusChanged"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Devices::DeviceStatusChange>::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ScalarDatapointEventDispatcher::event__validatedImpl(const std::string& subscriberURI, const double& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"validated"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<double>::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ScalarDatapointEventDispatcher::event__valueChangedImpl(const std::string& subscriberURI, const double& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"valueChanged"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<double>::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ScalarDatapointEventDispatcher::event__valueUpdatedImpl(const std::string& subscriberURI, const double& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"valueUpdated"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<double>::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


const std::string ScalarDatapointEventDispatcher::DEFAULT_NS("");
} // namespace Devices
} // namespace IoT

