//
// ControllerRequestHandler.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "ControllerRequestHandler.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"


using Poco::OSP::ServiceFinder;
using Poco::format;


namespace IoT {
namespace Web {
namespace Launcher {


ControllerRequestHandler::ControllerRequestHandler(Poco::OSP::BundleContext::Ptr pContext, int sessionTimeout, const std::string& authServiceName):
	_pContext(pContext),
	_pSessionManager(ServiceFinder::find<Poco::OSP::Web::WebSessionManager>(pContext)),
	_pAuthService(ServiceFinder::findByName<Poco::OSP::Auth::AuthService>(pContext, authServiceName)),
	_sessionId(pContext->thisBundle()->properties().getString("websession.id")),
	_sessionTimeout(sessionTimeout),
	_logger(Poco::Logger::get("Launcher.ControllerRequestHandler"))
{
}


void ControllerRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	if (request.getURI() == "/favicon.ico")
	{
		return response.redirect("/images/favicon.ico", Poco::Net::HTTPResponse::HTTP_SEE_OTHER);
	}

	Poco::OSP::Web::WebSession::Ptr pSession = _pSessionManager->get(_sessionId, request, _sessionTimeout, context());

	const std::string loginPage = "/macchina/login";
	const std::string launcherPage = "/macchina/launcher";

	std::string message;
	std::string nextPage;
	std::string username;
	Poco::Net::HTMLForm form(request, request.stream());
	std::string action(form.get("action", ""));
	
	if (action == "login")
	{
		username = form.get("username", "");
		std::string password = form.get("password", "");
		if (_pAuthService->authenticate(username, password))
		{
			if (_logger.information())
			{
				_logger.information(format("User %s successfully logged in.", username));
			}
			nextPage = launcherPage;
			pSession->set("username", username);
		}
		else
		{
			if (_logger.warning())
			{
				_logger.warning(format("User %s failed authentication.", username));
			}
			message = "The given username is not known, the password is wrong or the account has been disabled.";
		}
	}
	else if (action == "logout")
	{
		username = pSession->getValue<std::string>("username", "");
		if (!username.empty())
		{
			if (_logger.information())
			{
				_logger.information(format("User %s logged out.", username));
			}
			_pSessionManager->remove(pSession);
		}
	}
	else
	{
		username = pSession->getValue<std::string>("username", "");
		if (!username.empty())
		{
			nextPage = launcherPage;
		}
	}
	
	if (!message.empty())
	{
		pSession->set("message", message);
	}
	else
	{
		pSession->erase("message");
	}
	
	if (nextPage.empty())
	{
		nextPage = loginPage;
	}
	response.setContentLength(0);
	response.redirect(nextPage, Poco::Net::HTTPResponse::HTTP_SEE_OTHER);
	response.set("Cache-Control", "no-cache");
}


ControllerRequestHandlerFactory::ControllerRequestHandlerFactory():
	_configured(false),
	_sessionTimeout(3600),
	_authServiceName("osp.auth")
{
}


Poco::Net::HTTPRequestHandler* ControllerRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	configure();

	return new ControllerRequestHandler(context(), _sessionTimeout, _authServiceName);
}


void ControllerRequestHandlerFactory::configure()
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	if (!_configured)
	{
		_configured = true;

		Poco::OSP::ServiceRef::Ptr pPrefsSvcRef = context()->registry().findByName(Poco::OSP::PreferencesService::SERVICE_NAME);
		if (pPrefsSvcRef)
		{
			Poco::OSP::PreferencesService::Ptr pPrefsSvc = pPrefsSvcRef->castedInstance<Poco::OSP::PreferencesService>();

			_sessionTimeout = pPrefsSvc->configuration()->getInt("macchina.web.sessionTimeout", _sessionTimeout);
			_authServiceName = pPrefsSvc->configuration()->getString("macchina.authService", _authServiceName);
		}
	}
}


} } } // namespace IoT::Web::Launcher
