//
// WebServerRequestHandler.h
//
// $Id: //poco/1.7/OSP/Web/include/Poco/OSP/Web/WebServerRequestHandler.h#1 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebServerRequestHandler
//
// Definition of the WebServerRequestHandler class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_Web_WebServerRequestHandler_INCLUDED
#define OSP_Web_WebServerRequestHandler_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/Net/HTTPRequestHandler.h"


namespace Poco {
namespace OSP {
namespace Web {


class WebServerDispatcher;


class OSPWeb_API WebServerRequestHandler: public Poco::Net::HTTPRequestHandler
	/// A WebServerRequestHandler is some sort of MetaHttpRequestHandlerFactory.
	/// It uses an instance of WebServerDispatcher to dispatch the request
	/// to an appropriate request handler.
{
public:
	WebServerRequestHandler(WebServerDispatcher& dispatcher, bool secure);
		/// Creates the WebServerRequestHandler, using the given WebServerDispatcher.
		
	~WebServerRequestHandler();
		/// Destroys the WebServerRequestHandler.
		
	// HTTPRequestHandler
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	
private:
	WebServerDispatcher& _dispatcher;
	bool _secure;
};


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebServerRequestHandler_INCLUDED
