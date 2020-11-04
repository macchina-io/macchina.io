//
// RequestHandlerFactory.h
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef BundleAdmin_RequestHandlerFactory_INCLUDED
#define BundleAdmin_RequestHandlerFactory_INCLUDED


#include "Poco/OSP/Web/WebRequestHandlerFactory.h"


template <class Handler>
class RequestHandlerFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request)
	{
		return new Handler(context());
	}
};


#endif // BundleAdmin_RequestHandlerFactory_INCLUDED
