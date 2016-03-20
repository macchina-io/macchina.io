//
// JSServerPageFilter.h
//
// $Id: //poco/1.4/OSP/JS/src/JSServerPageFilter.h#1 $
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_JS_Web_JSServerPageFilter_INCLUDED
#define OSP_JS_Web_JSServerPageFilter_INCLUDED


#include "JSServletFilter.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


class JSServerPageFilter: public JSServletFilter
	/// A web filter for executing JavaScript server pages.
{
public:
	JSServerPageFilter(Poco::OSP::BundleContext::Ptr pContext, const Poco::OSP::Web::WebFilter::Args& args);
		/// Creates the JSServerPageFilter using the given BundleContext.

protected:
	void preprocess(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& uri, std::istream& resourceStream, std::string& servlet);
};


class JSServerPageFilterFactory: public Poco::OSP::Web::WebFilterFactory
	/// The factory for JSServerPageFilter.
{
public:
	Poco::OSP::Web::WebFilter* createFilter(const Poco::OSP::Web::WebFilter::Args& args)
	{
		return new JSServerPageFilter(context(), args);
	}
};


} } } } // namespace Poco::OSP::JS::Web


#endif // OSP_JS_Web_JSServerPageFilter_INCLUDED
