//
// LauncherAppsJSON.cpp
//
// This file has been generated from LauncherAppsJSON.cpsp on 2020-02-14 12:01:52.
//


#include "LauncherAppsJSON.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/DeflatingStream.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "AppRegistry.h"
#include "Utility.h"


using namespace std::string_literals;


namespace IoT {
namespace Web {
namespace Launcher {


LauncherAppsJSON::LauncherAppsJSON(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void LauncherAppsJSON::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("application/json"s);
	bool _compressResponse(request.hasToken("Accept-Encoding"s, "gzip"s));
	if (_compressResponse) response.set("Content-Encoding"s, "gzip"s);

	Poco::OSP::Web::WebSession::Ptr session;
	{
		Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = context()->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
		if (pWebSessionManagerRef)
		{
			Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
			session = pWebSessionManager->find(context()->thisBundle()->properties().getString("websession.id"s), request);
		}
	}
	if (!(U::isAuthenticated(session, response))) return;

	Poco::Net::HTMLForm form(request, request.stream());
#line 13 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/LauncherAppsJSON.cpsp"

std::string username = session->getValue<std::string>("username");
Poco::OSP::Auth::AuthService::Ptr pAuthService = Poco::OSP::ServiceFinder::findByName<Poco::OSP::Auth::AuthService>(context(), "osp.auth");
AppRegistry::Ptr pAppRegistry = Poco::OSP::ServiceFinder::find<AppRegistry>(context());
AppRegistry::AppVec apps;
pAppRegistry->list(apps);
int i = 0;
	std::ostream& _responseStream = response.send();
	Poco::DeflatingOutputStream _gzipStream(_responseStream, Poco::DeflatingStreamBuf::STREAM_GZIP, 1);
	std::ostream& responseStream = _compressResponse ? _gzipStream : _responseStream;
	responseStream << "\n";
	responseStream << "[\n";
#line 22 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/LauncherAppsJSON.cpsp"
 for (AppRegistry::AppVec::const_iterator it = apps.begin(); it != apps.end(); ++it) { 	responseStream << "\n";
	responseStream << "  ";
#line 23 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/LauncherAppsJSON.cpsp"
 if (it->permission.empty() || pAuthService->authorize(username, it->permission)) { 	responseStream << "\n";
	responseStream << "    ";
#line 24 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/LauncherAppsJSON.cpsp"
	responseStream << ( i++ ? "," : "" );
	responseStream << "\n";
	responseStream << "  {\n";
	responseStream << "    \"id\": ";
#line 26 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/LauncherAppsJSON.cpsp"
	responseStream << ( U::jsonize(it->id) );
	responseStream << ",\n";
	responseStream << "    \"title\": ";
#line 27 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/LauncherAppsJSON.cpsp"
	responseStream << ( U::jsonize(it->title) );
	responseStream << ",\n";
	responseStream << "    \"icon\": ";
#line 28 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/LauncherAppsJSON.cpsp"
	responseStream << ( U::jsonize(it->icon) );
	responseStream << ",\n";
	responseStream << "    \"tooltip\": ";
#line 29 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/LauncherAppsJSON.cpsp"
	responseStream << ( U::jsonize(it->tooltip) );
	responseStream << ",\n";
	responseStream << "    \"link\": ";
#line 30 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/LauncherAppsJSON.cpsp"
	responseStream << ( U::jsonize(it->path) );
	responseStream << "\n";
	responseStream << "  }\n";
	responseStream << "  ";
#line 32 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/LauncherAppsJSON.cpsp"
 } 	responseStream << "\n";
#line 33 "/ws/git/macchina-io/macchina.io/webui/Launcher/src/LauncherAppsJSON.cpsp"
 } 	responseStream << "\n";
	responseStream << "]\n";
	if (_compressResponse) _gzipStream.close();
}


Poco::Net::HTTPRequestHandler* LauncherAppsJSONFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new LauncherAppsJSON(context());
}


} } } // namespace IoT::Web::Launcher
