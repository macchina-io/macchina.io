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
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
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
#include "IoT/Modbus/ReadDiscreteInputsResponseDeserializer.h"
#include "IoT/Modbus/ReadDiscreteInputsResponseSerializer.h"
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
	_pRemoteObject->badFrameReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__badFrameReceived);
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
	_pRemoteObject->timeout += Poco::delegate(this, &ModbusMasterEventDispatcher::event__timeout);
	_pRemoteObject->writeMultipleCoilsResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeMultipleCoilsResponseReceived);
	_pRemoteObject->writeMultipleRegistersResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeMultipleRegistersResponseReceived);
	_pRemoteObject->writeSingleCoilResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeSingleCoilResponseReceived);
	_pRemoteObject->writeSingleRegisterResponseReceived += Poco::delegate(this, &ModbusMasterEventDispatcher::event__writeSingleRegisterResponseReceived);
}


ModbusMasterEventDispatcher::~ModbusMasterEventDispatcher()
{
	try
	{
		_pRemoteObject->badFrameReceived -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__badFrameReceived);
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
		_pRemoteObject->timeout -= Poco::delegate(this, &ModbusMasterEventDispatcher::event__timeout);
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


void ModbusMasterEventDispatcher::event__badFrameReceived(const void* pSender)
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
					event__badFrameReceivedImpl(it->first);
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


void ModbusMasterEventDispatcher::event__exceptionReceived(const void* pSender, const IoT::Modbus::ModbusExceptionMessage& data)
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


void ModbusMasterEventDispatcher::event__maskWriteRegisterResponseReceived(const void* pSender, const IoT::Modbus::MaskWriteRegisterResponse& data)
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


void ModbusMasterEventDispatcher::event__readCoilsResponseReceived(const void* pSender, const IoT::Modbus::ReadCoilsResponse& data)
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


void ModbusMasterEventDispatcher::event__readDiscreteInputsResponseReceived(const void* pSender, const IoT::Modbus::ReadDiscreteInputsResponse& data)
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


void ModbusMasterEventDispatcher::event__readExceptionStatusResponseReceived(const void* pSender, const IoT::Modbus::ReadExceptionStatusResponse& data)
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


void ModbusMasterEventDispatcher::event__readFIFOQueueResponseReceived(const void* pSender, const IoT::Modbus::ReadFIFOQueueResponse& data)
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


void ModbusMasterEventDispatcher::event__readHoldingRegistersResponseReceived(const void* pSender, const IoT::Modbus::ReadHoldingRegistersResponse& data)
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


void ModbusMasterEventDispatcher::event__readInputRegistersResponseReceived(const void* pSender, const IoT::Modbus::ReadInputRegistersResponse& data)
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


void ModbusMasterEventDispatcher::event__readWriteMultipleRegistersResponseReceived(const void* pSender, const IoT::Modbus::ReadWriteMultipleRegistersResponse& data)
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


void ModbusMasterEventDispatcher::event__timeout(const void* pSender, const Poco::UInt16& data)
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
					event__timeoutImpl(it->first, data);
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


void ModbusMasterEventDispatcher::event__writeMultipleCoilsResponseReceived(const void* pSender, const IoT::Modbus::WriteMultipleCoilsResponse& data)
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


void ModbusMasterEventDispatcher::event__writeMultipleRegistersResponseReceived(const void* pSender, const IoT::Modbus::WriteMultipleRegistersResponse& data)
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


void ModbusMasterEventDispatcher::event__writeSingleCoilResponseReceived(const void* pSender, const IoT::Modbus::WriteSingleCoilResponse& data)
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


void ModbusMasterEventDispatcher::event__writeSingleRegisterResponseReceived(const void* pSender, const IoT::Modbus::WriteSingleRegisterResponse& data)
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


void ModbusMasterEventDispatcher::event__badFrameReceivedImpl(const std::string& subscriberURI)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"badFrameReceived"s,"subscriberURI"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__exceptionReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ModbusExceptionMessage& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"exceptionReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ModbusExceptionMessage >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__maskWriteRegisterResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::MaskWriteRegisterResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"maskWriteRegisterResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::MaskWriteRegisterResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__readCoilsResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadCoilsResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"readCoilsResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadCoilsResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__readDiscreteInputsResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadDiscreteInputsResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"readDiscreteInputsResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadDiscreteInputsResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__readExceptionStatusResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadExceptionStatusResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"readExceptionStatusResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadExceptionStatusResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__readFIFOQueueResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadFIFOQueueResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"readFIFOQueueResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadFIFOQueueResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__readHoldingRegistersResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadHoldingRegistersResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"readHoldingRegistersResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadHoldingRegistersResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__readInputRegistersResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadInputRegistersResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"readInputRegistersResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadInputRegistersResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__readWriteMultipleRegistersResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadWriteMultipleRegistersResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"readWriteMultipleRegistersResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::ReadWriteMultipleRegistersResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__responseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::GenericMessage& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"responseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::GenericMessage >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__timeoutImpl(const std::string& subscriberURI, const Poco::UInt16& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"timeout"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__writeMultipleCoilsResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::WriteMultipleCoilsResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"writeMultipleCoilsResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::WriteMultipleCoilsResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__writeMultipleRegistersResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::WriteMultipleRegistersResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"writeMultipleRegistersResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::WriteMultipleRegistersResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__writeSingleCoilResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::WriteSingleCoilResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"writeSingleCoilResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::WriteSingleCoilResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void ModbusMasterEventDispatcher::event__writeSingleRegisterResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::WriteSingleRegisterResponse& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"writeSingleRegisterResponseReceived"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::Modbus::WriteSingleRegisterResponse >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


const std::string ModbusMasterEventDispatcher::DEFAULT_NS("");
} // namespace Modbus
} // namespace IoT

