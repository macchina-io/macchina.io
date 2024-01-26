//
// LogLevelRequestHandler.h
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef Console_LogLevelRequestHandler_INCLUDED
#define Console_LogLevelRequestHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace Web {
namespace Console {


class LogLevelRequestHandler: public Poco::Net::HTTPRequestHandler
	/// This class handles an incoming WebSocket upgrade request, 
	/// and streams log messages to the client.
{
public:
	explicit LogLevelRequestHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the LogLevelRequestHandler.
		
	~LogLevelRequestHandler();
		/// Destroys the LogLevelRequestHandler.
		
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		/// Handles an incoming WebSocket upgrade request and starts streaming log messages
		/// until the client closes the WebSocket.

protected:
	void handleGET(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	void handlePATCH(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	static bool isAuthenticated(Poco::OSP::Web::WebSession::Ptr pSession, const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	static bool isMutating(const Poco::Net::HTTPServerRequest& request);
	static std::string levelToString(int level);

private:
	Poco::OSP::BundleContext::Ptr _pContext;
};


} } } // namespace IoT::Web::Console


#endif // Console_LogLevelRequestHandler_INCLUDED
