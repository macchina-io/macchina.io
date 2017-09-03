//
// LoginPage.cpp
//
// This file has been generated from LoginPage.cpsp on 2017-09-03 11:58:09.
//


#include "LoginPage.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/DeflatingStream.h"


#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Utility.h"


namespace IoT {
namespace Web {
namespace Launcher {


LoginPage::LoginPage(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void LoginPage::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html");
	bool _compressResponse(request.hasToken("Accept-Encoding", "gzip"));
	if (_compressResponse) response.set("Content-Encoding", "gzip");

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
#line 9 "/Users/guenter/ws/git/macchina-io/macchina.io/webui/Launcher/src/LoginPage.cpsp"

std::string message;
if (session)
{
    message = session->getValue<std::string>("message", "");
}
	std::ostream& _responseStream = response.send();
	Poco::DeflatingOutputStream _gzipStream(_responseStream, Poco::DeflatingStreamBuf::STREAM_GZIP, 1);
	std::ostream& responseStream = _compressResponse ? _gzipStream : _responseStream;
	responseStream << "<!DOCTYPE HTML>\n";
	responseStream << "";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "";
	responseStream << "\n";
	responseStream << "\n";
	responseStream << "<html lang=\"en\">\n";
	responseStream << "  <head>\n";
	responseStream << "    <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">\n";
	responseStream << "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\">\n";
	responseStream << "    <title>macchina.io</title>\n";
	responseStream << "    <link rel=\"stylesheet\" href=\"/css/macchina.css\" type=\"text/css\"/>\n";
	responseStream << "    <link rel=\"icon\" href=\"/images/favicon.ico\">\n";
	responseStream << "    <script type=\"text/javascript\" src=\"/jquery/jquery.min.js\"></script>\n";
	responseStream << "  </head>\n";
	responseStream << "  <body>\n";
	responseStream << "    <header>\n";
	responseStream << "      <div class=\"headercontainer\">\n";
	responseStream << "        <div class=\"header\">\n";
	responseStream << "          <h1>\n";
	responseStream << "            <a href=\"/\"><img src=\"/images/headerlogo.png\" srcset=\"/images/headerlogo-x2.png 2x\" alt=\"macchina.io\"></a>\n";
	responseStream << "          </h1>\n";
	responseStream << "        </div>\n";
	responseStream << "      </div>\n";
	responseStream << "    </header>\n";
	responseStream << "    <div class=\"contentcontainer\">\n";
	responseStream << "      <div class=\"content\">\n";
	responseStream << "        ";
#line 38 "/Users/guenter/ws/git/macchina-io/macchina.io/webui/Launcher/src/LoginPage.cpsp"
 if (!message.empty()) { 	responseStream << "\n";
	responseStream << "          <div class=\"error\">\n";
	responseStream << "            ";
#line 40 "/Users/guenter/ws/git/macchina-io/macchina.io/webui/Launcher/src/LoginPage.cpsp"
	responseStream << ( U::htmlize(message) );
	responseStream << "\n";
	responseStream << "          </div>\n";
	responseStream << "        ";
#line 42 "/Users/guenter/ws/git/macchina-io/macchina.io/webui/Launcher/src/LoginPage.cpsp"
 } 	responseStream << "\n";
	responseStream << "\n";
	responseStream << "        <div class=\"loginBox\">\n";
	responseStream << "          <form method=\"post\" action=\"/\">\n";
	responseStream << "            <table>\n";
	responseStream << "              <tr>\n";
	responseStream << "                <th id=\"usernameLabelCell\">Username:</th>\n";
	responseStream << "                <td id=\"usernameInputCell\">\n";
	responseStream << "                  <input id=\"usernameInput\" type=\"text\" name=\"username\">\n";
	responseStream << "                </td>\n";
	responseStream << "              </tr>\n";
	responseStream << "              <tr>\n";
	responseStream << "                <th id=\"passwordLabelCell\">Password:</th>\n";
	responseStream << "                <td id=\"passwordInputCell\">\n";
	responseStream << "                  <input id=\"passwordInput\" type=\"password\" name=\"password\">\n";
	responseStream << "                </td>\n";
	responseStream << "              </tr>\n";
	responseStream << "              <tr>\n";
	responseStream << "                <td>&nbsp;</td>\n";
	responseStream << "                <td id=\"loginButtonCell\">\n";
	responseStream << "                  <input id=\"loginButton\" type=\"submit\" name=\"accept\" value=\"Login\">\n";
	responseStream << "                </td>\n";
	responseStream << "              </tr>\n";
	responseStream << "            </table>\n";
	responseStream << "            <input type=\"hidden\" name=\"action\" value=\"login\">\n";
	responseStream << "           </form>\n";
	responseStream << "        </div>\n";
	responseStream << "      </div>\n";
	responseStream << "    </div>\n";
	responseStream << "    <script type=\"text/javascript\">\n";
	responseStream << "    $(document).ready(\n";
	responseStream << "      function()\n";
	responseStream << "      {\n";
	responseStream << "        $('#usernameInput').focus();\n";
	responseStream << "      }\n";
	responseStream << "    );\n";
	responseStream << "    </script>\n";
	responseStream << "  </body>\n";
	responseStream << "</html>\n";
	responseStream << "";
	if (_compressResponse) _gzipStream.close();
}


Poco::Net::HTTPRequestHandler* LoginPageFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new LoginPage(context());
}


} } } // namespace IoT::Web::Launcher
