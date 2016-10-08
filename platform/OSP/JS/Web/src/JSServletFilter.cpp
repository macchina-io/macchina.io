//
// JSServletFilter.cpp
//
// $Id: //poco/1.4/OSP/JS/src/JSServletFilter.cpp#1 $
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "JSServletFilter.h"
#include "Poco/StreamCopier.h"
#include "Poco/NumberParser.h"
#include "Poco/StringTokenizer.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


namespace
{
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
}


JSServletFilter::JSServletFilter(Poco::OSP::BundleContext::Ptr pContext, const Poco::OSP::Web::WebFilter::Args& args, JSServletExecutorCache& cache):
	_pContext(pContext),
	_cache(cache),
	_memoryLimit(1024*1024)
{
	Poco::OSP::Web::WebFilter::Args::const_iterator it = args.find("memoryLimit");
	if (it != args.end())
	{
		_memoryLimit = Poco::NumberParser::parseUnsigned64(it->second);
	}
	it = args.find("searchPaths");
	if (it != args.end())
	{
		Poco::StringTokenizer tok(it->second, ",;", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		_moduleSearchPaths.assign(tok.begin(), tok.end());
	}
}


void JSServletFilter::process(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& path, std::istream& resourceStream, Poco::OSP::Bundle::ConstPtr pBundle)
{
	try
	{
		response.setContentType("text/html");

		std::string scriptURI("bndl://");
		scriptURI += pBundle->symbolicName();
		if (path.empty() || path[0] != '/') scriptURI += "/";
		scriptURI += path;

		JSServletExecutorHolder::Ptr pExecutorHolder;
		{
			Poco::ScopedLockWithUnlock<JSServletExecutorCache> cacheLock(_cache);

			pExecutorHolder = _cache.get(scriptURI);
			if (pExecutorHolder)
			{
				cacheLock.unlock();
				Poco::ScopedLock<JSServletExecutorHolder> lock(*pExecutorHolder);
				pExecutorHolder->executor()->prepareRequest(request, response);
				pExecutorHolder->executor()->handleRequest(request, response);
			}
			else
			{
				std::string servlet;
				preprocess(request, response, scriptURI, resourceStream, servlet);
				Poco::UInt64 memoryLimit = pBundle->properties().getUInt64("osp.js.memoryLimit", _memoryLimit);
				JSServletExecutor::Ptr pExecutor = new JSServletExecutor(_pContext->contextForBundle(pBundle), pBundle, servlet, Poco::URI(scriptURI), _moduleSearchPaths, memoryLimit);
				pExecutor->prepareRequest(request, response);
				pExecutor->run();
				pExecutorHolder = new JSServletExecutorHolder(pExecutor);
				Poco::ScopedLock<JSServletExecutorHolder> lock(*pExecutorHolder);
				_cache.add(scriptURI, pExecutorHolder);
				cacheLock.unlock();
				pExecutorHolder->executor()->handleRequest(request, response);
			}
		}
	
		if (!response.sent())
		{
			sendErrorResponse(response, "Script execution failed. See server log for details.");
		}
	}
	catch (Poco::Exception& exc)
	{
		_pContext->logger().log(exc);
		if (!response.sent())
		{
			sendErrorResponse(response, exc.displayText());
		}
	}
}


void JSServletFilter::preprocess(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& uri, std::istream& resourceStream, std::string& servlet)
{
	// The $servlet function is created to prevent the script from
	// creating global variables. V8 does not seem to garbage collect
	// global variables, resulting in memory leaks.
	servlet += "function $servlet(request, response, form, session) { ";
	Poco::StreamCopier::copyToString(resourceStream, servlet);
	servlet += " }\n";
}


void JSServletFilter::sendErrorResponse(Poco::Net::HTTPServerResponse& response, const std::string& message)
{
	if (!response.sent())
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
		response.setChunkedTransferEncoding(true);
		response.setContentType("text/html");
		response.send()
			<< "<html>"
			<< "<head><title>" << response.getStatus() << ": " << response.getReason() << "</title></head>"
			<< "<body>"
			<< "<h1>" << response.getStatus() << ": " << response.getReason() << "</h1>"
			<< "<p>" << htmlize(message) << "</p>"
			<< "</body>"
			<< "</html>";
	}
}


} } } } // namespace Poco::OSP::JS::Web
