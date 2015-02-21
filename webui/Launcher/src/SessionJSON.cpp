//
// SessionJSON.cpp
//
// This file has been generated from SessionJSON.cpsp on 2015-02-20 12:17:59.
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
#line 3 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
 if (session) { 	responseStream << "\n";
	responseStream << "\t\"authenticated\": ";
#line 4 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
	responseStream << ( session->getValue<std::string>("username", "") != "" ? "true" : "false" );
	responseStream << ",\n";
	responseStream << "\t\"username\": \"";
#line 5 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
	responseStream << ( session->getValue<std::string>("username", "") );
	responseStream << "\",\n";
	responseStream << "\t\"message\": \"";
#line 6 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
	responseStream << ( session->getValue<std::string>("message", "") );
	responseStream << "\",\n";
	responseStream << "\t\"lastError\": \"";
#line 7 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
	responseStream << ( session->getValue<std::string>("lastError", "") );
	responseStream << "\"\n";
	responseStream << "";
#line 8 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
 } else { 	responseStream << "\n";
	responseStream << "\t \"authenticated\": false\n";
	responseStream << "";
#line 10 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/SessionJSON.cpsp"
 } 	responseStream << "\n";
	responseStream << "}\n";
	responseStream << "";
}


Poco::Net::HTTPRequestHandler* SessionJSONFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new SessionJSON(context());
}


} } } // namespace IoT::Web::Launcher
