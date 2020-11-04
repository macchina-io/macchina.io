//
// WebSession.cpp
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/ClassLibrary.h"


using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTMLForm;
using Poco::OSP::Web::WebRequestHandlerFactory;
using Poco::OSP::Web::WebSession;
using Poco::OSP::Web::WebSessionManager;
using Poco::OSP::Service;
using Poco::OSP::ServiceRef;
using Poco::OSP::BundleContext;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::AnyCast;


class SessionHandler: public HTTPRequestHandler
	/// This sample demonstrates the usage of the WebSessionManager class.
{
public:
	SessionHandler(WebSessionManager::Ptr pWebSessionManager, int timeout, BundleContext::Ptr pContext):
		_pWebSessionManager(pWebSessionManager),
		_timeout(timeout),
		_pContext(pContext)
	{
	}
	
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		// See if we already have a session
		WebSession::Ptr pSession = _pWebSessionManager->find("sample", request);
		bool haveSession = !pSession.isNull();
		if (!haveSession)
		{
			// no session - create one
			pSession = _pWebSessionManager->get("sample", request, _timeout, _pContext);
		}
		
		// set session properties
		HTMLForm form(request);
		if (form.has("name") && form.has("value"))
		{
			std::string name = form["name"];
			std::string value = form["value"];
			if (value.empty())
			{
				if (pSession->find(name) != pSession->end())
					pSession->erase(name);
			}
			else pSession->set(name, value);
		}
		
		response.setContentType("text/html");
		response.setChunkedTransferEncoding(true);
		std::ostream& ostr = response.send();
		
		ostr <<
			"<HTML>\n"
			"<HEAD>\n"
			"<TITLE>WebSession Sample</TITLE>\n"
			"</HEAD>\n"
			"<BODY>\n"
			"<H1>WebSession Sample</H1>\n"
			"<FORM METHOD=\"GET\">\n"
			"<TABLE BORDER=\"0\" CELLSPACING=\"4\" CELLPADDING=\"4\">\n"
			"<TR>"
			"<TH>Name</TH><TH>Value (leave empty to remove)</TH>"
			"</TR>\n"
			"<TR>"
			"<TD><INPUT TYPE=\"text\" name=\"name\" size=\"31\"></TD>"
			"<TD><INPUT TYPE=\"text\" name=\"value\" size=\"31\"></TD>"
			"</TR>\n"
			"<TR>"
			"<TD></TD><TD><INPUT TYPE=\"submit\" VALUE=\"Set\"></TD>"
			"</TR>\n"
			"</TABLE>\n"
			"</FORM>\n";
			
		if (!haveSession)
		{
			ostr << "<P>A new session has been created.</P>";
		}
		ostr << 
			"<H2>Session:</H2>"
			"<UL>"
			"<LI>Created: " << DateTimeFormatter::format(pSession->created(), DateTimeFormat::HTTP_FORMAT) << "</LI>"
			"<LI>Expires: " << DateTimeFormatter::format(pSession->getExpiration(), DateTimeFormat::HTTP_FORMAT) << "</LI>";
		for (WebSession::Attributes::const_iterator it = pSession->begin(); it != pSession->end(); ++it)
		{
			ostr << "<LI>" << htmlize(it->first) << ": " << htmlize(AnyCast<std::string>(it->second)) << "</LI>";
		}
		ostr << "</UL></BODY></HTML>";
	}
	
protected:
	std::string htmlize(const std::string& str)
	{
		std::string::const_iterator it(str.begin());
		std::string::const_iterator end(str.end());
		std::string html;
		for (; it != end; ++it)
		{
			switch (*it)
			{
			case '<': html += "&lt;"; break;
			case '>': html += "&gt;"; break;
			case '"': html += "&quot;"; break;
			case '&': html += "&amp;"; break;
			default:  html += *it; break;
			}
		}
		return html;
	}
	
private:
	WebSessionManager::Ptr _pWebSessionManager;
	int _timeout;
	BundleContext::Ptr _pContext;
};


class SessionHandlerFactory: public WebRequestHandlerFactory
{
public:
	SessionHandlerFactory():
		_timeout(0)
	{
	}

	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
	{
		return new SessionHandler(_pWebSessionManager, _timeout, context());
	}
	
protected:
	void initImpl()
	{
		_timeout = context()->thisBundle()->properties().getInt("timeout", 30);
		ServiceRef::Ptr pWebSessionManagerRef = context()->registry().findByName(WebSessionManager::SERVICE_NAME);
		if (pWebSessionManagerRef)
		{
			 _pWebSessionManager = pWebSessionManagerRef->castedInstance<WebSessionManager>();
		}
	}
	
private:
	WebSessionManager::Ptr _pWebSessionManager;
	int _timeout;
};


POCO_BEGIN_NAMED_MANIFEST(WebServer, WebRequestHandlerFactory)
	POCO_EXPORT_CLASS(SessionHandlerFactory)
POCO_END_MANIFEST
