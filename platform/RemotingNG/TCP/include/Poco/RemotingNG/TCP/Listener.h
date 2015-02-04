//
// Listener.h
//
// $Id: //poco/1.4/RemotingNG/TCP/include/Poco/RemotingNG/TCP/Listener.h#5 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  Listener
//
// Definition of the Listener class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_TCP_Listener_INCLUDED
#define RemotingNG_TCP_Listener_INCLUDED


#include "Poco/RemotingNG/TCP/TCP.h"
#include "Poco/RemotingNG/TCP/ConnectionManager.h"
#include "Poco/RemotingNG/TCP/Timer.h"
#include "Poco/RemotingNG/EventListener.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/Mutex.h"
#include <map>


namespace Poco {
namespace RemotingNG {
namespace TCP {


class EventSubscription;


class RemotingNGTCP_API Listener: public Poco::RemotingNG::EventListener
	/// The RemotingNG Listener implementation for the TCP transport.
{
public:
	typedef Poco::AutoPtr<Listener> Ptr;
	
	Poco::BasicEvent<Connection::Ptr> connectionAccepted;
		/// Fired when a new client connection has been accepted.

	Listener(ConnectionManager& connectionManager = ConnectionManager::defaultManager());
		/// Creates a passive Event Listener.
		///
		/// This method is used to set up a passive Event Listener
		/// on the client. No TCPServer will be created.

	Listener(const std::string& endPoint, ConnectionManager& connectionManager = ConnectionManager::defaultManager());
		/// Creates a Listener for the given endpoint,
		/// which must be in <host>:<port> format.
		///
		/// This method will create a Poco::Net::ServerSocket,
		/// bind it to the given endpoint address, and set
		/// up a TCPServer instance for accepting incoming
		/// connections.

	Listener(const std::string& endPoint, Poco::Net::TCPServerParams::Ptr pParams, ConnectionManager& connectionManager = ConnectionManager::defaultManager());
		/// Creates a Listener for the given endpoint,
		/// which must be in <host>:<port> format.
		///
		/// This method will create a Poco::Net::ServerSocket,
		/// bind it to the given endpoint address, and set
		/// up a TCPServer instance (using the given params)
		/// for accepting incoming connections.

	Listener(const std::string& endPoint, const Poco::Net::ServerSocket& socket, Poco::Net::TCPServerParams::Ptr pParams, ConnectionManager& connectionManager = ConnectionManager::defaultManager());
		/// Creates a Listener for the given endpoint,
		/// which must be in <host>:<port> format.
		///
		/// This method will use the given server socket, and set
		/// up a TCPServer instance (using the given params)
		/// for accepting incoming connections.
		///
		/// Note that the given server socket can be a 
		/// Poco::Net::SecureServerSocket in order to set up
		/// a secure connection.

	~Listener();
		/// Destroys the Listener.

	void setTimeout(Poco::Timespan timeout);
		/// Sets the receive timeout for connections.
		
	Poco::Timespan getTimeout() const;
		/// Returns the receive timeout for connections.
		
	void setEventSubscriptionTimeout(Poco::Timespan timeout);
		/// Sets the timeout for event subscriptions.
		
	Poco::Timespan getEventSubscriptionTimeout() const;
		/// Returns the timeout for event subscriptions.
		
	ConnectionManager& connectionManager();
		/// Returns the ConnectionManager used by the Listener.

	// Poco::RemotingNG::EventListener
	void subscribeToEvents(Poco::RemotingNG::EventSubscriber::Ptr pEventSubscriber);
	void unsubscribeFromEvents(Poco::RemotingNG::EventSubscriber::Ptr pEventSubscriber);

	// Poco::RemotingNG::Listener
	void start();
	void stop();
	const std::string& protocol() const;
	std::string createURI(const Poco::RemotingNG::Identifiable::TypeId& typeId, const Poco::RemotingNG::Identifiable::ObjectId& objectId);
	bool handlesURI(const std::string& uri);
	void registerObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject, Poco::RemotingNG::Skeleton::Ptr pSkeleton);
	void unregisterObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject);

	// internal
	Poco::RemotingNG::EventSubscriber::Ptr findEventSubscriber(const std::string& path) const;

private:
	enum
	{
		DEFAULT_TIMEOUT = 30,
		DEFAULT_EVENT_SUBSCR_TIMEOUT = 60
	};
	
	class RemotingNGTCP_API EventSubscription: public TimerTask
	{
	public:
		typedef Poco::AutoPtr<EventSubscription> Ptr;
		
		EventSubscription(Listener& listener, const std::string& uri, Poco::UInt32 id);
		void run();
		const std::string& path() const;
		
	private:
		Listener& _listener;
		Poco::URI _uri;
		std::string _suri;
		std::string _path;
	};

	typedef std::map<Poco::RemotingNG::EventSubscriber::Ptr, EventSubscription::Ptr> EventSubscriptionsMap;
	
	ConnectionManager& _connectionManager;
	Poco::Timespan _timeout;
	Poco::Timespan _eventSubscriptionTimeout;
	bool _secure;
	Poco::SharedPtr<Poco::Net::TCPServer> _pTCPServer;
	EventSubscriptionsMap _eventSubscriptions;
	Poco::UInt32 _nextSubscriberId;
	Timer _timer;
	mutable Poco::FastMutex _mutex;
};


} } } // namespace Poco::RemotingNG::TCP


#endif // RemotingNG_TCP_Listener_INCLUDED
