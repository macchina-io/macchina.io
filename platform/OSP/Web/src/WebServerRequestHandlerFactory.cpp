//
// WebServerRequestHandlerFactory.cpp
//
// $Id: //poco/1.4/OSP/Web/src/WebServerRequestHandlerFactory.cpp#2 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebServerRequestHandlerFactory
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/Web/WebServerRequestHandlerFactory.h"
#include "Poco/OSP/Web/WebServerRequestHandler.h"


namespace Poco {
namespace OSP {
namespace Web {


WebServerRequestHandlerFactory::WebServerRequestHandlerFactory(WebServerDispatcher& dispatcher, bool secure):
	_dispatcher(dispatcher),
	_secure(secure)
{
}

	
WebServerRequestHandlerFactory::~WebServerRequestHandlerFactory()
{
}


Poco::Net::HTTPRequestHandler* WebServerRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new WebServerRequestHandler(_dispatcher, _secure);
}


} } } // namespace Poco::OSP::Web
