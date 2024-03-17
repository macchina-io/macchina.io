//
// WebSessionManager.h
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
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_Web_WebSessionManager_INCLUDED
#define OSP_Web_WebSessionManager_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionService.h"
#include "Poco/OSP/Web/WebSessionStore.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPCookie.h"
#include "Poco/UniqueExpireCache.h"
#include "Poco/Logger.h"
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
	using Ptr = Poco::AutoPtr<WebSessionManager>;

	enum CookiePersistence
	{
		COOKIE_TRANSIENT  = 1, /// Session cookies are transient (go away when browser is closed).
		COOKIE_PERSISTENT = 2  /// Session cookies are persistent (kept in browser until they expire).
	};

	explicit WebSessionManager(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the SessionManager without a WebSessionStore.

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
		/// session and CSRF cookies are transient (go away when the
		/// browser is closed) or persistent (default).

	CookiePersistence getCookiePersistence() const;
		/// Returns the cookie persistence for the session
		/// and CSRF cookies.

	void setCookieSecure(bool secure);
		/// Sets the secure attribute of the session cookie.
		///
		/// If set to true, the browser will only send the
		/// cookie over HTTPS connections.

	bool isCookieSecure() const;
		/// Returns true if the session cookie has the secure
		/// attribute set, otherwise false.

	void setCookieSameSite(Poco::Net::HTTPCookie::SameSite sameSite);
		/// Sets the SameSite attribute for the session cookie.
		///
		/// The default is Poco::Net::HTTPCookie::SAME_SITE_NOT_SPECIFIED.

	Poco::Net::HTTPCookie::SameSite setCookieSameSite() const;
		/// Returns the SameSite attribute for the session cookie.

	void setVerifyAddress(bool verify);
		/// Enable or disable verification of client address
		/// against the address stored in the session.

	bool isAddressVerified() const;
		/// Returns true if the client IP address is verified
		/// against the address stored in the session.

	void setCSRFCookie(const std::string& name);
		/// Sets the name of the CSRF/XSRF cookie.
		///
		/// If set, the CSRF token of the session will be stored in
		/// the cookie with the given name. This cookie is accessible
		/// from JavaScript and can be used to authenticate scripted
		/// HTTP requests (together with the session cookie).

	const std::string& getCSRFCookie() const;
		/// Returns the name of the CSRF cookie, if set, otherwise
		/// an empty string.

	void setSessionStore(WebSessionStore::Ptr pWebSessionStore);
		/// Sets the WebSessionStore.

	WebSessionStore::Ptr getSessionStore() const;
		/// Returns the WebSessionStore.

	WebSession::Ptr findById(const std::string& sessionId);
		/// Returns the session with the given ID, or null if it does not exist.

	std::size_t countSessions();
		/// Returns the number of active sessions.

	// WebSessionService
	WebSession::Ptr find(const std::string& appName, const Poco::Net::HTTPServerRequest& request);
	WebSession::Ptr get(const std::string& appName, const Poco::Net::HTTPServerRequest& request, int expireSeconds, BundleContext::Ptr pContext);
	WebSession::Ptr create(const std::string& appName, const Poco::Net::HTTPServerRequest& request, int expireSeconds, BundleContext::Ptr pContext);
	void remove(WebSession::Ptr ptr);
	void removeForUser(const std::string& username);

	// Service
	virtual const std::type_info& type() const;
	virtual bool isA(const std::type_info& otherType) const;

	static const std::string SERVICE_NAME;

protected:
	WebSession::Ptr findImpl(const std::string& appName, const Poco::Net::HTTPServerRequest& request, BundleContext::Ptr pContext);
	WebSession::Ptr findByIdImpl(const std::string& sessionId, BundleContext::Ptr pContext);
	WebSession::Ptr createImpl(const std::string& appName, const Poco::Net::HTTPServerRequest& request, int expireSeconds, BundleContext::Ptr pContext);
	void removeImpl(WebSession::Ptr pSession);
	void removeImpl(const std::string& id);
	std::string getId(const std::string& appName, const Poco::Net::HTTPServerRequest& request);
	void addSessionCookie(const std::string& appName, const Poco::Net::HTTPServerRequest& request, WebSession::Ptr ptrSes);
	void addCSRFCookie(const std::string& appName, const Poco::Net::HTTPServerRequest& request, WebSession::Ptr ptrSes);
	std::string createToken(const Poco::Net::HTTPServerRequest& request);
	std::string cookieName(const std::string& appName);
	std::string cookieDomain(const std::string& appName);
	std::string cookiePath(const std::string& appName);

private:
	static const std::string COOKIE_NAME;

	mutable Poco::FastMutex _mutex;
	Poco::OSP::BundleContext::Ptr _pContext;
	WebSessionStore::Ptr _pStore;
	Poco::UInt32 _serial;
	Poco::UniqueExpireCache<std::string, WebSession> _cache;
	std::string _defaultDomain;
	std::string _defaultPath;
	std::string _csrfCookie;
	CookiePersistence _cookiePersistence;
	bool _cookieSecure;
	bool _verifyAddress;
	Poco::Net::HTTPCookie::SameSite _cookieSameSite;
	Poco::Logger& _logger;
};


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebSessionManager_INCLUDED
