//
// SandboxRequestHandler.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "SandboxRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Utility.h"


namespace IoT {
namespace Web {
namespace Playground {


const std::string SandboxRequestHandler::SANDBOX_BUNDLE("io.macchina.webui.playground.sandbox");
const std::string SandboxRequestHandler::SANDBOX_SCRIPT("sandbox.js");


SandboxRequestHandler::SandboxRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void SandboxRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{	
	Poco::OSP::Web::WebSession::Ptr pSession;
	{
		Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = context()->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
		if (pWebSessionManagerRef)
		{
			Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
			pSession = pWebSessionManager->find(context()->thisBundle()->properties().getString("websession.id"), request);
		}
	}
	if (!Utility::isAuthenticated(pSession, response)) return;

	std::string username = pSession->getValue<std::string>("username");
	Poco::OSP::Auth::AuthService::Ptr pAuthService = Poco::OSP::ServiceFinder::findByName<Poco::OSP::Auth::AuthService>(context(), "osp.auth");

	if (!pAuthService->authorize(username, "bundleAdmin"))
	{
		response.setContentLength(0);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
		response.send();
		return;
	}
	
	Poco::Path p(request.getURI(), Poco::Path::PATH_UNIX);
	p.makeFile();
	std::string action = p.getBaseName();
	
	context()->logger().debug("Performing action: " + action);
	
	std::string bundleState;
	std::string error;
	Poco::OSP::Bundle::Ptr pBundle = context()->findBundle(SANDBOX_BUNDLE);
	if (pBundle)
	{
		try
		{
			if (action == "run")
			{
				pBundle->start();
			}
			else if (action == "stop")
			{
				pBundle->stop();
			}
			else if (action == "restart")
			{
				if (pBundle->state() == Poco::OSP::Bundle::BUNDLE_ACTIVE)
				{
					pBundle->stop();
				}
				pBundle->start();
			}
			else if (action == "load")
			{
				Poco::Path scriptPath(pBundle->path());
				scriptPath.makeDirectory();
				scriptPath.setFileName(SANDBOX_SCRIPT);
				response.set("Cache-Control", "no-cache");
				if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET)
				{
					response.sendFile(scriptPath.toString(), "text/plain");
				}
				else if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_HEAD)
				{
					Poco::File f(scriptPath.toString());
					Poco::Timestamp dateTime = f.getLastModified();
					Poco::File::FileSize length = f.getSize();
					response.set("Last-Modified", Poco::DateTimeFormatter::format(dateTime, Poco::DateTimeFormat::HTTP_FORMAT));
					response.setContentLength64(length);
					response.setContentType("text/plain");
					response.send();
				}
				return;
			}
			else if (action == "save")
			{
				Poco::Path scriptPath(pBundle->path());
				scriptPath.makeDirectory();
				scriptPath.setFileName(SANDBOX_SCRIPT);
				Poco::FileOutputStream ostr(scriptPath.toString());
				Poco::StreamCopier::copyStream(request.stream(), ostr);
			}
			else if (action == "state")
			{
				// Nothing to do
			}
			else
			{
				context()->logger().error("Invalid action: " + action);
			}
		}
		catch (Poco::Exception& exc)
		{
			error = exc.displayText();
			context()->logger().log(exc);
		}
		bundleState = pBundle->stateString();
	}
	else
	{
		error = "The sandbox bundle is not available.";
	}
	
	response.setContentType("application/json");
	response.setChunkedTransferEncoding(true);
	response.send()
		<< "{"
		<< "\"bundleState\":" << Utility::jsonize(bundleState) << ","
		<< "\"error\":" << Utility::jsonize(error)
		<< "}";
}


Poco::Net::HTTPRequestHandler* SandboxRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new SandboxRequestHandler(context());
}


} } } // namespace IoT::Web::Playground
