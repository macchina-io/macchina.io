//
// LauncherAppsJSON.h
//
// This file has been generated from LauncherAppsJSON.cpsp on 2015-02-19 17:45:05.
//


#ifndef LauncherAppsJSON_INCLUDED
#define LauncherAppsJSON_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace Web {
namespace Launcher {


class LauncherAppsJSON: public Poco::Net::HTTPRequestHandler
{
public:
	LauncherAppsJSON(Poco::OSP::BundleContext::Ptr);

	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

protected:
	Poco::OSP::BundleContext::Ptr context() const
	{
		return _pContext;
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
};


class LauncherAppsJSONFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};


} } } // namespace IoT::Web::Launcher


#endif // LauncherAppsJSON_INCLUDED
