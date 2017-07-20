//
// Utility.cpp
//
// $Id: //my-devices.net/Main/reflector/src/Utility.cpp#14 $
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Utility.h"


namespace IoT {
namespace Web {
namespace Dataflow {


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


} } } // namespace IoT::Web::Dataflow
