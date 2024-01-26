//
// LogLevelRequestHandler.cpp
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "LogLevelRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Logger.h"


using namespace std::string_literals;


namespace IoT {
namespace Web {
namespace Console {


LogLevelRequestHandler::LogLevelRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


LogLevelRequestHandler::~LogLevelRequestHandler()
{
}


void LogLevelRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::OSP::Web::WebSession::Ptr pSession;
	{
		Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = _pContext->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
		if (pWebSessionManagerRef)
		{
			Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
			pSession = pWebSessionManager->find(_pContext->thisBundle()->properties().getString("websession.id"s), request);
		}
	}
	if (!isAuthenticated(pSession, request, response)) return;

	if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET)
	{
		handleGET(request, response);
	}
	else if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_PATCH)
	{
		handlePATCH(request, response);
	}
	else
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
		response.setContentLength(0);
		response.setChunkedTransferEncoding(false);
		response.send();
	}
}


void LogLevelRequestHandler::handleGET(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::JSON::Object::Ptr pObject = new Poco::JSON::Object;
	std::vector<std::string> names;
	Poco::Logger::names(names);
	for (const auto& name: names)
	{
		Poco::Logger& logger = Poco::Logger::get(name);
		pObject->set(name, levelToString(logger.getLevel()));
	}
	response.setContentType("application/json"s);
	response.setChunkedTransferEncoding(true);
	std::ostream& responseStream = response.send();
	pObject->stringify(responseStream);
}


void LogLevelRequestHandler::handlePATCH(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	try
	{
		Poco::JSON::Parser parser;
		const auto json = parser.parse(request.stream());
		Poco::JSON::Object::Ptr pObject = json.extract<Poco::JSON::Object::Ptr>();
		for (const auto& p: *pObject)
		{
			if (Poco::Logger::has(p.first))
			{
				_pContext->logger().debug("Setting log level of logger '%s' to %s."s, p.first, p.second.toString());
				if (p.first.empty())
				{
					Poco::Logger::setLevel(p.first, Poco::Logger::parseLevel(p.second.toString()));
				}
				else
				{
					Poco::Logger::get(p.first).setLevel(Poco::Logger::parseLevel(p.second.toString()));
				}
			}
		}
		response.setContentLength(0);
		response.setChunkedTransferEncoding(false);
		response.send();
	}
	catch (Poco::Exception& exc)
	{
		_pContext->logger().log(exc);
		if (!response.sent())
		{
			response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
			response.setContentLength(0);
			response.setChunkedTransferEncoding(false);
			response.send();
		}
	}
}


bool LogLevelRequestHandler::isAuthenticated(Poco::OSP::Web::WebSession::Ptr pSession, const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	if (!pSession || !pSession->has("username") || (isMutating(request) && request.get("X-XSRF-TOKEN"s, ""s) != pSession->csrfToken()))
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
		response.setContentLength(0);
		response.setChunkedTransferEncoding(false);
		response.send();
		return false;
	}
	return true;
}


bool LogLevelRequestHandler::isMutating(const Poco::Net::HTTPServerRequest& request)
{
	const std::string& method = request.getMethod();
	return method != Poco::Net::HTTPRequest::HTTP_GET && method != Poco::Net::HTTPRequest::HTTP_HEAD;
}


std::string LogLevelRequestHandler::levelToString(int level)
{
	switch (level)
	{
	case 0:
		return "none"s;
	case Poco::Message::PRIO_FATAL:
		return "fatal"s;
	case Poco::Message::PRIO_CRITICAL:
		return "critical"s;
	case Poco::Message::PRIO_ERROR:
		return "error"s;
	case Poco::Message::PRIO_WARNING:
		return "warning"s;
	case Poco::Message::PRIO_NOTICE:
		return "notice"s;
	case Poco::Message::PRIO_INFORMATION:
		return "information"s;
	case Poco::Message::PRIO_DEBUG:
		return "debug"s;
	case Poco::Message::PRIO_TRACE:
		return "trace"s;
	default:
		return "unknown"s;
	}
}


} } } // namespace IoT::Web::Console
