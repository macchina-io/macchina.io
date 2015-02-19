//
// Utility.cpp
//
// $Id: //my-devices.net/Main/reflector/src/Utility.cpp#14 $
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Utility.h"
#include "Poco/Format.h"


namespace IoT {
namespace Web {
namespace Launcher {


bool Utility::isAuthenticated(Poco::OSP::Web::WebSession::Ptr pSession, Poco::Net::HTTPServerResponse& response)
{
	if (!pSession || !pSession->has("username"))
	{
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
		response.setContentLength(0);
		response.setChunkedTransferEncoding(false);
		response.send();
		return false;
	}
	return true;
}


std::string Utility::jsonize(const std::string& str)
{
	std::string result("\"");
	std::string::const_iterator it(str.begin());
	std::string::const_iterator end(str.end());
	for (; it != end; ++it)
	{
		switch (*it)
		{
		case '"':
			result += "\\\"";
			break;
		case '\\':
			result += "\\\\";
			break;
		case '\b':
			result += "\\b";
			break;
		case '\f':
			result += "\\f";
			break;
		case '\n':
			result += "\\n";
			break;
		case '\r':
			result += "\\r";
			break;
		case '\t':
			result += "\\t";
			break;
		default:
			result += *it;
			break;
		}
	}
	result += "\"";
	return result;
}


std::string Utility::htmlize(const std::string& str)
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


std::string Utility::text(Poco::OSP::BundleContext::Ptr pContext, const std::string& id)
{
	std::string key("text.");
	key += id;
	return pContext->thisBundle()->properties().getString(key, key);
}


std::string Utility::text(Poco::OSP::BundleContext::Ptr pContext, const std::string& id, const Poco::Any& arg1)
{
	std::string key("text.");
	key += id;
	return Poco::format(pContext->thisBundle()->properties().getString(key, key), arg1);
}


std::string Utility::text(Poco::OSP::BundleContext::Ptr pContext, const std::string& id, const Poco::Any& arg1, const Poco::Any& arg2)
{
	std::string key("text.");
	key += id;
	return Poco::format(pContext->thisBundle()->properties().getString(key, key), arg1, arg2);
}


std::string Utility::text(Poco::OSP::BundleContext::Ptr pContext, const std::string& id, const Poco::Any& arg1, const Poco::Any& arg2, const Poco::Any& arg3)
{
	std::string key("text.");
	key += id;
	return Poco::format(pContext->thisBundle()->properties().getString(key, key), arg1, arg2, arg3);
}


std::string Utility::text(Poco::OSP::BundleContext::Ptr pContext, const std::string& id, const Poco::Any& arg1, const Poco::Any& arg2, const Poco::Any& arg3, const Poco::Any& arg4)
{
	std::string key("text.");
	key += id;
	return Poco::format(pContext->thisBundle()->properties().getString(key, key), arg1, arg2, arg3, arg4);
}


} } } // namespace IoT::Web::Launcher
