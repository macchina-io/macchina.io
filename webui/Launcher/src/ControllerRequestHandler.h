//
// ControllerRequestHandler.h
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef Launcher_ControllerRequestHandler_INCLUDED
#define Launcher_ControllerRequestHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"


namespace IoT {
namespace Web {
namespace Launcher {


class ControllerRequestHandler: public Poco::Net::HTTPRequestHandler
	/// This class handles incoming web requests and either
	/// redirects them to the login page (if no valid session
	/// cookie is found), or to the launcher page.
{
public:
	ControllerRequestHandler(Poco::OSP::BundleContext::Ptr pContext, int sessionTimeout, const std::string& authServiceName);
		/// Creates a ControllerRequestHandler, using the
		/// given BundleContext.

	// HTTPRequestHandler
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

protected:
	Poco::OSP::BundleContext::Ptr context() const
	{
		return _pContext;
	}
	
private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::Web::WebSessionManager::Ptr _pSessionManager;
	Poco::OSP::Auth::AuthService::Ptr _pAuthService;
	std::string _sessionId;
	int _sessionTimeout;
	Poco::Logger& _logger;
};


class ControllerRequestHandlerFactory: public Poco::OSP::Web::WebRequestHandlerFactory
	/// The WebRequestHandlerFactory for ControllerRequestHandler objects.
{
public:
	ControllerRequestHandlerFactory();
		/// Creates the ControllerRequestHandlerFactory.
		
	// WebRequestHandlerFactory
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

protected:
	void configure();

private:
	Poco::FastMutex _mutex;
	bool _configured;
	int _sessionTimeout;
	std::string _authServiceName;
};


} } } // namespace IoT::Web::Launcher


#endif // Launcher_ControllerRequestHandler_INCLUDED
