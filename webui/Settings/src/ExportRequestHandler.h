//
// ExportRequestHandler.h
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef Settings_ExportRequestHandler_INCLUDED
#define Settings_ExportRequestHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace Web {
namespace Settings {


class ExportRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
	ExportRequestHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the ExportRequestHandler using the given bundle context.

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


class ExportRequestHandlerFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};


} } } // namespace IoT::Web::Settings


#endif // Settings_ExportRequestHandler_INCLUDED
