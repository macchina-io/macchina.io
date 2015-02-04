//
// Transport.cpp
//
// $Id: //poco/1.4/RemotingNG/TCP/src/Transport.cpp#8 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  Transport
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/TCP/Transport.h"
#include "Poco/RemotingNG/TCP/ConnectionManager.h"
#include "Poco/RemotingNG/TCP/ChannelStream.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/NullStream.h"
#include "Poco/InflatingStream.h"
#include "Poco/DeflatingStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Format.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


const std::string Transport::PROTOCOL("tcp");


Transport::Transport(ConnectionManager& connectionManager):
	_connectionManager(connectionManager), 
	_timeout(DEFAULT_TIMEOUT, 0),
	_compression(false),
	_channel(0),
	_logger(Poco::Logger::get("RemotingNG.TCP.Transport"))
{
}


Transport::~Transport()
{
	try
	{
		if (_pConnection && _channel != 0)
		{
			_pConnection->releaseChannel(_channel);
		}
	}
	catch (...)
	{
		poco_unexpected();
	}
}


Poco::Timespan Transport::getTimeout() const
{
	return _timeout;
}

	
void Transport::setTimeout(const Poco::Timespan& timeout)
{
	_timeout = timeout;
}


bool Transport::isCompressionEnabled() const
{
	return _compression;
}


void Transport::enableCompression(bool enable)
{
	_compression = enable;
}


const std::string& Transport::endPoint() const
{
	return _endPoint;
}


void Transport::connect(const std::string& endPoint)
{
	_endPoint = endPoint;
	_endPointURI = endPoint;
}


void Transport::disconnect()
{
	_endPoint.clear();
	_endPointURI.clear();
}


bool Transport::connected() const
{
	return !_endPoint.empty();
}


Poco::RemotingNG::Serializer& Transport::beginMessage(const Poco::RemotingNG::Identifiable::ObjectId& oid, const Poco::RemotingNG::Identifiable::TypeId& tid, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType)
{
	if (_logger.debug()) 
	{
		_logger.debug(Poco::format("Beginning one-way request '%s' to %s.", messageName, _endPoint));
	}
	_pConnection = _connectionManager.getConnection(_endPointURI);
	_channel = _pConnection->allocChannel();
	setupSerializer(oid, tid, messageType, Frame::FRAME_FLAG_ONEWAY);
	return _serializer;
}


void Transport::sendMessage(const Poco::RemotingNG::Identifiable::ObjectId& /*oid*/, const Poco::RemotingNG::Identifiable::TypeId& /*tid*/, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType /*messageType*/)
{
	if (_logger.debug()) _logger.debug("Completing one-way request.");

	if (_pDeflatingStream)
	{
		_pDeflatingStream->close();
		_pDeflatingStream = 0;
	}
	_pRequestStream->close();
	_pRequestStream = 0;
	_pConnection->releaseChannel(_channel);
	_channel = 0;
}


Poco::RemotingNG::Serializer& Transport::beginRequest(const Poco::RemotingNG::Identifiable::ObjectId& oid, const Poco::RemotingNG::Identifiable::TypeId& tid, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType)
{
	if (_logger.debug()) 
	{
		_logger.debug(Poco::format("Beginning request '%s' to %s.", messageName, _endPoint));
	}
	_pConnection = _connectionManager.getConnection(_endPointURI);
	_channel = _pConnection->allocChannel();	
	setupSerializer(oid, tid, messageType, 0);
	return _serializer;
}


Poco::RemotingNG::Deserializer& Transport::sendRequest(const Poco::RemotingNG::Identifiable::ObjectId& /*oid*/, const Poco::RemotingNG::Identifiable::TypeId& /*tid*/, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType)
{
	if (_logger.debug()) _logger.debug("Sending request...");

	// Set up reply stream before closing request to avoid
	// race condition (no reply handler registered) with fast
	// connections.
	
	Poco::UInt32 frameType = 0;
	switch (messageType)
	{
	case Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST:
		frameType = Frame::FRAME_TYPE_REPL;
		break;
	
	case Poco::RemotingNG::SerializerBase::MESSAGE_EVENT:
		frameType = Frame::FRAME_TYPE_EVNR;
		break;
	
	default:
		poco_bugcheck();
	}

	_pReplyStream = new ChannelInputStream(_pConnection, frameType, _channel, _timeout);

	if (_pDeflatingStream)
	{
		_pDeflatingStream->close();
		_pDeflatingStream = 0;
	}
	_pRequestStream->close();
	_pRequestStream = 0;

	if (_compression)
	{
		_pInflatingStream = new Poco::InflatingInputStream(*_pReplyStream);
		_deserializer.setup(*_pInflatingStream);
	}
	else
	{
		_deserializer.setup(*_pReplyStream);
	}
	return _deserializer;
}


void Transport::endRequest()
{
	if (_logger.debug()) _logger.debug("Request done.");

	_serializer.reset();
	_deserializer.reset();
	_pReplyStream = 0;
	_pInflatingStream = 0;
	_pConnection->releaseChannel(_channel);
	_channel = 0;
	_pConnection = 0;
}


void Transport::setupSerializer(const Poco::RemotingNG::Identifiable::ObjectId& oid, const Poco::RemotingNG::Identifiable::TypeId& tid, Poco::RemotingNG::SerializerBase::MessageType messageType, Poco::UInt16 frameFlags)
{
	Poco::UInt32 frameType = 0;
	switch (messageType)
	{
	case Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST:
		frameType = Frame::FRAME_TYPE_REQU;
		break;
	
	case Poco::RemotingNG::SerializerBase::MESSAGE_EVENT:
		frameType = Frame::FRAME_TYPE_EVNT;
		break;
	
	default:
		poco_bugcheck();
	}

	if (_compression) frameFlags |= Frame::FRAME_FLAG_DEFLATE;
	
	_pRequestStream = new ChannelOutputStream(_pConnection, frameType, _channel, frameFlags);
	if (_compression)
	{
		_pDeflatingStream = new Poco::DeflatingOutputStream(*_pRequestStream);
		_serializer.setup(*_pDeflatingStream);
	}
	else
	{
		_serializer.setup(*_pRequestStream);
	}
	if (messageType == Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST)
	{
		_serializer.serializeEndPoint(oid, tid);
	}
	else
	{
		std::string eoid(oid);
		eoid += '#';
		eoid += _endPointURI.getFragment();
		_serializer.serializeEndPoint(eoid, tid);
	}
}


} } } // namespace Poco::RemotingNG::TCP
