//
// LoginPage.h
//
// This file has been generated from LoginPage.cpsp on 2017-07-29 17:26:46.
//


#ifndef LoginPage_INCLUDED
#define LoginPage_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace Web {
namespace Launcher {


class LoginPage: public Poco::Net::HTTPRequestHandler
{
public:
	LoginPage(Poco::OSP::BundleContext::Ptr);

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


class LoginPageFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};


} } } // namespace IoT::Web::Launcher


#endif // LoginPage_INCLUDED
