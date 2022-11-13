//
// CookieJar.cpp
//
// Library: JS/Net
// Package: Wrappers
// Module:  CookieJar
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Net/CookieJar.h"


namespace Poco {
namespace JS {
namespace Net {


CookieJar::CookieJar()
{
}


CookieJar::~CookieJar()
{
}


void CookieJar::addCookies(Poco::Net::HTTPRequest& request)
{
	Poco::Timestamp now;
	Poco::Net::NameValueCollection cookies;
	for (CookieMap::const_iterator it = _cookies.begin(); it != _cookies.end(); ++it)
	{
		if (it->second.expireTime == 0 || now <= it->second.expireTime)
		{
			cookies.add(it->second.cookie.getName(), it->second.cookie.getValue());
		}
	}
	if (!cookies.empty())
	{
		request.setCookies(cookies);
	}
}


void CookieJar::updateCookies(const Poco::Net::HTTPResponse& response)
{
	std::vector<Poco::Net::HTTPCookie> cookies;
	response.getCookies(cookies);
	Poco::Timestamp now;
	for (std::vector<Poco::Net::HTTPCookie>::const_iterator it = cookies.begin(); it != cookies.end(); ++it)
	{
		if (it->getMaxAge() == -1)
		{
			CookieInfo ci;
			ci.cookie = *it;
			ci.expireTime = 0;
			_cookies[it->getName()] = ci;
		}
		else if (it->getMaxAge() == 0)
		{
			_cookies.erase(it->getName());
		}
		else
		{
			CookieInfo ci;
			ci.cookie = *it;
			ci.expireTime += it->getMaxAge()*Poco::Timestamp::resolution();
			_cookies[it->getName()] = ci;
		}
	}
}


} } } // namespace Poco::JS::Net
