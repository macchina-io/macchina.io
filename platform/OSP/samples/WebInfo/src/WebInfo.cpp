//
// WebInfo.cpp
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
#include "Poco/Net/IPAddress.h"
#include "Poco/Net/NetworkInterface.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Environment.h"
#include "Poco/Process.h"
#include "Poco/ClassLibrary.h"


using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::OSP::Web::WebRequestHandlerFactory;
using Poco::Environment;
using Poco::DateTime;
using Poco::LocalDateTime;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::Process;


class InfoHandler: public HTTPRequestHandler
	/// Return a HTML document with information about the process.
{
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		response.setContentType("text/html");
		response.setChunkedTransferEncoding(true);
		std::ostream& ostr = response.send();

		const std::string& softwareVersion = request.serverParams().getSoftwareVersion();
		LocalDateTime now;

		std::string osName = Environment::osName();
		std::string osDisplayName = Environment::osDisplayName();
		if (osDisplayName != osName)
		{
			osName += " (";
			osName += osDisplayName;
			osName += ")";
		}

		ostr << "<HTML><HEAD><TITLE>Server Information</TITLE>"
		        "<LINK REL=\"stylesheet\" HREF=\"css/styles.css\" TYPE=\"text/css\"/></HEAD><BODY>"
		        "<DIV CLASS=\"header\">"
				"<H1 CLASS=\"category\">Open Service Platform</h1>"
				"<H1 CLASS=\"title\">Server Information</H1>"
				"</DIV>"
		        "<DIV CLASS=\"body\">"
		        "<UL>";
		    
		ostr << "<LI><B>Host:</B> " << Environment::nodeName() << "</LI>"
		     << "<LI><B>Node ID:</B> " << Environment::nodeId() << "</LI>"
		     << "<LI><B>IP Addresses:</B> " << getHostAddresses() << "</LI>"
		     << "<LI><B>OS Name:</B> " << osName << "</LI>"
		     << "<LI><B>OS Version:</B> " << Environment::osVersion() << "</LI>"
		     << "<LI><B>OS Architecture:</B> " << Environment::osArchitecture() << "</LI>"
		     << "<LI><B>Processor Cores:</B> " << Environment::processorCount() << "</LI>"
		     << "<LI><B>Local Server Time:</B> " << DateTimeFormatter::format(now, DateTimeFormat::HTTP_FORMAT) << "</LI>"
		     << "<LI><B>Server Process ID:</B> " << Process::id() << "</LI>";
		   
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
	
	std::string getHostAddresses()
	{
		std::string result;
		Poco::Net::NetworkInterface::NetworkInterfaceList list = Poco::Net::NetworkInterface::list();
		for (Poco::Net::NetworkInterface::NetworkInterfaceList::iterator it = list.begin(); it != list.end(); ++it)
		{
			const Poco::Net::IPAddress& addr = it->address();
			if (addr.isUnicast() && !addr.isLoopback())
			{
				if (!result.empty())
					result += ", ";
				result += addr.toString();
			}
		}
		return result;
	}
};


class InfoHandlerFactory: public WebRequestHandlerFactory
{
public:
	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
	{
		return new InfoHandler;
	}
};


POCO_BEGIN_NAMED_MANIFEST(WebServer, WebRequestHandlerFactory)
	POCO_EXPORT_CLASS(InfoHandlerFactory)
POCO_END_MANIFEST
