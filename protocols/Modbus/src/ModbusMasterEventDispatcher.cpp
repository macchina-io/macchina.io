//
// ModbusMasterEventDispatcher.cpp
//
// Library: IoT/Modbus
// Package: Generated
// Module:  ModbusMasterEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Modbus/ModbusMasterEventDispatcher.h"
#include "IoT/Modbus/GenericMessageDeserializer.h"
#include "IoT/Modbus/GenericMessageSerializer.h"
#include "IoT/Modbus/MaskWriteRegisterResponseDeserializer.h"
#include "IoT/Modbus/MaskWriteRegisterResponseSerializer.h"
#include "IoT/Modbus/ModbusExceptionMessageDeserializer.h"
#include "IoT/Modbus/ModbusExceptionMessageSerializer.h"
#include "IoT/Modbus/ReadCoilsResponseDeserializer.h"
#include "IoT/Modbus/ReadCoilsResponseSerializer.h"
#include "IoT/Modbus/ReadDiscreteInputsRequestDeserializer.h"
#include "IoT/Modbus/ReadDiscreteInputsRequestSerializer.h"
#include "IoT/Modbus/ReadExceptionStatusResponseDeserializer.h"
#include "IoT/Modbus/ReadExceptionStatusResponseSerializer.h"
#include "IoT/Modbus/ReadFIFOQueueResponseDeserializer.h"
#include "IoT/Modbus/ReadFIFOQueueResponseSerializer.h"
#include "IoT/Modbus/ReadHoldingRegistersResponseDeserializer.h"
#include "IoT/Modbus/ReadHoldingRegistersResponseSerializer.h"
#include "IoT/Modbus/ReadInputRegistersResponseDeserializer.h"
#include "IoT/Modbus/ReadInputRegistersResponseSerializer.h"
#include "IoT/Modbus/ReadWriteMultipleRegistersResponseDeserializer.h"
#include "IoT/Modbus/ReadWriteMultipleRegistersResponseSerializer.h"
#include "IoT/Modbus/WriteMultipleCoilsResponseDeserializer.h"
#include "IoT/Modbus/WriteMultipleCoilsResponseSerializer.h"
#include "IoT/Modbus/WriteMultipleRegistersResponseDeserializer.h"
#include "IoT/Modbus/WriteMultipleRegistersResponseSerializer.h"
#include "IoT/Modbus/WriteSingleCoilResponseDeserializer.h"
#include "IoT/Modbus/WriteSingleCoilResponseSerializer.h"
#include "IoT/Modbus/WriteSingleRegisterResponseDeserializer.h"
#include "IoT/Modbus/WriteSingleRegisterResponseSerializer.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"


namespace IoT {
namespace Modbus {


ModbusMasterEventDispatcher::ModbusMasterEventDispatcher(ModbusMasterRemoteObject* pRemoteObject, const std::string& protocol):
	Poco::RemotingNG::EventDispatcher(protocol),
	_pRemoteObject(pRemoteObject)
{
	_pRemoteObject->exceptionReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__exceptionReceived);
	_pRemoteObject->maskWriteRegisterResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__maskWriteRegisterResponseReceived);
	_pRemoteObject->readCoilsResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__readCoilsResponseReceived);
	_pRemoteObject->readDiscreteInputsResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__readDiscreteInputsResponseReceived);
	_pRemoteObject->readExceptionStatusResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__readExceptionStatusResponseReceived);
	_pRemoteObject->readFIFOQueueResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__readFIFOQueueResponseReceived);
	_pRemoteObject->readHoldingRegistersResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__readHoldingRegistersResponseReceived);
	_pRemoteObject->readInputRegistersResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__readInputRegistersResponseReceived);
	_pRemoteObject->readWriteMultipleRegistersResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__readWriteMultipleRegistersResponseReceived);
	_pRemoteObject->responseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__responseReceived);
	_pRemoteObject->writeMultipleCoilsResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeMultipleCoilsResponseReceived);
	_pRemoteObject->writeMultipleRegistersResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeMultipleRegistersResponseReceived);
	_pRemoteObject->writeSingleCoilResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeSingleCoilResponseReceived);
	_pRemoteObject->writeSingleRegisterResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeSingleRegisterResponseReceived);
}


ModbusMasterEventDispatcher::~ModbusMasterEventDispatcher()
{
	try
	{
		_pRemoteObject->exceptionReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__exceptionReceived);
		_pRemoteObject->maskWriteRegisterResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__maskWriteRegisterResponseReceived);
		_pRemoteObject->readCoilsResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__readCoilsResponseReceived);
		_pRemoteObject->readDiscreteInputsResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__readDiscreteInputsResponseReceived);
		_pRemoteObject->readExceptionStatusResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__readExceptionStatusResponseReceived);
		_pRemoteObject->readFIFOQueueResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__readFIFOQueueResponseReceived);
		_pRemoteObject->readHoldingRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__readHoldingRegistersResponseReceived);
		_pRemoteObject->readInputRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__readInputRegistersResponseReceived);
		_pRemoteObject->readWriteMultipleRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__readWriteMultipleRegistersResponseReceived);
		_pRemoteObject->responseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__responseReceived);
		_pRemoteObject->writeMultipleCoilsResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeMultipleCoilsResponseReceived);
		_pRemoteObject->writeMultipleRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeMultipleRegistersResponseReceived);
		_pRemoteObject->writeSingleCoilResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeSingleCoilResponseReceived);
		_pRemoteObject->writeSingleRegisterResponseReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeSingleRegisterResponseReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void ModbusMasterEventDispatcher::event__exceptionReceived(const void* pSender, const IoT::Modbus::ModbusExceptionMessage& data)
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
					event__exceptionReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__maskWriteRegisterResponseReceived(const void* pSender, IoT::Modbus::MaskWriteRegisterResponse& data)
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
					event__maskWriteRegisterResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__readCoilsResponseReceived(const void* pSender, IoT::Modbus::ReadCoilsResponse& data)
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
					event__readCoilsResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__readDiscreteInputsResponseReceived(const void* pSender, IoT::Modbus::ReadDiscreteInputsRequest& data)
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
					event__readDiscreteInputsResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__readExceptionStatusResponseReceived(const void* pSender, IoT::Modbus::ReadExceptionStatusResponse& data)
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
					event__readExceptionStatusResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__readFIFOQueueResponseReceived(const void* pSender, IoT::Modbus::ReadFIFOQueueResponse& data)
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
					event__readFIFOQueueResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__readHoldingRegistersResponseReceived(const void* pSender, IoT::Modbus::ReadHoldingRegistersResponse& data)
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
					event__readHoldingRegistersResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__readInputRegistersResponseReceived(const void* pSender, IoT::Modbus::ReadInputRegistersResponse& data)
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
					event__readInputRegistersResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__readWriteMultipleRegistersResponseReceived(const void* pSender, IoT::Modbus::ReadWriteMultipleRegistersResponse& data)
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
					event__readWriteMultipleRegistersResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__responseReceived(const void* pSender, const IoT::Modbus::GenericMessage& data)
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
					event__responseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__writeMultipleCoilsResponseReceived(const void* pSender, IoT::Modbus::WriteMultipleCoilsResponse& data)
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
					event__writeMultipleCoilsResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__writeMultipleRegistersResponseReceived(const void* pSender, IoT::Modbus::WriteMultipleRegistersResponse& data)
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
					event__writeMultipleRegistersResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__writeSingleCoilResponseReceived(const void* pSender, IoT::Modbus::WriteSingleCoilResponse& data)
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
					event__writeSingleCoilResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__writeSingleRegisterResponseReceived(const void* pSender, IoT::Modbus::WriteSingleRegisterResponse& data)
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
					event__writeSingleRegisterResponseReceivedImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__exceptionReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ModbusExceptionMessage& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"exceptionReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ModbusExceptionMessage >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__maskWriteRegisterResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::MaskWriteRegisterResponse& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"maskWriteRegisterResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::MaskWriteRegisterResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("maskWriteRegisterResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::MaskWriteRegisterResponse >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


void ModbusMasterEventDispatcher::event__readCoilsResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::ReadCoilsResponse& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"readCoilsResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadCoilsResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("readCoilsResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::ReadCoilsResponse >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


void ModbusMasterEventDispatcher::event__readDiscreteInputsResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::ReadDiscreteInputsRequest& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"readDiscreteInputsResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadDiscreteInputsRequest >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("readDiscreteInputsResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::ReadDiscreteInputsRequest >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


void ModbusMasterEventDispatcher::event__readExceptionStatusResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::ReadExceptionStatusResponse& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"readExceptionStatusResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadExceptionStatusResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("readExceptionStatusResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::ReadExceptionStatusResponse >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


void ModbusMasterEventDispatcher::event__readFIFOQueueResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::ReadFIFOQueueResponse& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"readFIFOQueueResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadFIFOQueueResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("readFIFOQueueResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::ReadFIFOQueueResponse >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


void ModbusMasterEventDispatcher::event__readHoldingRegistersResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::ReadHoldingRegistersResponse& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"readHoldingRegistersResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadHoldingRegistersResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("readHoldingRegistersResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::ReadHoldingRegistersResponse >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


void ModbusMasterEventDispatcher::event__readInputRegistersResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::ReadInputRegistersResponse& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"readInputRegistersResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadInputRegistersResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("readInputRegistersResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::ReadInputRegistersResponse >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


void ModbusMasterEventDispatcher::event__readWriteMultipleRegistersResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::ReadWriteMultipleRegistersResponse& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"readWriteMultipleRegistersResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadWriteMultipleRegistersResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("readWriteMultipleRegistersResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::ReadWriteMultipleRegistersResponse >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


void ModbusMasterEventDispatcher::event__responseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::GenericMessage& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"responseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::GenericMessage >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__writeMultipleCoilsResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::WriteMultipleCoilsResponse& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"writeMultipleCoilsResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::WriteMultipleCoilsResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("writeMultipleCoilsResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::WriteMultipleCoilsResponse >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


void ModbusMasterEventDispatcher::event__writeMultipleRegistersResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::WriteMultipleRegistersResponse& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"writeMultipleRegistersResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::WriteMultipleRegistersResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("writeMultipleRegistersResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::WriteMultipleRegistersResponse >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


void ModbusMasterEventDispatcher::event__writeSingleCoilResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::WriteSingleCoilResponse& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"writeSingleCoilResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::WriteSingleCoilResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("writeSingleCoilResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::WriteSingleCoilResponse >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


void ModbusMasterEventDispatcher::event__writeSingleRegisterResponseReceivedImpl(const std::string& subscriberURI, IoT::Modbus::WriteSingleRegisterResponse& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"writeSingleRegisterResponseReceived","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::WriteSingleRegisterResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("writeSingleRegisterResponseReceivedReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	Poco::RemotingNG::TypeDeserializer<IoT::Modbus::WriteSingleRegisterResponse >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_EVENT_REPLY);
	remoting__trans.endRequest();
}


const std::string ModbusMasterEventDispatcher::DEFAULT_NS("");
} // namespace Modbus
} // namespace IoT

