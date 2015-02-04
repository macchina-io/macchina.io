//
// Listener.cpp
//
// $Id: //poco/1.4/RemotingNG/TCP/src/Listener.cpp#5 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  Listener
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/TCP/Listener.h"
#include "Poco/RemotingNG/TCP/Transport.h"
#include "Poco/RemotingNG/TCP/ServerTransport.h"
#include "Poco/RemotingNG/TCP/ServerConnectionFactory.h"
#include "Poco/RemotingNG/TCP/FrameHandler.h"
#include "Poco/RemotingNG/TCP/ChannelStream.h"
#include "Poco/NumberFormatter.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


class EventFrameHandler: public FrameHandler
{
public:
	typedef Poco::AutoPtr<EventFrameHandler> Ptr;

	EventFrameHandler(Listener::Ptr pListener):
		_pListener(pListener)
	{
	}
	
	bool handleFrame(Connection::Ptr pConnection, Frame::Ptr pFrame)
	{
		if (pFrame->type() == Frame::FRAME_TYPE_EVNT && (pFrame->flags() & Frame::FRAME_FLAG_CONT) == 0)
		{
			Poco::SharedPtr<ChannelInputStream> pRequestStream = new ChannelInputStream(pConnection, pFrame->type(), pFrame->channel(), _pListener->getTimeout());
			Poco::SharedPtr<ChannelOutputStream> pReplyStream;
			if ((pFrame->flags() & Frame::FRAME_FLAG_ONEWAY) == 0)
			{
				Poco::UInt16 flags(0);
				if (pFrame->flags() & Frame::FRAME_FLAG_DEFLATE)
					flags |= Frame::FRAME_FLAG_DEFLATE;
				pReplyStream = new ChannelOutputStream(pConnection, Frame::FRAME_TYPE_EVNR, pFrame->channel(), flags);
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


Listener::Listener(ConnectionManager& connectionManager):
	Poco::RemotingNG::EventListener("0.0.0.0:0"),
	_connectionManager(connectionManager),
	_timeout(DEFAULT_TIMEOUT, 0),
	_eventSubscriptionTimeout(DEFAULT_EVENT_SUBSCR_TIMEOUT, 0),
	_secure(false),
	_nextSubscriberId(1)
{
}


Listener::Listener(const std::string& endPoint, ConnectionManager& connectionManager):
	Poco::RemotingNG::EventListener(endPoint),
	_connectionManager(connectionManager),
	_timeout(DEFAULT_TIMEOUT, 0),
	_eventSubscriptionTimeout(DEFAULT_EVENT_SUBSCR_TIMEOUT, 0),
	_secure(false),
	_nextSubscriberId(1)
{
	Poco::Net::SocketAddress addr(endPoint);
	Poco::Net::ServerSocket socket(addr);
	_pTCPServer = new Poco::Net::TCPServer(new ServerConnectionFactory(Ptr(this, true)), socket);
}


Listener::Listener(const std::string& endPoint, Poco::Net::TCPServerParams::Ptr pParams, ConnectionManager& connectionManager):
	Poco::RemotingNG::EventListener(endPoint),
	_connectionManager(connectionManager),
	_timeout(DEFAULT_TIMEOUT, 0),
	_eventSubscriptionTimeout(DEFAULT_EVENT_SUBSCR_TIMEOUT, 0),
	_secure(false),
	_nextSubscriberId(1)
{
	Poco::Net::SocketAddress addr(endPoint);
	Poco::Net::ServerSocket socket(addr);
	_pTCPServer = new Poco::Net::TCPServer(new ServerConnectionFactory(Ptr(this, true)), socket, pParams);
}


Listener::Listener(const std::string& endPoint, const Poco::Net::ServerSocket& socket, Poco::Net::TCPServerParams::Ptr pParams, ConnectionManager& connectionManager):
	Poco::RemotingNG::EventListener(endPoint),
	_connectionManager(connectionManager),
	_timeout(DEFAULT_TIMEOUT, 0),
	_eventSubscriptionTimeout(DEFAULT_EVENT_SUBSCR_TIMEOUT, 0),
	_secure(socket.secure()),
	_nextSubscriberId(1)
{
	_pTCPServer = new Poco::Net::TCPServer(new ServerConnectionFactory(Ptr(this, true)), socket, pParams);
}


Listener::~Listener()
{
}


void Listener::setTimeout(Poco::Timespan timeout)
{
	_timeout = timeout;
}


Poco::Timespan Listener::getTimeout() const
{
	return _timeout;
}


void Listener::setEventSubscriptionTimeout(Poco::Timespan timeout)
{
	_eventSubscriptionTimeout = timeout;
}


Poco::Timespan Listener::getEventSubscriptionTimeout() const
{
	return _eventSubscriptionTimeout;
}


ConnectionManager& Listener::connectionManager()
{
	return _connectionManager;
}


void Listener::subscribeToEvents(Poco::RemotingNG::EventSubscriber::Ptr pEventSubscriber)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	Poco::UInt32 nextSubscriberId = _nextSubscriberId++;
	EventSubscription::Ptr pEventSubscription = new EventSubscription(*this, pEventSubscriber->uri(), nextSubscriberId);
	EventSubscriptionsMap::iterator it = _eventSubscriptions.find(pEventSubscriber);
	if (it == _eventSubscriptions.end())
	{
		_eventSubscriptions[pEventSubscriber] = pEventSubscription;
	}
	else
	{
		it->second->cancel();
		it->second = pEventSubscription;
	}
	long interval = static_cast<long>(_eventSubscriptionTimeout.totalMilliseconds()/2);
	_timer.scheduleAtFixedRate(pEventSubscription, interval, interval);
	pEventSubscription->run();
}


void Listener::unsubscribeFromEvents(Poco::RemotingNG::EventSubscriber::Ptr pEventSubscriber)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	EventSubscriptionsMap::iterator it = _eventSubscriptions.find(pEventSubscriber);
	if (it != _eventSubscriptions.end())
	{
		it->second->cancel();
		it->second->run(); // sends unsubscribe message
		_eventSubscriptions.erase(it);
	}
}


Poco::RemotingNG::EventSubscriber::Ptr Listener::findEventSubscriber(const std::string& path) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	for (EventSubscriptionsMap::const_iterator it = _eventSubscriptions.begin(); it != _eventSubscriptions.end(); ++it)
	{
		if (it->second->path() == path)
		{
			return it->first;
		}
	}
	return Poco::RemotingNG::EventSubscriber::Ptr();
}


void Listener::start()
{
	if (_pTCPServer) _pTCPServer->start();
}


void Listener::stop()
{
	if (_pTCPServer) _pTCPServer->stop();
	_pTCPServer = 0;
}


const std::string& Listener::protocol() const
{
	return Transport::PROTOCOL;
}


std::string Listener::createURI(const Poco::RemotingNG::Identifiable::TypeId& typeId, const Poco::RemotingNG::Identifiable::ObjectId& objectId)
{
	std::string uri(_secure ? "remoting.tcps://" : "remoting.tcp://");
	uri += endPoint();
	uri += '/';
	uri += protocol();
	uri += '/';
	uri += typeId;
	uri += '/';
	uri += objectId;
	return uri;
}


bool Listener::handlesURI(const std::string& /*uri*/)
{
	return false;
}


void Listener::registerObject(Poco::RemotingNG::RemoteObject::Ptr /*pRemoteObject*/, Poco::RemotingNG::Skeleton::Ptr /*pSkeleton*/)
{
}


void Listener::unregisterObject(Poco::RemotingNG::RemoteObject::Ptr /*pRemoteObject*/)
{
}


Listener::EventSubscription::EventSubscription(Listener& listener, const std::string& uri, Poco::UInt32 id):
	_listener(listener),
	_uri(uri)
{
	Poco::URI suri(uri);
	Connection::Ptr pConnection = _listener.connectionManager().getConnection(suri);
	suri.setAuthority(pConnection->localAddress().toString());
	suri.setFragment(Poco::NumberFormatter::format(id));
	_suri = suri.toString();
	_path = suri.getPathEtc().substr(1);
}


const std::string& Listener::EventSubscription::path() const
{
	return _path;
}


void Listener::EventSubscription::run()
{
	Connection::Ptr pConnection = _listener.connectionManager().getConnection(_uri);
	if (!pConnection->hasAttribute("EventFrameHandler") && !isCancelled())
	{
		pConnection->pushFrameHandler(new EventFrameHandler(Listener::Ptr(&_listener, true)));
		pConnection->setAttribute("EventFrameHandler", "");
	}
	Frame::Ptr pFrame = new Frame(isCancelled() ? Frame::FRAME_TYPE_EVUN : Frame::FRAME_TYPE_EVSU, 0, Frame::FRAME_FLAG_EOM, Frame::FRAME_HEADER_SIZE + _suri.size());
	_suri.copy(pFrame->payloadBegin(), _suri.size());
	pFrame->setPayloadSize(static_cast<Poco::UInt16>(_suri.size()));
	pConnection->sendFrame(pFrame);
}


} } } // namespace Poco::RemotingNG::TCP
