//
// WebIndex.cpp
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/Web/WebServerDispatcher.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/AutoPtr.h"
#include "Poco/ClassLibrary.h"


using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::OSP::Web::WebRequestHandlerFactory;
using Poco::OSP::Web::WebServerDispatcher;
using Poco::OSP::Service;
using Poco::OSP::ServiceRef;
using Poco::AutoPtr;


class IndexHandler: public HTTPRequestHandler
	/// Return a HTML document with a list of all available
	/// resources on the OSP web server.
{
public:
	IndexHandler(AutoPtr<WebServerDispatcher> pWebServerDispatcher):
		_pWebServerDispatcher(pWebServerDispatcher)
	{
	}
	
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		WebServerDispatcher::PathInfoMap pathInfos;
		_pWebServerDispatcher->listVirtualPaths(pathInfos);
		
		response.setContentType("text/html");
		response.setChunkedTransferEncoding(true);
		std::ostream& ostr = response.send();

		const std::string& softwareVersion = request.serverParams().getSoftwareVersion();

		ostr << "<HTML><HEAD><TITLE>Server Index</TITLE>"
		        "<LINK REL=\"stylesheet\" HREF=\"css/styles.css\" TYPE=\"text/css\"/></HEAD><BODY>"
		        "<DIV CLASS=\"header\">"
				"<H1 CLASS=\"category\">Open Service Platform</h1>"
				"<H1 CLASS=\"title\">Web Server Index</H1>"
				"</DIV>"
		        "<DIV CLASS=\"body\">"
		        "<P>The following resources are available on this server:</P>"
		        "<UL>";
		for (WebServerDispatcher::PathInfoMap::const_iterator it = pathInfos.begin(); it != pathInfos.end(); ++it)
		{
			ostr << "<LI>";
			std::string title(it->second.description);
			if (title.empty()) title = it->first;
			ostr << "<A HREF=\"" << it->first << "\" TITLE=\"Path: " << it->first << "\">" << htmlize(title) << "</A><BR>";
			ostr << "<I>" << htmlize(it->second.pBundle->name()) << " " 
			     << it->second.pBundle->version().toString() << "</I></LI>";
		}
		ostr << "</UL><HR><P>";
		ostr << htmlize(softwareVersion) << " at " << request.serverAddress().toString();
		ostr << "</P></DIV></BODY></HTML>";
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
	AutoPtr<WebServerDispatcher> _pWebServerDispatcher;
};


class IndexHandlerFactory: public WebRequestHandlerFactory
{
public:
	IndexHandlerFactory()
	{
	}

	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
	{
		const std::string& path = request.getURI();
		if (path == "/" || path == "/index.html")
			return new IndexHandler(_pWebServerDispatcher);
		else
			return 0;
	}
	
protected:
	void initImpl()
	{
		ServiceRef::Ptr pWebServerDispatcherRef = context()->registry().findByName(WebServerDispatcher::SERVICE_NAME);
		if (pWebServerDispatcherRef)
		{
			 _pWebServerDispatcher = pWebServerDispatcherRef->castedInstance<WebServerDispatcher>();
		}
	}
	
private:
	AutoPtr<WebServerDispatcher> _pWebServerDispatcher;
};


POCO_BEGIN_NAMED_MANIFEST(WebServer, WebRequestHandlerFactory)
	POCO_EXPORT_CLASS(IndexHandlerFactory)
POCO_END_MANIFEST
