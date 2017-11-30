//
// Utility.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Utility.h"


namespace IoT {
namespace Web {
namespace Settings {


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


void Utility::copyProperties(const Poco::Util::AbstractConfiguration& source, Poco::Util::AbstractConfiguration& target, const std::set<std::string>& excludeSet, const std::string& root)
{
	Poco::Util::AbstractConfiguration::Keys keys;
	source.keys(root, keys);

	if (keys.empty() && source.hasProperty(root))
	{
		target.setString(root, source.getRawString(root));
	}
	else
	{
		for (Poco::Util::AbstractConfiguration::Keys::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string fullKey = root;
			if (!fullKey.empty()) fullKey += '.';
			fullKey.append(*it);
			if (excludeSet.find(fullKey) == excludeSet.end())
			{
				copyProperties(source, target, excludeSet, fullKey);
			}
		}
	}
}


void Utility::copyDeltaProperties(const Poco::Util::AbstractConfiguration& ref, const Poco::Util::AbstractConfiguration& source, Poco::Util::AbstractConfiguration& target, const std::set<std::string>& excludeSet, const std::string& root)
{
	Poco::Util::AbstractConfiguration::Keys keys;
	source.keys(root, keys);

	if (keys.empty() && source.hasProperty(root))
	{
		if ((ref.hasProperty(root) && ref.getRawString(root) != source.getRawString(root)) || !ref.hasProperty(root))
		{
			target.setString(root, source.getRawString(root));
		}
	}
	else
	{
		for (Poco::Util::AbstractConfiguration::Keys::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string fullKey = root;
			if (!fullKey.empty()) fullKey += '.';
			fullKey.append(*it);
			if (excludeSet.find(fullKey) == excludeSet.end())
			{
				copyDeltaProperties(ref, source, target, excludeSet, fullKey);
			}
		}
	}
}


} } } // namespace IoT::Web::Settings
