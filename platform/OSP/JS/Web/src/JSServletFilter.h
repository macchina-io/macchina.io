//
// JSServletFilter.h
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_Web_JSServletFilter_INCLUDED
#define OSP_JS_Web_JSServletFilter_INCLUDED


#include "Poco/OSP/Web/WebFilter.h"
#include "Poco/OSP/Web/WebFilterFactory.h"
#include "Poco/Mutex.h"
#include "JSServletExecutor.h"
#include "JSServletExecutorCache.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


class JSServletFilter: public Poco::OSP::Web::WebFilter
	/// A web filter for executing JavaScript servlets.
{
public:
	JSServletFilter(Poco::OSP::BundleContext::Ptr pContext, const Poco::OSP::Web::WebFilter::Args& args, JSServletExecutorCache& cache);
		/// Creates the JSServletFilter using the given BundleContext.

	// Poco::OSP::Web::WebFilter
	void process(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& path, std::istream& resourceStream, Poco::OSP::Bundle::ConstPtr pBundle);

protected:
	virtual void preprocess(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& uri, std::istream& resourceStream, std::string& servlet);
	Poco::OSP::BundleContext::Ptr context() const;
	void sendErrorResponse(Poco::Net::HTTPServerResponse& response, const std::string& message);

private:
	BundleContext::Ptr _pContext;
	JSServletExecutorCache& _cache;
	std::vector<std::string> _moduleSearchPaths;
	Poco::UInt64 _memoryLimit;
	bool _hasFilterMemoryLimit;
	Poco::UInt64 _maxUploadSize;
	bool _hasMaxUploadSize;
	unsigned _maxUploadCount;
	bool _hasMaxUploadCount;
};


class JSServletFilterFactory: public Poco::OSP::Web::WebFilterFactory
	/// The factory for JSServletFilter.
{
public:
	JSServletFilterFactory():
		_cache(JSServletExecutorCache::instance())
	{
	}

	Poco::OSP::Web::WebFilter* createFilter(const Poco::OSP::Web::WebFilter::Args& args)
	{
		return new JSServletFilter(context(), args, _cache);
	}

private:
	JSServletExecutorCache& _cache;
};


//
// inlines
//
inline Poco::OSP::BundleContext::Ptr JSServletFilter::context() const
{
	return _pContext;
}


} } } } // namespace Poco::OSP::JS::Web


#endif // OSP_JS_Web_JSServletFilter_INCLUDED
