//
// JSServerPageFilter.cpp
//
// $Id: //poco/1.4/OSP/JS/src/JSServerPageFilter.cpp#1 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "JSServerPageFilter.h"
#include "JSSPage.h"
#include "JSSPageReader.h"


namespace Poco {
namespace OSP {
namespace JS {


JSServerPageFilter::JSServerPageFilter(Poco::OSP::BundleContext::Ptr pContext, const Poco::OSP::Web::WebFilter::Args& args):
	JSServletFilter(pContext, args)
{
}


void JSServerPageFilter::preprocess(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, const std::string& path, std::istream& resourceStream, std::string& servlet)
{
	JSSPage page;
	JSSPageReader pageReader(page, path);
	pageReader.parse(resourceStream);
	// The $servlet function is created to prevent the script from
	// creating global variables. V8 does not seem to garbage collect
	// global variables, resulting in memory leaks.
	servlet += "function $servlet() { ";
	servlet += page.handler().str();
	servlet += "\nresponse.send();";
	servlet += "}\n$servlet();";
	response.setContentType(page.get("contentType", "text/html"));
}


} } } // namespace Poco::OSP::JS
