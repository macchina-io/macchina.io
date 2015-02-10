//
// AccelerometerEventDispatcher.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  AccelerometerEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/AccelerometerEventDispatcher.h"
#include "IoT/Devices/AccelerationDeserializer.h"
#include "IoT/Devices/AccelerationSerializer.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"


namespace IoT {
namespace Devices {


AccelerometerEventDispatcher::AccelerometerEventDispatcher(AccelerometerRemoteObject* pRemoteObject, const std::string& protocol):
	Poco::RemotingNG::EventDispatcher(protocol),
	_pRemoteObject(pRemoteObject)
{
	_pRemoteObject->accelerationUpdate += Poco::delegate(this, &AccelerometerEventDispatcher::event__accelerationUpdate);
}


AccelerometerEventDispatcher::~AccelerometerEventDispatcher()
{
	try
	{
		_pRemoteObject->accelerationUpdate -= Poco::delegate(this, &AccelerometerEventDispatcher::event__accelerationUpdate);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void AccelerometerEventDispatcher::event__accelerationUpdate(const void* pSender, const IoT::Devices::Acceleration& data)
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
					event__accelerationUpdateImpl(it->first, data);
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


void AccelerometerEventDispatcher::event__accelerationUpdateImpl(const std::string& subscriberURI, const IoT::Devices::Acceleration& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"accelerationUpdate","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Devices::Acceleration >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


const std::string AccelerometerEventDispatcher::DEFAULT_NS("");
} // namespace Devices
} // namespace IoT

