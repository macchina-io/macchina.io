//
// URIUtility.cpp
//
// $Id: //poco/1.4/RemotingNG/src/URIUtility.cpp#2 $
//
// Library: RemotingNG
// Package: RemotingNG
// Module:  URIUtility
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/StringTokenizer.h"
#include "Poco/URI.h"
#include "Poco/NumberFormatter.h"


namespace Poco {
namespace RemotingNG {


std::string URIUtility::createURIPath(const Identifiable::ObjectId& oid, const Identifiable::TypeId& tid, const std::string& protocol)
{
	poco_assert_dbg(!oid.empty());
	poco_assert_dbg(!tid.empty());
	poco_assert_dbg(!protocol.empty());
	std::string result("/");
	result += protocol;
	result += '/';
	result += tid;
	result += '/';
	result += oid;
	return result;
}


std::string URIUtility::createURIAuthority(const std::string& host, Poco::UInt16 port)
{
	std::string auth;
	if (host.find(':') != std::string::npos)
	{
		auth += '[';
		auth += host;
		auth += ']';
	}
	else auth += host;
	auth += ':';
	auth += Poco::NumberFormatter::format(port);
	return auth;
}


void URIUtility::parseURIPath(const std::string& path, Identifiable::ObjectId& oid, Identifiable::TypeId& tid, std::string& protocol)
{
	// note: we can get full URIs here
	Poco::StringTokenizer tok(path, "/"); // no trim, no ignore empty!

	if (tok.count() >= 3)
	{
		Poco::StringTokenizer::Iterator it = tok.end();
		--it;
		oid = *it;
		--it;
		tid = *it;
		--it;
		protocol = *it;
	}
	else throw Poco::SyntaxException("malformed RemotingNG URI path", path);
}


} } // namespace Poco::RemotingNG
