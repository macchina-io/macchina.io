//
// JSServerPageFilter.h
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_Web_JSServerPageFilter_INCLUDED
#define OSP_JS_Web_JSServerPageFilter_INCLUDED


#include "JSServletFilter.h"
#include "JSServletExecutorCache.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


class JSServerPageFilter: public JSServletFilter
	/// A web filter for executing JavaScript server pages.
{
public:
	JSServerPageFilter(Poco::OSP::BundleContext::Ptr pContext, const Poco::OSP::Web::WebFilter::Args& args, JSServletExecutorCache& cache);
		/// Creates the JSServerPageFilter using the given BundleContext.

protected:
	void preprocess(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& uri, std::istream& resourceStream, std::string& servlet);
};


class JSServerPageFilterFactory: public Poco::OSP::Web::WebFilterFactory
	/// The factory for JSServerPageFilter.
{
public:
	JSServerPageFilterFactory():
		_cache(JSServletExecutorCache::instance())
	{
	}

	Poco::OSP::Web::WebFilter* createFilter(const Poco::OSP::Web::WebFilter::Args& args)
	{
		return new JSServerPageFilter(context(), args, _cache);
	}

private:
	JSServletExecutorCache& _cache;
};


} } } } // namespace Poco::OSP::JS::Web


#endif // OSP_JS_Web_JSServerPageFilter_INCLUDED
