//
// WebEventRequestHandler.cpp
//
// Library: OSP/WebEvent
// Package: WebEvent
// Module:  WebEventRequestHandler
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/WebEvent/WebEventRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Buffer.h"
#include "Poco/Format.h"


namespace Poco {
namespace OSP {
namespace WebEvent {


WebEventRequestHandler::WebEventRequestHandler(WebEventServiceImpl::Ptr pWebEventServiceImpl, Poco::OSP::BundleContext::Ptr pContext):
	_pWebEventServiceImpl(pWebEventServiceImpl),
	_pContext(pContext)
{
}

	
WebEventRequestHandler::~WebEventRequestHandler()
{
}

	
void WebEventRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	if (authenticate() && authorize())
	{
		try
		{
			_pWebEventServiceImpl->preflightRequest(request);
			if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
			{
				const Poco::Net::HTTPServerRequest* pRequest = &request;
				_pWebEventServiceImpl->requestReceived(pRequest);
				if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
				{
					Poco::SharedPtr<Poco::Net::WebSocket> pWS = new Poco::Net::WebSocket(request, response);
					_pContext->logger().information(Poco::format("WebSocket connection established with %s.", request.clientAddress().toString()));
					_pWebEventServiceImpl->addSubscriber(pWS);
				}
				else
				{
					_pContext->logger().notice(Poco::format("WebSocket connection from %s rejected by delegate (status=%d).",
						request.clientAddress().toString(),
						static_cast<int>(response.getStatus())));
					response.setContentLength(0);
					response.send();
				}
			}
			else
			{
				_pContext->logger().notice(Poco::format("WebSocket connection from %s rejected by preflight (status=%d).",
					request.clientAddress().toString(),
					static_cast<int>(response.getStatus())));
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
	else
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
		response.setContentLength(0);
		response.send();
	}
}

bool WebEventRequestHandler::authenticate() const
{
	// TODO: actually authenticate
	return true;
}


bool WebEventRequestHandler::authorize() const
{
	// TODO: actually authorize
	return true;
}


} } } // namespace Poco::OSP::WebEvent
