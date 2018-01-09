//
// BundleActionsRequestHandler.h
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef BundleAdmin_BundleActionsRequestHandler_INCLUDED
#define BundleAdmin_BundleActionsRequestHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace Web {
namespace BundleAdmin {


class BundleActionsRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
	BundleActionsRequestHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the BundleActionsRequestHandler using the given bundle context.

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


class BundleActionsRequestHandlerFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};


} } } // namespace IoT::Web::BundleAdmin


#endif // BundleAdmin_BundleActionsRequestHandler_INCLUDED
