//
// JSServerPageFilter.cpp
//
// Copyright (c) 2013-2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "JSServerPageFilter.h"
#include "JSSPage.h"
#include "JSSPageReader.h"


namespace Poco {
namespace OSP {
namespace JS {
namespace Web {


JSServerPageFilter::JSServerPageFilter(Poco::OSP::BundleContext::Ptr pContext, const Poco::OSP::Web::WebFilter::Args& args, JSServletExecutorCache& cache):
	JSServletFilter(pContext, args, cache)
{
}


void JSServerPageFilter::preprocess(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& uri, std::istream& resourceStream, std::string& servlet)
{
	JSSPage page;
	JSSPageReader pageReader(page, uri);
	pageReader.parse(resourceStream);
	// The $servlet function is created to prevent the script from
	// creating global variables. V8 does not seem to garbage collect
	// global variables, resulting in memory leaks.
	servlet += "function $servlet(request, response, form, session) { ";
	servlet += page.handler().str();
	servlet += "\nresponse.send();\n";
	servlet += "}\n";
	response.setContentType(page.get("contentType", "text/html"));
}


} } } } // namespace Poco::OSP::JS::Web
