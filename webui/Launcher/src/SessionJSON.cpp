//
// SessionJSON.cpp
//
// This file has been generated from SessionJSON.cpsp on 2017-09-03 11:58:09.
//


#include "SessionJSON.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"


namespace IoT {
namespace Web {
namespace Launcher {


SessionJSON::SessionJSON(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void SessionJSON::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("application/json");

	Poco::OSP::Web::WebSession::Ptr session;
	{
		Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = context()->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
		if (pWebSessionManagerRef)
		{
			Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
			session = pWebSessionManager->find(context()->thisBundle()->properties().getString("websession.id"), request);
		}
	}
	Poco::Net::HTMLForm form(request, request.stream());
	std::ostream& responseStream = response.send();
	responseStream << "";
	responseStream << "\n";
	responseStream << "{\n";
	responseStream << "";
#line 3 "/Users/guenter/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
 if (session) { 	responseStream << "\n";
	responseStream << "  \"authenticated\": ";
#line 4 "/Users/guenter/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
	responseStream << ( session->getValue<std::string>("username", "") != "" ? "true" : "false" );
	responseStream << ",\n";
	responseStream << "  \"username\": \"";
#line 5 "/Users/guenter/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
	responseStream << ( session->getValue<std::string>("username", "") );
	responseStream << "\",\n";
	responseStream << "  \"message\": \"";
#line 6 "/Users/guenter/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
	responseStream << ( session->getValue<std::string>("message", "") );
	responseStream << "\",\n";
	responseStream << "  \"lastError\": \"";
#line 7 "/Users/guenter/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
	responseStream << ( session->getValue<std::string>("lastError", "") );
	responseStream << "\"\n";
	responseStream << "";
#line 8 "/Users/guenter/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
 } else { 	responseStream << "\n";
	responseStream << "  \"authenticated\": false\n";
	responseStream << "";
#line 10 "/Users/guenter/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
 } 	responseStream << "\n";
	responseStream << "}\n";
	responseStream << "";
}


Poco::Net::HTTPRequestHandler* SessionJSONFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new SessionJSON(context());
}


} } } // namespace IoT::Web::Launcher
