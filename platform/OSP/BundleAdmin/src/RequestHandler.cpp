//
// RequestHandler.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "RequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"


using Poco::Util::MapConfiguration;
using Poco::AutoPtr;


RequestHandler::RequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext),
	_pStream(0),
	_pTemplateArgs(new MapConfiguration)
{
}


RequestHandler::~RequestHandler()
{
}


std::ostream& RequestHandler::stream()
{
	if (!_pStream)
	{
		response().setContentType("text/html");
		response().setChunkedTransferEncoding(true);
		_pStream = &response().send();
	}
	return *_pStream;
}


void RequestHandler::beginPage(const std::string& title)
{
	templat().clear();
	templat().setString("title", htmlize(title));
	templat().setString("backlink", std::string());
	sendTemplate("html.beginPage");
}


void RequestHandler::beginPage(const std::string& title, const std::string backlinkPath, const std::string& backlinkTitle)
{
	templat().clear();
	templat().setString("title", htmlize(title));
	templat().setString("backlink", bundle()->properties().getString("html.backlink"));
	templat().setString("backlink.path", backlinkPath);
	templat().setString("backlink.title", htmlize(backlinkTitle));
	sendTemplate("html.beginPage");
}


void RequestHandler::endPage()
{
	sendTemplate("html.endPage");
}


void RequestHandler::beginTable()
{
	sendTemplate("html.beginTable");
}


void RequestHandler::endTable()
{
	sendTemplate("html.endTable");
}

	
void RequestHandler::beginRow(bool even)
{
	sendTemplate(even ? "html.beginEvenRow" : "html.beginOddRow");
}

	
void RequestHandler::endRow()
{
	sendTemplate("html.endRow");
}

	
void RequestHandler::beginHeaderCell()
{
	sendTemplate("html.beginHeaderCell");
}

	
void RequestHandler::endHeaderCell()
{
	sendTemplate("html.endHeaderCell");
}

	
void RequestHandler::beginCell()
{
	sendTemplate("html.beginCell");
}

	
void RequestHandler::endCell()
{
	sendTemplate("html.endCell");
}


void RequestHandler::headerCell(const std::string& text)
{
	beginHeaderCell();
	write(text);
	endHeaderCell();
}

	
void RequestHandler::cell(const std::string& text)
{
	beginCell();
	write(text);
	endCell();
}


void RequestHandler::beginList()
{
	sendTemplate("html.beginList");
}

	
void RequestHandler::endList()
{
	sendTemplate("html.endList");
}

	
void RequestHandler::beginItem()
{
	sendTemplate("html.beginItem");
}

	
void RequestHandler::endItem()
{
	sendTemplate("html.endItem");
}

	
void RequestHandler::item(const std::string& text)
{
	beginItem();
	write(text);
	endItem();
}


void RequestHandler::item(const std::string& label, const std::string& value)
{
	beginItem();
	stream() << "<B>";
	write(label);
	stream() << ":</B> ";
	write(value);
	endItem();
}


void RequestHandler::heading(const std::string& title)
{
	templat().clear();
	templat().setString("title", htmlize(title));
	sendTemplate("html.heading");
}


void RequestHandler::beginPara()
{
	sendTemplate("html.beginPara");
}


void RequestHandler::endPara()
{
	sendTemplate("html.endPara");
}


void RequestHandler::beginActionBar()
{
	sendTemplate("html.beginActionBar");
}


void RequestHandler::endActionBar()
{
	sendTemplate("html.endActionBar");
}


void RequestHandler::write(const std::string& text)
{
	stream() << htmlize(text);
}


void RequestHandler::action(Poco::OSP::Bundle::Ptr pBundle, const std::string& action, const std::string& label)
{
	this->action(pBundle, std::string(), action, label);
}


void RequestHandler::action(Poco::OSP::Bundle::Ptr pBundle, const std::string& actionPath, const std::string& action, const std::string& label)
{
	this->action(pBundle->symbolicName(), actionPath, action, label);
}


void RequestHandler::action(const std::string& actionPath, const std::string& action, const std::string& label)
{
	this->action(std::string(), actionPath, action, label);
}


void RequestHandler::action(const std::string& symbolicName, const std::string& actionPath, const std::string& action, const std::string& label)
{
	beginCell();
	templat().clear();
	templat().setString("symbolicName", symbolicName);
	templat().setString("action", action);
	templat().setString("actionLabel", label);
	templat().setString("actionPath", bundle()->properties().expand(actionPath));
	sendTemplate("html.actionForm");
	endCell();
}


void RequestHandler::sendTemplate(const std::string& templateName)
{
	stream() << templat().expand(bundle()->properties().getString(templateName));
}


void RequestHandler::linkBundle(Poco::OSP::Bundle::ConstPtr pBundle, const std::string& name)
{
	templat().clear();
	templat().setString("symbolicName", pBundle->symbolicName());
	templat().setString("name", name);
	sendTemplate("html.bundleLink");
}


void RequestHandler::linkBundle(const std::string& symbolicName)
{
	templat().clear();
	templat().setString("symbolicName", symbolicName);
	templat().setString("name", symbolicName);
	sendTemplate("html.bundleLink");
}


std::string RequestHandler::text(const std::string& id)
{
	std::string resId("text.");
	resId += id;
	return templat().expand(bundle()->properties().getString(resId));
}


std::string RequestHandler::htmlize(const std::string& str)
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
