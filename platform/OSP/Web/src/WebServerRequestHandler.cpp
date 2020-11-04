//
// WebServerRequestHandler.cpp
//
// Library: OSP/Web
// Package: Web
// Module:  WebServerRequestHandler
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Web/WebServerRequestHandler.h"
#include "Poco/OSP/Web/WebServerDispatcher.h"


namespace Poco {
namespace OSP {
namespace Web {


WebServerRequestHandler::WebServerRequestHandler(WebServerDispatcher& dispatcher, bool secure):
	_dispatcher(dispatcher),
	_secure(secure)
{
}

	
WebServerRequestHandler::~WebServerRequestHandler()
{
}

	
void WebServerRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	_dispatcher.handleRequest(request, response, _secure);
}


} } } // namespace Poco::OSP::Web
