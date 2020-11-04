//
// ConsoleRequestHandler.h
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef Console_ConsoleRequestHandler_INCLUDED
#define Console_ConsoleRequestHandler_INCLUDED


#include "Poco/EventChannel.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Message.h"
#include "Poco/NotificationQueue.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Web {
namespace Console {


class ConsoleRequestHandler: public Poco::Net::HTTPRequestHandler
	/// This class handles an incoming WebSocket upgrade request, 
	/// and streams log messages to the client.
{
public:
	ConsoleRequestHandler(Poco::AutoPtr<Poco::EventChannel> pChannel, Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the ConsoleRequestHandler.
		
	~ConsoleRequestHandler();
		/// Destroys the ConsoleRequestHandler.
		
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		/// Handles an incoming WebSocket upgrade request and starts streaming log messages
		/// until the client closes the WebSocket.

	static void stopAll();
		/// Stops all request handlers.

protected:
	void forwardMessages(Poco::Net::WebSocket& webSocket);
	void onMessageLogged(const Poco::Message& message);
	void onStopped();
	
	enum
	{
		MAX_QUEUE_SIZE = 10000
	};

private:
	Poco::AutoPtr<Poco::EventChannel> _pChannel;
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::NotificationQueue _queue;
	static Poco::BasicEvent<void> _stopped;
};


} } } // namespace IoT::Web::Console


#endif // Console_ConsoleRequestHandler_INCLUDED
