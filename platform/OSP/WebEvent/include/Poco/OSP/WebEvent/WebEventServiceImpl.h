//
// WebEventServiceImpl.h
//
// $Id: //poco/1.4/OSP/WebEvent/include/Poco/OSP/WebEvent/WebEventServiceImpl.h#6 $
//
// Library: OSP/WebEvent
// Package: WebEvent
// Module:  WebEventServiceImpl
//
// Definition of the WebEventServiceImpl interface.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_WebEvent_WebEventServiceImpl_INCLUDED
#define OSP_WebEvent_WebEventServiceImpl_INCLUDED


#include "Poco/OSP/WebEvent/WebEventService.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/NotificationQueue.h"
#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/SharedPtr.h"
#include <vector>
#include <set>
#include <map>


namespace Poco {
namespace OSP {
namespace WebEvent {


class OSPWebEvent_API WebEventServiceImpl: public WebEventService
{
public:
	typedef Poco::AutoPtr<WebEventServiceImpl> Ptr;
	
	WebEventServiceImpl(Poco::OSP::BundleContext::Ptr pContext, int maxSockets);
		/// Creates the WebEventServiceImpl.
		
	~WebEventServiceImpl();
		/// Destroys the WebEventServiceImpl.

	// WebEventService
	Poco::BasicEvent<const NotificationEvent>& subjectNotified(const std::string& subject);
	void notify(const std::string& subjectName, const std::string& data);

	// Service
	const std::type_info& type() const;	
	bool isA(const std::type_info& otherType) const;

protected:
	void preflightRequest(Poco::Net::HTTPServerRequest& request);
	void runMain();
	void runWorker();
	void addSubscriber(Poco::SharedPtr<Poco::Net::WebSocket> pWS);
	void removeSubscriber(Poco::SharedPtr<Poco::Net::WebSocket> pWS, bool clientShutdown);
	void subscribe(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::set<std::string>& subjectNames);
	void unsubscribe(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::set<std::string>& subjectNames);
	void send(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::string& message);
	void receive(Poco::SharedPtr<Poco::Net::WebSocket> pWS);
	void shutdown(Poco::SharedPtr<Poco::Net::WebSocket> pWS, Poco::UInt16 statusCode, const std::string& statusMessage, bool passive);
	
	void notifyImpl(const std::string& subjectName, const std::string& data);
	void addSubscriberImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS);
	void removeSubscriberImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS, bool clientShutdown);
	void subscribeImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::set<std::string>& subjectNames);
	void unsubscribeImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::set<std::string>& subjectNames);
	void sendImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::string& message);
	void receiveImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS);
	void shutdownImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS, Poco::UInt16 statusCode, const std::string& statusMessage, bool passive);
	void watchSocketImpl(const Poco::Net::Socket& socket);
	void unwatchSocketImpl(const Poco::Net::Socket& socket);

private:
	static const std::string SUBSCRIBE;
	static const std::string UNSUBSCRIBE;
	static const std::string NOTIFY;
	static const std::string VERSION;
	static const std::string SYSTEM_PING;
	static const std::string SYSTEM_PONG;

	enum
	{
		WEBEVENT_RECEIVE_TIMEOUT = 5,
		WEBEVENT_SEND_TIMEOUT = 10,
		WEBEVENT_SHUTDOWN_TIMEOUT = 2 
	};
	
	struct Subscriber: public Poco::RefCountedObject
	{
		typedef Poco::AutoPtr<Subscriber> Ptr;

		Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket;
		std::set<std::string> subjectNames;
	};
	typedef std::multimap<std::string, Subscriber::Ptr> SubjectMap;
	typedef Poco::BasicEvent<const NotificationEvent> Event;
	typedef Poco::SharedPtr<Event> EventPtr;
	typedef std::multimap<std::string, EventPtr> EventMap;
	typedef std::map<Poco::Net::Socket, Subscriber::Ptr> SocketMap;
	typedef Poco::SharedPtr<Poco::Thread> ThreadPtr;
	typedef std::vector<ThreadPtr> ThreadVec;
	
	Poco::OSP::BundleContext::Ptr _pContext;
	int _maxSockets;
	SubjectMap _subjectMap;
	EventMap _eventMap;
	SocketMap  _socketMap;
	Poco::Net::Socket::SocketList _socketList;
	Poco::NotificationQueue _mainQueue;
	Poco::NotificationQueue _workerQueue;
	Poco::Thread _mainThread;
	ThreadVec _workerThreads;
	Poco::RunnableAdapter<WebEventServiceImpl> _mainRunnable;
	Poco::RunnableAdapter<WebEventServiceImpl> _workerRunnable;
	bool _stopped;

	friend class WebEventRequestHandler;
	friend class AddSubscriberNotification;
	friend class RemoveSubscriberNotification;
	friend class SubscribeNotification;
	friend class UnsubscribeNotification;
	friend class NotifyNotification;
	friend class SendNotification;
	friend class ReceiveNotification;
	friend class ShutdownNotification;
	friend class WatchSocketNotification;
};


} } } // namespace Poco::OSP::WebEvent


#endif // OSP_WebEvent_WebEventServiceImpl_INCLUDED
