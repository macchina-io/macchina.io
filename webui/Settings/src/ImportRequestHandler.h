//
// ImportRequestHandler.h
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef Settings_ImportRequestHandler_INCLUDED
#define Settings_ImportRequestHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace Web {
namespace Settings {


class ImportRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
	ImportRequestHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the ImportRequestHandler using the given bundle context.

	// Poco::Net::HTTPRequestHandler
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

	Poco::OSP::BundleContext::Ptr context() const
	{
		return _pContext;
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
};


class ImportRequestHandlerFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};


} } } // namespace IoT::Web::Settings


#endif // Settings_ImportRequestHandler_INCLUDED
