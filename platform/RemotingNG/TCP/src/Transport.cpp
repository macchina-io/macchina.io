//
// Transport.cpp
//
// $Id: //poco/1.7/RemotingNG/TCP/src/Transport.cpp#3 $
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
#include "Poco/RemotingNG/TCP/Frame.h"
#include "Poco/RemotingNG/TCP/FrameHandler.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/InflatingStream.h"
#include "Poco/DeflatingStream.h"
#include "Poco/MemoryStream.h"
#include "Poco/CountingStream.h"
#include "Poco/BinaryWriter.h"
#include "Poco/BinaryReader.h"
#include "Poco/StreamCopier.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Format.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


class AuthResponseFrameHandler: public FrameHandler
{
public:
	typedef Poco::AutoPtr<AuthResponseFrameHandler> Ptr;

	explicit AuthResponseFrameHandler(Poco::UInt32 channel):
		_channel(channel),
		_authToken(0)
	{
	}
	
	bool handleFrame(Connection::Ptr pConnection, Frame::Ptr pFrame)
	{
		if (pFrame->channel() == _channel && pFrame->type() == Frame::FRAME_TYPE_AUTR)
		{
			Poco::MemoryInputStream istr(pFrame->payloadBegin(), pFrame->getPayloadSize());
			Poco::BinaryReader reader(istr, Poco::BinaryReader::NETWORK_BYTE_ORDER);
			reader >> _authToken;
			_received.set();
			return true;
		}
		else return false;
	}
	
	Poco::UInt64 wait(long timeout)
	{
		_received.wait(timeout);
		return _authToken;
	}
	
private:
	Poco::UInt32 _channel;
	Poco::Event _received;
	Poco::UInt64 _authToken;
};


const std::string Transport::PROTOCOL("tcp");


Transport::Transport(ConnectionManager& connectionManager):
	_connectionManager(connectionManager), 
	_timeout(DEFAULT_TIMEOUT, 0),
	_compression(false),
	_channel(0),
	_authToken(0),
	_authConnectionId(0),
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


void Transport::setCredentials(const Credentials& credentials)
{
	_credentials = credentials;
	// force re-authentication with next request
	_authToken = 0;
	_authConnectionId = 0;
}


const Credentials& Transport::getCredentials() const
{
	return _credentials;
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
	authenticate();
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
	authenticate();
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
	if (_authToken) frameFlags |= Frame::FRAME_FLAG_AUTH;
	
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
	if (_authToken)
	{
		_serializer.serializeToken(_authToken);
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


namespace 
{
	void serializeCredentials(const Credentials& creds, std::ostream& ostr)
	{
		poco_assert (creds.countAttributes() < 256);

		Poco::BinaryWriter writer(ostr, Poco::BinaryWriter::NETWORK_BYTE_ORDER);
		writer << static_cast<Poco::UInt8>(creds.countAttributes());
		std::vector<std::string> keys = creds.enumerateAttributes();
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			writer << *it << creds.getAttribute(*it);
		}
	}
}


void Transport::authenticate()
{
	if (_credentials.countAttributes() > 0 && _authConnectionId != _pConnection->id())
	{
		if (verifyCredentials(_credentials))
		{	
			if (_logger.debug())
			{
				_logger.debug("Authenticating transport...");
			}
			AuthResponseFrameHandler::Ptr pAuthResponseFrameHandler = new AuthResponseFrameHandler(_channel);
			_pConnection->pushFrameHandler(pAuthResponseFrameHandler);
			try
			{
				Frame::Ptr pFrame = new Frame(Frame::FRAME_TYPE_AUTH, _channel, Frame::FRAME_FLAG_EOM, Frame::FRAME_MAX_SIZE);
				Poco::MemoryOutputStream ostr(pFrame->payloadBegin(), pFrame->maxPayloadSize());
				serializeCredentials(_credentials, ostr);
				pFrame->setPayloadSize(static_cast<Poco::UInt16>(ostr.charsWritten()));
				_pConnection->sendFrame(pFrame);
				
				if (_logger.debug())
				{
					_logger.debug("Waiting for authentication response...");
				}
				_authToken = pAuthResponseFrameHandler->wait(static_cast<long>(_timeout.totalMilliseconds()));
				if (_authToken)
				{
					_authConnectionId = _pConnection->id();
					if (_logger.debug())
					{
						_logger.debug("Authentication done.");
					}
				}
				else throw AuthenticationFailedException("The server refused the provided credentials");
			}
			catch (Poco::Exception&)
			{
				_authToken = 0;
				_authConnectionId = 0;
				_pConnection->popFrameHandler(pAuthResponseFrameHandler);
				throw;
			}
			_pConnection->popFrameHandler(pAuthResponseFrameHandler);
		}
		else throw InvalidCredentialsException("Credentials too large");
	}
}


bool Transport::verifyCredentials(const Credentials& creds)
{
	if (creds.countAttributes() < 256)
	{
		Poco::CountingOutputStream ostr;
		serializeCredentials(creds, ostr);
		return ostr.chars() <= Frame::FRAME_MAX_PAYLOAD_SIZE;
	}
	else return false;
}


} } } // namespace Poco::RemotingNG::TCP
