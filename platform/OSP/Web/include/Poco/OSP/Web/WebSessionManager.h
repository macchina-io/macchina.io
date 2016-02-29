//
// WebSessionManager.h
//
// $Id: //poco/1.7/OSP/Web/include/Poco/OSP/Web/WebSessionManager.h#1 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebSessionManager
//
// Definition of the WebSessionManager class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_Web_WebSessionManager_INCLUDED
#define OSP_Web_WebSessionManager_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionService.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/UniqueExpireCache.h"
#include "Poco/Mutex.h"


namespace Poco {
namespace OSP {
namespace Web {


class OSPWeb_API WebSessionManager: public WebSessionService<Poco::Net::HTTPServerRequest>
	/// A WebSessionManager manages HTTP sessions using cookies.
	///
	/// The SessionManager is registered under the service name
	/// "osp.web.session".
	///
	/// Note that the application name (appName) specified in get() and create()
	/// can contain a domain name, separated by '@'. If a domain name is given,
	/// it is used to set the domain for the session cookie. Similarly, a path
	/// can be given, beginning with a slash.
	///
	/// For example, if the appName is sample@.appinf.com, then the browser
	/// will send the session cookie to all hosts with names in the appinf.com
	/// domain. If a domain is not given, the session cookie will only be available
	/// to the host that has originally set it.
{
public:
	typedef Poco::AutoPtr<WebSessionManager> Ptr;

	enum CookiePersistence
	{
		COOKIE_TRANSIENT  = 1, /// Session cookies are transient (go away when browser is closed).
		COOKIE_PERSISTENT = 2  /// Session cookies are persistent (kept in browser until they expire).
	};

	WebSessionManager();
		/// Creates the SessionManager.

	~WebSessionManager();
		/// Destroys the SessionManager.
		
	void setDefaultDomain(const std::string& domain);
		/// Sets the default domain for the session cookie.
		
	const std::string& getDefaultDomain() const;
		/// Returns the default domain for the session cookie.
		
	void setDefaultPath(const std::string& path);
		/// Sets the default path for the session cookie.
		
	const std::string& getDefaultPath() const;
		/// Returns the default path for the session cookie.
		
	void setCookiePersistence(CookiePersistence persistence);
		/// Sets the cookie persistence, which controls whether
		/// session cookies are transient (go away when the
		/// browser is closed) or persistent (default).
		
	CookiePersistence getCookiePersistence() const;
		/// Returns the cookie persistence.

	// WebSessionService
	WebSession::Ptr find(const std::string& appName, const Poco::Net::HTTPServerRequest& request);
	WebSession::Ptr get(const std::string& appName, const Poco::Net::HTTPServerRequest& request, int expireSeconds, BundleContext::Ptr pContext);
	WebSession::Ptr create(const std::string& appName, const Poco::Net::HTTPServerRequest& request, int expireSeconds, BundleContext::Ptr pContext);
	void remove(WebSession::Ptr ptr);

	// Service
	virtual const std::type_info& type() const;
	virtual bool isA(const std::type_info& otherType) const;

	static const std::string SERVICE_NAME;

protected:
	std::string getId(const std::string& appName, const Poco::Net::HTTPServerRequest& request);
	void addCookie(const std::string& appName, const Poco::Net::HTTPServerRequest& request, WebSession::Ptr ptrSes);
	std::string createSessionId(const Poco::Net::HTTPServerRequest& request);
	std::string cookieName(const std::string& appName);
	std::string cookieDomain(const std::string& appName);
	std::string cookiePath(const std::string& appName);

private:
	static const std::string COOKIE_NAME;

	Poco::FastMutex _mutex;
	Poco::UInt32 _serial;
	Poco::UniqueExpireCache<std::string, WebSession> _cache;
	std::string _defaultDomain;
	std::string _defaultPath;
	CookiePersistence _cookiePersistence;
};


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebSessionManager_INCLUDED
