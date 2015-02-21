//
// BundleListRequestHandler.h
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef BundleAdmin_BundleListRequestHandler_INCLUDED
#define BundleAdmin_BundleListRequestHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace Web {
namespace BundleAdmin {


class BundleListRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
	BundleListRequestHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the BundleListRequestHandler using the given bundle context.

	// Poco::Net::HTTPRequestHandler
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

protected:
	Poco::OSP::BundleContext::Ptr context() const
	{
		return _pContext;
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
};


class BundleListRequestHandlerFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};


} } } // namespace IoT::Web::BundleAdmin


#endif // BundleAdmin_BundleListRequestHandler_INCLUDED
