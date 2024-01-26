//
// JSServletFilter.cpp
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "JSServletFilter.h"
#include "Poco/StreamCopier.h"
#include "Poco/NumberParser.h"
#include "Poco/StringTokenizer.h"


using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {



JSServletFilter::JSServletFilter(Poco::OSP::BundleContext::Ptr pContext, const Poco::OSP::Web::WebFilter::Args& args, JSServletExecutorCache& cache):
	_pContext(pContext),
	_cache(cache),
	_memoryLimit(JSExecutor::getDefaultMemoryLimit()),
	_hasFilterMemoryLimit(false)
{
	Poco::OSP::Web::WebFilter::Args::const_iterator it = args.find("memoryLimit"s);
	if (it != args.end())
	{
		_memoryLimit = Poco::NumberParser::parseUnsigned64(it->second);
		_hasFilterMemoryLimit = true;
	}
	it = args.find("searchPaths"s);
	if (it != args.end())
	{
		Poco::StringTokenizer tok(it->second, ",;"s, Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		_moduleSearchPaths.assign(tok.begin(), tok.end());
	}
}


void JSServletFilter::process(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& path, std::istream& resourceStream, Poco::OSP::Bundle::ConstPtr pBundle)
{
	try
	{
		response.setContentType("text/html"s);

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

				Poco::UInt64 memoryLimit = _memoryLimit;
				if (!_hasFilterMemoryLimit)
				{
					memoryLimit = pBundle->properties().getUInt64("osp.js.memoryLimit"s, _memoryLimit);
				}

				std::string moduleSearchPaths = pBundle->properties().getString("osp.js.moduleSearchPaths"s, ""s);
				Poco::StringTokenizer tok(moduleSearchPaths, ",;", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
				_moduleSearchPaths.insert(_moduleSearchPaths.begin(), tok.begin(), tok.end());

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
		response.setContentType("text/html"s);
		response.send()
			<< "<html>"
			<< "<head><title>" << response.getStatus() << ": " << response.getReason() << "</title></head>"
			<< "<body>"
			<< "<h1>" << response.getStatus() << ": " << response.getReason() << "</h1>"
			<< "<p>" << Poco::Net::htmlize(message) << "</p>"
			<< "</body>"
			<< "</html>";
	}
}


} } } } // namespace Poco::OSP::JS::Web
