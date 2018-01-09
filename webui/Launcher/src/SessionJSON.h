//
// SessionJSON.h
//
// This file has been generated from SessionJSON.cpsp on 2017-09-04 17:34:19.
//


#ifndef SessionJSON_INCLUDED
#define SessionJSON_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace Web {
namespace Launcher {


class SessionJSON: public Poco::Net::HTTPRequestHandler
{
public:
	SessionJSON(Poco::OSP::BundleContext::Ptr);

	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

protected:
	Poco::OSP::BundleContext::Ptr context() const
	{
		return _pContext;
	}

	Poco::OSP::BundleContext::Ptr c() const
	{
		return _pContext;
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
};


class SessionJSONFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};


} } } // namespace IoT::Web::Launcher


#endif // SessionJSON_INCLUDED
