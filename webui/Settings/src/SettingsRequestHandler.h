//
// SettingsRequestHandler.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef Settings_SettingsRequestHandler_INCLUDED
#define Settings_SettingsRequestHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace Web {
namespace Settings {


class SettingsRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
	SettingsRequestHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the SettingsRequestHandler using the given bundle context.

	// Poco::Net::HTTPRequestHandler
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

protected:
	void handleSave(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	void handleLoad(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

	Poco::OSP::BundleContext::Ptr context() const
	{
		return _pContext;
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
};


class SettingsRequestHandlerFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};


} } } // namespace IoT::Web::Settings


#endif // Settings_SettingsRequestHandler_INCLUDED
