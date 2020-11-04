//
// BarcodeReaderEventDispatcher.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  BarcodeReaderEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/BarcodeReaderEventDispatcher.h"
#include "IoT/Devices/BarcodeReadEventDeserializer.h"
#include "IoT/Devices/BarcodeReadEventSerializer.h"
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


BarcodeReaderEventDispatcher::BarcodeReaderEventDispatcher(BarcodeReaderRemoteObject* pRemoteObject, const std::string& protocol):
	Poco::RemotingNG::EventDispatcher(protocol),
	_pRemoteObject(pRemoteObject)
{
	_pRemoteObject->barcodeRead += Poco::delegate(this, &BarcodeReaderEventDispatcher::event__barcodeRead);
	_pRemoteObject->statusChanged += Poco::delegate(this, &BarcodeReaderEventDispatcher::event__statusChanged);
}


BarcodeReaderEventDispatcher::~BarcodeReaderEventDispatcher()
{
	try
	{
		_pRemoteObject->barcodeRead -= Poco::delegate(this, &BarcodeReaderEventDispatcher::event__barcodeRead);
		_pRemoteObject->statusChanged -= Poco::delegate(this, &BarcodeReaderEventDispatcher::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void BarcodeReaderEventDispatcher::event__barcodeRead(const void* pSender, const IoT::Devices::BarcodeReadEvent& data)
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
					event__barcodeReadImpl(it->first, data);
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


void BarcodeReaderEventDispatcher::event__statusChanged(const void* pSender, const IoT::Devices::DeviceStatusChange& data)
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


void BarcodeReaderEventDispatcher::event__barcodeReadImpl(const std::string& subscriberURI, const IoT::Devices::BarcodeReadEvent& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"barcodeRead"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Devices::BarcodeReadEvent >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void BarcodeReaderEventDispatcher::event__statusChangedImpl(const std::string& subscriberURI, const IoT::Devices::DeviceStatusChange& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"statusChanged"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Devices::DeviceStatusChange >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


const std::string BarcodeReaderEventDispatcher::DEFAULT_NS("");
} // namespace Devices
} // namespace IoT

