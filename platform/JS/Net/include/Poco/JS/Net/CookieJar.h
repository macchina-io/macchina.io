//
// CookieJar.h
//
// Library: JS/Net
// Package: Wrappers
// Module:  CookieJar
//
// Definition of the CookieJar class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Net_CookieJar_INCLUDED
#define JS_Net_CookieJar_INCLUDED


#include "Poco/JS/Net/Net.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPCookie.h"
#include "Poco/Timestamp.h"
#include <map>


namespace Poco {
namespace JS {
namespace Net {


class JSNet_API CookieJar
	/// A CookieJar object stores cookies set by a HTTP server.
	///
	/// This class is used sharing session cookies among
	/// multiple HTTP requests to the same server.
{
public:
	CookieJar();
		/// Creates an empty CookieJar.

	~CookieJar();
		/// Destroys the CookieJar.

	void addCookies(Poco::Net::HTTPRequest& request);
		/// Adds the stored cookies to the given request object.

	void updateCookies(const Poco::Net::HTTPResponse& response);
		/// Updates the stored cookies with the cookies from
		/// the given response object.

private:
	struct CookieInfo
	{
		Poco::Net::HTTPCookie cookie;
		Poco::Timestamp expireTime;
	};
	typedef std::map<std::string, CookieInfo> CookieMap;

	CookieMap _cookies;
};


} } } // namespace Poco::JS::Net


#endif // JS_Net_CookieJar_INCLUDED
