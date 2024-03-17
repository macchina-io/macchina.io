//
// WebSessionManager.cpp
//
// Library: OSP/Web
// Package: Web
// Module:  WebSessionManager
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/StringTokenizer.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SHA1Engine.h"
#include "Poco/RandomStream.h"


using Poco::Net::NameValueCollection;
using Poco::FastMutex;
using Poco::NumberFormatter;
using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace Web {


const std::string WebSessionManager::COOKIE_NAME("osp.web.session");
const std::string WebSessionManager::SERVICE_NAME("osp.web.session");


WebSessionManager::WebSessionManager(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext),
	_serial(0),
	_cookiePersistence(COOKIE_PERSISTENT),
	_cookieSecure(false),
	_verifyAddress(true),
	_cookieSameSite(Poco::Net::HTTPCookie::SAME_SITE_NOT_SPECIFIED),
	_logger(Poco::Logger::get("osp.web.session"))
{
}


WebSessionManager::~WebSessionManager()
{
}


void WebSessionManager::setDefaultDomain(const std::string& domain)
{
	_defaultDomain = domain;
}


const std::string& WebSessionManager::getDefaultDomain() const
{
	return _defaultDomain;
}


void WebSessionManager::setDefaultPath(const std::string& path)
{
	_defaultPath = path;
}


const std::string& WebSessionManager::getDefaultPath() const
{
	return _defaultPath;
}


void WebSessionManager::setCookiePersistence(WebSessionManager::CookiePersistence persistence)
{
	_cookiePersistence = persistence;
}


WebSessionManager::CookiePersistence WebSessionManager::getCookiePersistence() const
{
	return _cookiePersistence;
}


void WebSessionManager::setCookieSameSite(Poco::Net::HTTPCookie::SameSite sameSite)
{
	_cookieSameSite = sameSite;
}


Poco::Net::HTTPCookie::SameSite WebSessionManager::setCookieSameSite() const
{
	return _cookieSameSite;
}


void WebSessionManager::setCookieSecure(bool secure)
{
	_cookieSecure = secure;
}


bool WebSessionManager::isCookieSecure() const
{
	return _cookieSecure;
}


void WebSessionManager::setVerifyAddress(bool verify)
{
	_verifyAddress = verify;
}


bool WebSessionManager::isAddressVerified() const
{
	return _verifyAddress;
}


void WebSessionManager::setCSRFCookie(const std::string& name)
{
	_csrfCookie = name;
}


const std::string& WebSessionManager::getCSRFCookie() const
{
	return _csrfCookie;
}


void WebSessionManager::setSessionStore(WebSessionStore::Ptr pWebSessionStore)
{
	FastMutex::ScopedLock lock(_mutex);

	_pStore = pWebSessionStore;
}


WebSessionStore::Ptr WebSessionManager::getSessionStore() const
{
	FastMutex::ScopedLock lock(_mutex);

	return _pStore;
}


const std::type_info& WebSessionManager::type() const
{
	return typeid(WebSessionManager);
}


bool WebSessionManager::isA(const std::type_info& otherType) const
{
	std::string name(typeid(WebSessionManager).name());
	return name == otherType.name() || WebSessionService<Poco::Net::HTTPServerRequest>::isA(otherType);
}


WebSession::Ptr WebSessionManager::findById(const std::string& sessionId)
{
	FastMutex::ScopedLock lock(_mutex);

	return findByIdImpl(sessionId, _pContext);
}


std::size_t WebSessionManager::countSessions()
{
	FastMutex::ScopedLock lock(_mutex);

	if (_pStore)
	{
		return _pStore->countSessions();
	}
	else
	{
		return _cache.size();
	}
}


WebSession::Ptr WebSessionManager::find(const std::string& appName, const Poco::Net::HTTPServerRequest& request)
{
	FastMutex::ScopedLock lock(_mutex);

	return findImpl(appName, request, _pContext);
}


WebSession::Ptr WebSessionManager::get(const std::string& appName, const Poco::Net::HTTPServerRequest& request, int expireSeconds, BundleContext::Ptr pContext)
{
	FastMutex::ScopedLock lock(_mutex);

	WebSession::Ptr pSession = findImpl(appName, request, pContext);
	if (!pSession)
	{
		_logger.debug("No existing session, creating new one."s);
		pSession = createImpl(appName, request, expireSeconds, pContext);
	}
	return pSession;
}


WebSession::Ptr WebSessionManager::create(const std::string& appName, const Poco::Net::HTTPServerRequest& request, int expireSeconds, BundleContext::Ptr pContext)
{
	FastMutex::ScopedLock lock(_mutex);

	return createImpl(appName, request, expireSeconds, pContext);
}


void WebSessionManager::remove(WebSession::Ptr pSession)
{
	FastMutex::ScopedLock lock(_mutex);

	removeImpl(pSession);
}


void WebSessionManager::removeForUser(const std::string& username)
{
	FastMutex::ScopedLock lock(_mutex);

	std::vector<std::string> sessionsToRemove;

	if (_pStore)
	{
		sessionsToRemove = _pStore->sessionsByValue("username"s, username);
	}
	else
	{
		_cache.forEach(
			[&sessionsToRemove, &username](const std::string& id, const WebSession& session)
			{
				auto it = session.find("username"s);
				if (it != session.end())
				{
					try
					{
						if (Poco::AnyCast<std::string>(it->second) == username)
						{
							sessionsToRemove.push_back(id);
						}
					}
					catch (...)
					{
					}
				}
			}
		);
	}

	for (const auto& id: sessionsToRemove)
	{
		removeImpl(id);
	}
}


WebSession::Ptr WebSessionManager::findImpl(const std::string& appName, const Poco::Net::HTTPServerRequest& request, BundleContext::Ptr pContext)
{
	WebSession::Ptr pSession;
	std::string sessionId(getId(appName, request));
	if (!sessionId.empty())
	{
		if (_logger.debug())
		{
			_logger.debug("Looking up session %s..."s, sessionId);
		}
		pSession = findByIdImpl(sessionId, pContext);
	}
	else
	{
		_logger.debug("No session cookie found in request."s);
	}
	if (pSession)
	{
		if (_logger.debug())
		{
			_logger.debug("Existing session %s found."s, sessionId);
		}
		if (!_verifyAddress || pSession->clientAddress() == request.clientAddress().host())
		{
			pSession->access();
			_cache.add(pSession->id(), pSession);
			addSessionCookie(appName, request, pSession);
			addCSRFCookie(appName, request, pSession);
		}
		else
		{
			_logger.notice("Client address mismatch for session %s (known address: %s, request address: %s). Session will be removed."s,
				sessionId, pSession->clientAddress().toString(), request.clientAddress().host().toString());

			// possible attack: same session ID from different host - invalidate session
			removeImpl(pSession);
			return 0;
		}
	}
	return pSession;
}


WebSession::Ptr WebSessionManager::findByIdImpl(const std::string& sessionId, BundleContext::Ptr pContext)
{
	WebSession::Ptr pSession = _cache.get(sessionId);
	if (_logger.debug() && pSession)
	{
		_logger.debug("Session %s found in cache."s, sessionId);
	}
	if (_pStore)
	{
		if (_logger.debug())
		{
			_logger.debug("Looking up session %s in session store..."s, sessionId);
		}
		if (pSession)
		{
			std::pair<WebSession::Ptr, bool> result = _pStore->loadSession(pContext, sessionId, pSession->version());
			if (result.first && result.second)
				pSession = result.first;
			else if (!result.second)
				pSession.reset();
		}
		else
		{
			std::pair<WebSession::Ptr, bool> result = _pStore->loadSession(pContext, sessionId);
			if (result.second) pSession = result.first;
		}
	}
	return pSession;
}


WebSession::Ptr WebSessionManager::createImpl(const std::string& appName, const Poco::Net::HTTPServerRequest& request, int expireSeconds, BundleContext::Ptr pContext)
{
	WebSession::Ptr pSession(new WebSession(createToken(request), createToken(request), 1, expireSeconds, request.clientAddress().host(), _pStore, pContext));
	_cache.add(pSession->id(), pSession);
	addSessionCookie(appName, request, pSession);
	addCSRFCookie(appName, request, pSession);
	if (_pStore)
	{
		_pStore->saveSession(pSession);
	}
	if (_logger.debug())
	{
		_logger.debug("New session %s created."s, pSession->id());
	}
	return pSession;
}


void WebSessionManager::removeImpl(WebSession::Ptr pSession)
{
	removeImpl(pSession->id());
}


void WebSessionManager::removeImpl(const std::string& id)
{
	if (_logger.debug())
	{
		_logger.debug("Removing session %s."s, id);
	}
	_cache.remove(id);
	if (_pStore)
	{
		_pStore->expireSession(id, 0);
	}
}


std::string WebSessionManager::getId(const std::string& appName, const Poco::Net::HTTPServerRequest& request)
{
	std::string id;
	std::string name(cookieName(appName));
	NameValueCollection cookies;
	request.getCookies(cookies);
	NameValueCollection::ConstIterator it = cookies.find(name);
	if (it != cookies.end())
	{
		id = it->second;
	}
	return id;
}


void WebSessionManager::addSessionCookie(const std::string& appName, const Poco::Net::HTTPServerRequest& request, WebSession::Ptr pSession)
{
	Poco::Net::HTTPCookie cookie(cookieName(appName), pSession->id());
	if (_cookiePersistence == COOKIE_PERSISTENT)
	{
		cookie.setMaxAge(pSession->timeout());
	}
	cookie.setPath(cookiePath(appName));
	cookie.setDomain(cookieDomain(appName));
	cookie.setHttpOnly();
	cookie.setSecure(_cookieSecure);
	cookie.setSameSite(_cookieSameSite);
	request.response().addCookie(cookie);
}


void WebSessionManager::addCSRFCookie(const std::string& appName, const Poco::Net::HTTPServerRequest& request, WebSession::Ptr pSession)
{
	if (!_csrfCookie.empty())
	{
		Poco::Net::HTTPCookie csrfCookie(_csrfCookie, pSession->csrfToken());
		if (_cookiePersistence == COOKIE_PERSISTENT)
		{
			csrfCookie.setMaxAge(pSession->timeout());
		}
		csrfCookie.setPath(cookiePath(appName));
		csrfCookie.setSecure(_cookieSecure);
		csrfCookie.setSameSite(Poco::Net::HTTPCookie::SAME_SITE_STRICT);
		request.response().addCookie(csrfCookie);
	}
}


std::string WebSessionManager::createToken(const Poco::Net::HTTPServerRequest& request)
{
	++_serial;

	Poco::SHA1Engine sha1;
	sha1.update(&_serial, sizeof(_serial));
	Poco::Timestamp::TimeVal tv = Poco::Timestamp().epochMicroseconds();
	sha1.update(&tv, sizeof(tv));
	Poco::RandomInputStream ris;
	for (int i = 0; i < 32; i++)
	{
		char c = ris.get();
		sha1.update(c);
	}
	sha1.update(request.clientAddress().toString());

	std::string result = Poco::DigestEngine::digestToHex(sha1.digest());
	return result;
}


std::string WebSessionManager::cookieName(const std::string& appName)
{
	std::string cookieName(COOKIE_NAME);
	if (!appName.empty())
	{
		std::string::size_type pos = appName.find('@');
		if (pos == std::string::npos) pos = appName.find('/');
		if (pos == std::string::npos) pos = appName.size();
		cookieName.append(".");
		cookieName.append(appName, 0, pos);
	}
	return cookieName;
}


std::string WebSessionManager::cookieDomain(const std::string& appName)
{
	std::string result;
	std::string::size_type pos = appName.find('@');
	if (pos != std::string::npos)
	{
		pos++;
		while (pos < appName.size() && appName[pos] != '/') result += appName[pos++];
	}
	return result.empty() ? _defaultDomain : result;
}


std::string WebSessionManager::cookiePath(const std::string& appName)
{
	std::string result("/");
	std::string::size_type pos = appName.find('/');
	if (pos != std::string::npos)
	{
		result.assign(appName, pos, appName.size() - pos);
	}
	return result.empty() ? _defaultPath : result;
}


} } } // namespace Poco::OSP::Web
