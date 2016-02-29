//
// ServerConnection.cpp
//
// $Id: //poco/1.7/RemotingNG/TCP/src/ServerConnection.cpp#1 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  ServerConnection
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/TCP/ServerConnection.h"
#include "Poco/RemotingNG/TCP/ConnectionManager.h"
#include "Poco/RemotingNG/TCP/Connection.h"
#include "Poco/RemotingNG/TCP/FrameHandler.h"
#include "Poco/RemotingNG/TCP/ServerTransport.h"
#include "Poco/RemotingNG/TCP/Transport.h"
#include "Poco/RemotingNG/TCP/ChannelStream.h"
#include "Poco/RemotingNG/EventDispatcher.h"
#include "Poco/RemotingNG/ORB.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


class RequestFrameHandler: public FrameHandler
{
public:
	typedef Poco::AutoPtr<RequestFrameHandler> Ptr;

	RequestFrameHandler(Listener::Ptr pListener):
		_pListener(pListener)
	{
	}
	
	bool handleFrame(Connection::Ptr pConnection, Frame::Ptr pFrame)
	{
		if (pFrame->type() == Frame::FRAME_TYPE_REQU && (pFrame->flags() & Frame::FRAME_FLAG_CONT) == 0)
		{
			Poco::SharedPtr<ChannelInputStream> pRequestStream = new ChannelInputStream(pConnection, pFrame->type(), pFrame->channel(), _pListener->getTimeout());
			Poco::SharedPtr<ChannelOutputStream> pReplyStream;
			if ((pFrame->flags() & Frame::FRAME_FLAG_ONEWAY) == 0)
			{
				Poco::UInt16 flags(0);
				if (pFrame->flags() & Frame::FRAME_FLAG_DEFLATE)
					flags |= Frame::FRAME_FLAG_DEFLATE;
				pReplyStream = new ChannelOutputStream(pConnection, Frame::FRAME_TYPE_REPL, pFrame->channel(), flags);
			}
			ServerTransport::Ptr pServerTransport = new ServerTransport(*_pListener, pRequestStream, pReplyStream, (pFrame->flags() & Frame::FRAME_FLAG_DEFLATE) != 0);
			_pListener->connectionManager().threadPool().start(*pServerTransport);
			Poco::Thread::yield();
			pServerTransport->waitReady();
			pRequestStream->rdbuf()->queue()->handleFrame(pConnection, pFrame);
			return true;
		}
		else return false;
	}
	
private:
	Listener::Ptr _pListener;
};


class EventSubscriptionFrameHandler: public FrameHandler
{
public:
	typedef Poco::AutoPtr<EventSubscriptionFrameHandler> Ptr;

	EventSubscriptionFrameHandler(Listener::Ptr pListener):
		_pListener(pListener)
	{
	}

	bool handleFrame(Connection::Ptr pConnection, Frame::Ptr pFrame)
	{
		if (pFrame->type() == Frame::FRAME_TYPE_EVSU || pFrame->type() == Frame::FRAME_TYPE_EVUN)
		{
			Poco::RemotingNG::ORB& orb = Poco::RemotingNG::ORB::instance();
			std::string suri(pFrame->payloadBegin(), pFrame->getPayloadSize());
			Poco::URI dispURI(suri);
			dispURI.setAuthority(_pListener->endPoint());
			dispURI.setFragment("");
			Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = orb.findEventDispatcher(dispURI.toString(), Transport::PROTOCOL);
			if (pFrame->type() == Frame::FRAME_TYPE_EVSU)
			{
				Poco::Timestamp expire;
				expire += _pListener->getEventSubscriptionTimeout().totalMicroseconds();
				pEventDispatcher->subscribe(suri, suri, expire);
			}
			else
			{
				pEventDispatcher->unsubscribe(suri);
			}
			pConnection->returnFrame(pFrame);
			return true;
		}
		return false;
	}

private:
	Listener::Ptr _pListener;
};


ServerConnection::ServerConnection(Listener::Ptr pListener, const Poco::Net::StreamSocket& socket):
	Poco::Net::TCPServerConnection(socket),
	_pListener(pListener),
	_logger(Poco::Logger::get("RemotingNG.TCP.ServerConnection"))
{
}


ServerConnection::~ServerConnection()
{
}


void ServerConnection::run()
{
	if (_logger.debug()) _logger.debug("ServerConnection started.");
	Connection::Ptr pConnection = new Connection(socket(), Connection::MODE_SERVER);
	EventSubscriptionFrameHandler::Ptr pEventSubFrameHandler = new EventSubscriptionFrameHandler(_pListener);
	RequestFrameHandler::Ptr pRequestFrameHandler = new RequestFrameHandler(_pListener);
	pConnection->pushFrameHandler(pEventSubFrameHandler);
	pConnection->pushFrameHandler(pRequestFrameHandler);
	_pListener->connectionManager().registerConnection(pConnection);
	try
	{
		_pListener->connectionAccepted(pConnection);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("connectionAccepted event handler threw exception: " + exc.displayText());
	}
	catch (...)
	{
		_logger.error("connectionAccepted event handler threw unknown exception");
	}
	try
	{
		pConnection->run();
	}
	catch (Poco::Exception& exc)
	{
		_logger.log(exc);
	}
	_pListener->connectionManager().unregisterConnection(pConnection);
	pConnection->popFrameHandler(pRequestFrameHandler);
	pConnection->popFrameHandler(pEventSubFrameHandler);
	if (_logger.debug()) _logger.debug("ServerConnection done.");
}


} } } // namespace Poco::RemotingNG::TCP
