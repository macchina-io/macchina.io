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


using namespace std::string_literals;


namespace
{
	std::string escape(const std::string& str)
	{
		std::string::const_iterator it(str.begin());
		std::string::const_iterator end(str.end());
		std::string escaped;
		for (; it != end; ++it)
		{
			switch (*it)
			{
			case '\'': escaped += "\\'"; break;
			case '\"': escaped += "\\\""; break;
			case '\\': escaped += "\\\\"; break;
			case '\n': escaped += "\\n"; break;
			case '\r': escaped += "\\r"; break;
			case '\t': escaped += "\\t"; break;
			default:  escaped += *it; break;
			}
		}
		return escaped;
	}
}


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
	servlet += "function $servlet(request, response, form, uploads, session) { ";

	servlet += "\nresponse.contentType = '" + escape(page.get("page.contentType"s, "text/html"s)) + "';";
	
	const std::string contentLanguage(page.get("page.contentLanguage"s, ""s));
	if (!contentLanguage.empty())
	{
		servlet += "\nresponse.set('Content-Language', '" + escape(contentLanguage) + "');";
	}

	const std::string contentSecurityPolicy(page.get("page.contentSecurityPolicy"s, ""s));
	if (!contentSecurityPolicy.empty())
	{
		servlet += "\nresponse.set('Content-Security-Policy', '" + escape(contentSecurityPolicy) + "');";
	}

	const std::string cacheControl(page.get("page.cacheControl"s, ""s));
	if (!cacheControl.empty())
	{
		servlet += "\nresponse.set('Cache-Control', '" + escape(cacheControl) + "');";
	}

	const std::string referrerPolicy(page.get("page.referrerPolicy"s, ""s));
	if (!referrerPolicy.empty())
	{
		servlet += "\nresponse.set('Referrer-Policy', '" + escape(referrerPolicy) + "');";
	}

	servlet += "\n";
	servlet += page.handler().str();
	servlet += "\nresponse.send();\n";
	servlet += "}\n";
}


} } } } // namespace Poco::OSP::JS::Web
