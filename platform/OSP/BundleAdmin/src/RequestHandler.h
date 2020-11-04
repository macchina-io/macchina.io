//
// RequestHandler.h
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef BundleAdmin_RequestHandler_INCLUDED
#define BundleAdmin_RequestHandler_INCLUDED


#include "Poco/Net/AbstractHTTPRequestHandler.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/Util/MapConfiguration.h"
#include "Poco/AutoPtr.h"
#include <ostream>


class RequestHandler: public Poco::Net::AbstractHTTPRequestHandler
	/// The base class for all request handlers.
{
protected:
	RequestHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the RequestHandler.

	~RequestHandler();
		/// Destroys the RequestHandler.
	
	Poco::OSP::BundleContext::Ptr context() const;
		/// Returns the bundle context.
	
	Poco::OSP::Bundle::ConstPtr bundle() const;
		/// Returns the bundle.
		
	Poco::Util::MapConfiguration& templat();
		/// Returns the template args.
		
	std::ostream& stream();
		/// Prepares the response (when called for the first time)
		/// and returns the response stream.

	void beginPage(const std::string& title);
		/// Writes the beginning of the HTML page.

	void beginPage(const std::string& title, const std::string backlinkPath, const std::string& backlinkTitle);
		/// Writes the beginning of the HTML page and includes a link to the parent page.
	
	void endPage();
		/// Finishes the HTML page.
		
	void beginTable();
		/// Starts a table.
		
	void endTable();
		/// Ends a table.
		
	void beginRow(bool even);
		/// Starts a table row.
		
	void endRow();
		/// Ends a table row.
		
	void beginHeaderCell();
		/// Starts a header cell.
		
	void endHeaderCell();
		/// Ends a header cell.
		
	void beginCell();
		/// Begins a cell.
		
	void endCell();
		/// Ends a cell.
		
	void headerCell(const std::string& text);
		/// Writes a header cell.
		
	void cell(const std::string& text);
		/// Writes a cell.
		
	void beginList();
		/// Starts an unordered list.
		
	void endList();
		/// Ends an unordered list.
		
	void beginItem();
		/// Starts a list item.
		
	void endItem();
		/// Ends a list item.
		
	void item(const std::string& text);
		/// Writes a list item.

	void item(const std::string& label, const std::string& value);
		/// Writes a list item.
		
	void heading(const std::string& title);
		/// Writes a heading.
		
	void beginPara();
		/// Starts a paragraph.
		
	void endPara();
		/// Ends a paragraph.
		
	void beginActionBar();
		/// Starts an action bar.
		
	void endActionBar();
		/// Ends an action bar.
		
	void write(const std::string& text);
		/// Writes some text.

	void action(Poco::OSP::Bundle::Ptr pBundle, const std::string& action, const std::string& label);
		/// Writes an action button.
		
	void action(Poco::OSP::Bundle::Ptr pBundle, const std::string& actionPath, const std::string& action, const std::string& label);
		/// Writes an action button.

	void action(const std::string& actionPath, const std::string& action, const std::string& label);
		/// Writes an action button.

	void action(const std::string& symbolicName, const std::string& actionPath, const std::string& action, const std::string& label);
		/// Writes an action button.
		
	void sendTemplate(const std::string& templateName);
		/// Sends a template.
		
	void linkBundle(Poco::OSP::Bundle::ConstPtr pBundle, const std::string& name);
		/// Writes a link to a bundle.

	void linkBundle(const std::string& symbolicName);
		/// Writes a link to a bundle.

	std::string text(const std::string& id);
		/// Returns a text fragment from the resources.

	static std::string htmlize(const std::string& str);
		/// Escapes characters in str to make it valid HTML.
			
private:
	Poco::OSP::BundleContext::Ptr _pContext;
	std::ostream* _pStream;
	Poco::AutoPtr<Poco::Util::MapConfiguration> _pTemplateArgs;
};


//
// inlines
//
inline Poco::OSP::BundleContext::Ptr RequestHandler::context() const
{
	return _pContext;
}


inline Poco::OSP::Bundle::ConstPtr RequestHandler::bundle() const
{
	return _pContext->thisBundle();
}


inline Poco::Util::MapConfiguration& RequestHandler::templat()
{
	return *_pTemplateArgs;
}


#endif // BundleAdmin_RequestHandler_INCLUDED
