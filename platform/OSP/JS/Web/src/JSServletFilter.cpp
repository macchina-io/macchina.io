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
	_hasFilterMemoryLimit(false),
	_maxUploadSize(2*1024*1024),
	_hasMaxUploadSize(false),
	_maxUploadCount(4),
	_hasMaxUploadCount(false)
{
	Poco::OSP::Web::WebFilter::Args::const_iterator it = args.find("memoryLimit"s);
	if (it != args.end())
	{
		_memoryLimit = Poco::NumberParser::parseUnsigned64(it->second);
		_hasFilterMemoryLimit = true;
	}
	it = args.find("maxUploadSize"s);
	if (it != args.end())
	{
		_maxUploadSize = Poco::NumberParser::parseUnsigned64(it->second);
		_hasMaxUploadSize = true;
	}
	it = args.find("maxUploadCount"s);
	if (it != args.end())
	{
		_maxUploadCount = Poco::NumberParser::parseUnsigned64(it->second);
		_hasMaxUploadCount = true;
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
				long timeout = pBundle->properties().getUInt32("osp.js.jssTimeout"s, 30000);
				Poco::ScopedLock<JSServletExecutorHolder> lock(*pExecutorHolder, timeout);
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

				Poco::UInt64 maxUploadSize = _maxUploadSize;
				if (!_hasMaxUploadSize)
				{
					maxUploadSize = pBundle->properties().getUInt64("osp.js.maxUploadSize"s, _maxUploadSize);
				}

				unsigned maxUploadCount = _maxUploadCount;
				if (!_hasMaxUploadCount)
				{
					maxUploadCount = pBundle->properties().getUInt("osp.js.maxUploadCount"s, _maxUploadCount);
				}

				std::string moduleSearchPaths = pBundle->properties().getString("osp.js.moduleSearchPaths"s, ""s);
				Poco::StringTokenizer tok(moduleSearchPaths, ",;"s, Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
				_moduleSearchPaths.insert(_moduleSearchPaths.begin(), tok.begin(), tok.end());

				JSServletExecutor::Ptr pExecutor = new JSServletExecutor(_pContext->contextForBundle(pBundle), pBundle, servlet, Poco::URI(scriptURI), _moduleSearchPaths, memoryLimit, maxUploadSize, maxUploadCount);
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
			sendErrorResponse(response, "Script execution failed. See the server log for details."s);
		}
	}
	catch (Poco::TimeoutException& exc)
	{
		_pContext->logger().error("Request timed out waiting for servlet script %s to become available."s, request.getURI());
		if (!response.sent())
		{
			sendErrorResponse(response, "The request timed out waiting for the script to become available. See the server log for details."s);
		}
	}
	catch (Poco::Exception& exc)
	{
		_pContext->logger().log(exc);
		if (!response.sent())
		{
			sendErrorResponse(response, "The request could not be processed. See the server log for details."s);
		}
	}
}


void JSServletFilter::preprocess(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& uri, std::istream& resourceStream, std::string& servlet)
{
	// The $servlet function is created to prevent the script from
	// creating global variables. V8 does not seem to garbage collect
	// global variables, resulting in memory leaks.
	servlet += "function $servlet(request, response, form, uploads, session) { ";
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
