//
// XBeeNodeEventDispatcher.cpp
//
// Library: IoT/XBee
// Package: Generated
// Module:  XBeeNodeEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/XBee/XBeeNodeEventDispatcher.h"
#include "IoT/XBee/APIFrameDeserializer.h"
#include "IoT/XBee/APIFrameSerializer.h"
#include "IoT/XBee/ATCommandResponseDeserializer.h"
#include "IoT/XBee/ATCommandResponseSerializer.h"
#include "IoT/XBee/ExplicitAddressingZigBeeReceivePacketDeserializer.h"
#include "IoT/XBee/ExplicitAddressingZigBeeReceivePacketSerializer.h"
#include "IoT/XBee/IOSampleDeserializer.h"
#include "IoT/XBee/IOSampleSerializer.h"
#include "IoT/XBee/ModemStatusDeserializer.h"
#include "IoT/XBee/ModemStatusSerializer.h"
#include "IoT/XBee/ReceivePacketDeserializer.h"
#include "IoT/XBee/ReceivePacketSerializer.h"
#include "IoT/XBee/RemoteATCommandResponseDeserializer.h"
#include "IoT/XBee/RemoteATCommandResponseSerializer.h"
#include "IoT/XBee/SensorReadDeserializer.h"
#include "IoT/XBee/SensorReadSerializer.h"
#include "IoT/XBee/TransmitStatusDeserializer.h"
#include "IoT/XBee/TransmitStatusSerializer.h"
#include "IoT/XBee/ZigBeeReceivePacketDeserializer.h"
#include "IoT/XBee/ZigBeeReceivePacketSerializer.h"
#include "IoT/XBee/ZigBeeTransmitStatusDeserializer.h"
#include "IoT/XBee/ZigBeeTransmitStatusSerializer.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"


namespace IoT {
namespace XBee {


XBeeNodeEventDispatcher::XBeeNodeEventDispatcher(XBeeNodeRemoteObject* pRemoteObject, const std::string& protocol):
	Poco::RemotingNG::EventDispatcher(protocol),
	_pRemoteObject(pRemoteObject)
{
	_pRemoteObject->commandResponseReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__commandResponseReceived);
	_pRemoteObject->explicitAddressingZigBeePacketReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__explicitAddressingZigBeePacketReceived);
	_pRemoteObject->frameReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__frameReceived);
	_pRemoteObject->ioDataReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__ioDataReceived);
	_pRemoteObject->ioSampleReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__ioSampleReceived);
	_pRemoteObject->modemStatusReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__modemStatusReceived);
	_pRemoteObject->packetReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__packetReceived);
	_pRemoteObject->remoteCommandResponseReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__remoteCommandResponseReceived);
	_pRemoteObject->sensorReadReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__sensorReadReceived);
	_pRemoteObject->transmitStatusReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__transmitStatusReceived);
	_pRemoteObject->zigBeePacketReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__zigBeePacketReceived);
	_pRemoteObject->zigBeeTransmitStatusReceived += Poco::delegate(this, &XBeeNodeEventDispatcher::event__zigBeeTransmitStatusReceived);
}


XBeeNodeEventDispatcher::~XBeeNodeEventDispatcher()
{
	try
	{
		_pRemoteObject->commandResponseReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__commandResponseReceived);
		_pRemoteObject->explicitAddressingZigBeePacketReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__explicitAddressingZigBeePacketReceived);
		_pRemoteObject->frameReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__frameReceived);
		_pRemoteObject->ioDataReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__ioDataReceived);
		_pRemoteObject->ioSampleReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__ioSampleReceived);
		_pRemoteObject->modemStatusReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__modemStatusReceived);
		_pRemoteObject->packetReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__packetReceived);
		_pRemoteObject->remoteCommandResponseReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__remoteCommandResponseReceived);
		_pRemoteObject->sensorReadReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__sensorReadReceived);
		_pRemoteObject->transmitStatusReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__transmitStatusReceived);
		_pRemoteObject->zigBeePacketReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__zigBeePacketReceived);
		_pRemoteObject->zigBeeTransmitStatusReceived -= Poco::delegate(this, &XBeeNodeEventDispatcher::event__zigBeeTransmitStatusReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void XBeeNodeEventDispatcher::event__commandResponseReceived(const void* pSender, const IoT::XBee::ATCommandResponse& data)
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
					event__commandResponseReceivedImpl(it->first, data);
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


void XBeeNodeEventDispatcher::event__explicitAddressingZigBeePacketReceived(const void* pSender, const IoT::XBee::ExplicitAddressingZigBeeReceivePacket& data)
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
					event__explicitAddressingZigBeePacketReceivedImpl(it->first, data);
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


void XBeeNodeEventDispatcher::event__frameReceived(const void* pSender, const IoT::XBee::APIFrame& data)
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
					event__frameReceivedImpl(it->first, data);
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


void XBeeNodeEventDispatcher::event__ioDataReceived(const void* pSender, const IoT::XBee::ReceivePacket& data)
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
					event__ioDataReceivedImpl(it->first, data);
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


void XBeeNodeEventDispatcher::event__ioSampleReceived(const void* pSender, const IoT::XBee::IOSample& data)
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
					event__ioSampleReceivedImpl(it->first, data);
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


void XBeeNodeEventDispatcher::event__modemStatusReceived(const void* pSender, const IoT::XBee::ModemStatus& data)
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
					event__modemStatusReceivedImpl(it->first, data);
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


void XBeeNodeEventDispatcher::event__packetReceived(const void* pSender, const IoT::XBee::ReceivePacket& data)
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


void XBeeNodeEventDispatcher::event__remoteCommandResponseReceived(const void* pSender, const IoT::XBee::RemoteATCommandResponse& data)
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
					event__remoteCommandResponseReceivedImpl(it->first, data);
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


void XBeeNodeEventDispatcher::event__sensorReadReceived(const void* pSender, const IoT::XBee::SensorRead& data)
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
					event__sensorReadReceivedImpl(it->first, data);
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


void XBeeNodeEventDispatcher::event__transmitStatusReceived(const void* pSender, const IoT::XBee::TransmitStatus& data)
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
					event__transmitStatusReceivedImpl(it->first, data);
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


void XBeeNodeEventDispatcher::event__zigBeePacketReceived(const void* pSender, const IoT::XBee::ZigBeeReceivePacket& data)
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
					event__zigBeePacketReceivedImpl(it->first, data);
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


void XBeeNodeEventDispatcher::event__zigBeeTransmitStatusReceived(const void* pSender, const IoT::XBee::ZigBeeTransmitStatus& data)
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
					event__zigBeeTransmitStatusReceivedImpl(it->first, data);
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


void XBeeNodeEventDispatcher::event__commandResponseReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ATCommandResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"commandResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::ATCommandResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void XBeeNodeEventDispatcher::event__explicitAddressingZigBeePacketReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ExplicitAddressingZigBeeReceivePacket& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"explicitAddressingZigBeePacketReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::ExplicitAddressingZigBeeReceivePacket >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void XBeeNodeEventDispatcher::event__frameReceivedImpl(const std::string& subscriberURI, const IoT::XBee::APIFrame& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"frameReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::APIFrame >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void XBeeNodeEventDispatcher::event__ioDataReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ReceivePacket& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"ioDataReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::ReceivePacket >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void XBeeNodeEventDispatcher::event__ioSampleReceivedImpl(const std::string& subscriberURI, const IoT::XBee::IOSample& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"ioSampleReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::IOSample >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void XBeeNodeEventDispatcher::event__modemStatusReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ModemStatus& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"modemStatusReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::ModemStatus >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void XBeeNodeEventDispatcher::event__packetReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ReceivePacket& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"packetReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::ReceivePacket >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void XBeeNodeEventDispatcher::event__remoteCommandResponseReceivedImpl(const std::string& subscriberURI, const IoT::XBee::RemoteATCommandResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"remoteCommandResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::RemoteATCommandResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void XBeeNodeEventDispatcher::event__sensorReadReceivedImpl(const std::string& subscriberURI, const IoT::XBee::SensorRead& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"sensorReadReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::SensorRead >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void XBeeNodeEventDispatcher::event__transmitStatusReceivedImpl(const std::string& subscriberURI, const IoT::XBee::TransmitStatus& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"transmitStatusReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::TransmitStatus >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void XBeeNodeEventDispatcher::event__zigBeePacketReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ZigBeeReceivePacket& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"zigBeePacketReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::ZigBeeReceivePacket >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void XBeeNodeEventDispatcher::event__zigBeeTransmitStatusReceivedImpl(const std::string& subscriberURI, const IoT::XBee::ZigBeeTransmitStatus& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"zigBeeTransmitStatusReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::XBee::ZigBeeTransmitStatus >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


const std::string XBeeNodeEventDispatcher::DEFAULT_NS("");
} // namespace XBee
} // namespace IoT

