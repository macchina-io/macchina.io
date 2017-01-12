//
// ServerTransport.cpp
//
// $Id: //poco/1.4/RemotingNG/TCP/src/TransportFactory.cpp#1 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  ServerTransport
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/TCP/ServerTransport.h"
#include "Poco/RemotingNG/TCP/Listener.h"
#include "Poco/RemotingNG/TCP/Transport.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/Context.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


ServerTransport::ServerTransport(Listener& listener, const Poco::SharedPtr<ChannelInputStream>& pRequestStream, const Poco::SharedPtr<ChannelOutputStream>& pReplyStream, bool compressed):
	_listener(listener),
	_pRequestStream(pRequestStream),
	_pReplyStream(pReplyStream),
	_pInflater(0),
	_pDeflater(0),
	_logger(Poco::Logger::get("RemotingNG.TCP.ServerTransport"))
{
	if (compressed)
	{
		_pInflater = new Poco::InflatingInputStream(*_pRequestStream);
		if (_pReplyStream)
		{
			_pDeflater = new Poco::DeflatingOutputStream(*_pReplyStream);
		}
	}
}

	
ServerTransport::~ServerTransport()
{
	delete _pInflater;
	delete _pDeflater;
}

	
void ServerTransport::waitReady()
{
	_ready.wait();
}


Deserializer& ServerTransport::beginRequest()
{
	if (_logger.debug()) _logger.debug("Beginning request...");

	return _deserializer;
}


Serializer& ServerTransport::sendReply(SerializerBase::MessageType messageType)
{
	if (_logger.debug()) _logger.debug("Sending reply...");
	
	if (_pDeflater)
		_serializer.setup(*_pDeflater);
	else
		_serializer.setup(*_pReplyStream);
	return _serializer;
}


void ServerTransport::endRequest()
{
	if (_logger.debug()) _logger.debug("Request done.");

	if (_pDeflater)
		_pDeflater->close();
	if (_pReplyStream)
		_pReplyStream->close();
}


void ServerTransport::run()
{
	Ptr pThis(this, true);
	_ready.set();

	if (_pInflater)
		_deserializer.setup(*_pInflater);
	else
		_deserializer.setup(*_pRequestStream);
	std::string oid;
	std::string tid;
	_deserializer.deserializeEndPoint(oid, tid);
	std::string path = Transport::PROTOCOL;
	path += '/';
	path += tid;
	path += '/';
	path += oid;

	Poco::RemotingNG::ScopedContext scopedContext;
	scopedContext.context()->setValue("transport", Transport::PROTOCOL);
	scopedContext.context()->setValue("remoteAddress", _pRequestStream->rdbuf()->connection()->remoteAddress());
	scopedContext.context()->setValue("localAddress", _pRequestStream->rdbuf()->connection()->localAddress());
	scopedContext.context()->setValue("id", _pRequestStream->rdbuf()->connection()->id());
	scopedContext.context()->setValue("connection", _pRequestStream->rdbuf()->connection().get());
	scopedContext.context()->setValue("uri", path);
	
	Poco::RemotingNG::ORB& orb = Poco::RemotingNG::ORB::instance();
	if (oid.find('#') != std::string::npos)
	{
		if (_logger.debug()) 
		{
			_logger.debug("Dispatching event to subscriber: " + path);
		}
		Poco::RemotingNG::EventSubscriber::Ptr pEventSubscriber = _listener.findEventSubscriber(path);
		if (pEventSubscriber)
		{
			pEventSubscriber->invoke(*this, 0);
		}
		else
		{
			_logger.error("Unknown event subscriber: " + path);
			RemotingException exc("Unknown event subscriber");
			sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT).serializeFaultMessage("fault", exc);
			endRequest();
		}
	}
	else
	{
		if (_logger.debug())
		{
			_logger.debug("Dispatching request to service object: " + path);
		}
				
		bool serviceFound = orb.invoke(_listener, path, *this);
		if (!serviceFound)
		{
			_logger.error("Unknown service object: " + path);
			RemotingException exc("Unknown service");
			sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT).serializeFaultMessage("fault", exc);
			endRequest();
		}
	}
}


} } } // namespace Poco::RemotingNG::TCP
