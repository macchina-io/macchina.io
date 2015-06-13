//
// ConsoleRequestHandler.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "ConsoleRequestHandler.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/NetException.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Notification.h"
#include "Poco/Delegate.h"
#include <sstream>


namespace IoT {
namespace Web {
namespace Console {


class MessageNotification: public Poco::Notification
{
public:
	MessageNotification(const Poco::Message& msg):
		_msg(msg)
	{
	}
	
	~MessageNotification()
	{
	}
	
	const Poco::Message& message() const
	{
		return _msg;
	}
	
private:
	Poco::Message _msg;
};


class StopNotification: public Poco::Notification
{
};


std::string jsonize(const std::string& str)
{
	std::string result("\"");
	std::string::const_iterator it(str.begin());
	std::string::const_iterator end(str.end());
	for (; it != end; ++it)
	{
		switch (*it)
		{
		case '"':
			result += "\\\"";
			break;
		case '\\':
			result += "\\\\";
			break;
		case '\b':
			result += "\\b";
			break;
		case '\f':
			result += "\\f";
			break;
		case '\n':
			result += "\\n";
			break;
		case '\r':
			result += "\\r";
			break;
		case '\t':
			result += "\\t";
			break;
		default:
			result += *it;
			break;
		}
	}
	result += "\"";
	return result;
}


std::string quote(const std::string& str)
{
	std::string quoted("\"");
	quoted += str;
	quoted += "\"";
	return quoted;
}


std::string messageToJSON(const Poco::Message& message)
{
	std::ostringstream json;
	
	json 
		<< "{"
		<< quote("source") << ":"
		<< jsonize(message.getSource())
		<< ","
		<< quote("text") << ":"
		<< jsonize(message.getText())
		<< ","
		<< quote("priority") << ":"
		<< static_cast<int>(message.getPriority())
		<< ","
		<< quote("timestamp") << ":"
		<< quote(Poco::DateTimeFormatter::format(message.getTime(), Poco::DateTimeFormat::ISO8601_FRAC_FORMAT))
		<< "}";
	
	return json.str();
}


Poco::BasicEvent<void> ConsoleRequestHandler::_stopped;


ConsoleRequestHandler::ConsoleRequestHandler(Poco::AutoPtr<Poco::EventChannel> pChannel, Poco::OSP::BundleContext::Ptr pContext):
	_pChannel(pChannel),
	_pContext(pContext)
{
	_stopped += Poco::delegate(this, &ConsoleRequestHandler::onStopped);
}

	
ConsoleRequestHandler::~ConsoleRequestHandler()
{
	_stopped -= Poco::delegate(this, &ConsoleRequestHandler::onStopped);
}

	
void ConsoleRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	try
	{
		std::string username;
		Poco::OSP::Web::WebSession::Ptr pSession;
		{
			Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = _pContext->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
			if (pWebSessionManagerRef)
			{
				Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
				pSession = pWebSessionManager->find(_pContext->thisBundle()->properties().getString("websession.id"), request);
				username = pSession->getValue<std::string>("username", "");
			}
		}	
	
		if (!username.empty())
		{
			Poco::Net::WebSocket webSocket(request, response);
			_pContext->logger().information(Poco::format("Console WebSocket connection established with %s.", request.clientAddress().toString()));
			forwardMessages(webSocket);
		}
		else
		{
			response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
			response.setContentLength(0);
			response.send();
		}
	}
	catch (Poco::Net::WebSocketException& exc)
	{
		_pContext->logger().log(exc);
		switch (exc.code())
		{
		case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
			response.set("Sec-WebSocket-Version", Poco::Net::WebSocket::WEBSOCKET_VERSION);
			// fallthrough
		case Poco::Net::WebSocket::WS_ERR_NO_HANDSHAKE:
		case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
		case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
			response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
			response.setContentLength(0);
			response.send();
			break;
		}
	}
}


void ConsoleRequestHandler::stopAll()
{
	_stopped();
}


void ConsoleRequestHandler::forwardMessages(Poco::Net::WebSocket& webSocket)
{
	_pChannel->messageLogged += Poco::delegate(this, &ConsoleRequestHandler::onMessageLogged);
	
	try
	{
		Poco::AutoPtr<Poco::Notification> pNf = _queue.waitDequeueNotification();
		while (pNf)
		{
			Poco::AutoPtr<MessageNotification> pMessageNf = pNf.cast<MessageNotification>();
			if (pNf)
			{
				std::string json(messageToJSON(pMessageNf->message()));
				webSocket.sendFrame(json.data(), static_cast<int>(json.size()));				
				pNf = _queue.waitDequeueNotification();
			}
			// break if StopNotification
		}
	}
	catch (Poco::Exception&)
	{
	}
	
	_pChannel->messageLogged -= Poco::delegate(this, &ConsoleRequestHandler::onMessageLogged);
}


void ConsoleRequestHandler::onMessageLogged(const Poco::Message& message)
{
	if (_queue.size() < MAX_QUEUE_SIZE)
	{
		_queue.enqueueNotification(new MessageNotification(message));
	}
}


void ConsoleRequestHandler::onStopped()
{
	_queue.enqueueUrgentNotification(new StopNotification);
}


} } } // namespace IoT::Web::Console
