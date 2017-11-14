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
// SPDX-License-Identifier: Apache-2.0
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


namespace Poco {
namespace OSP {
namespace Web {


const std::string WebSessionManager::COOKIE_NAME("osp.web.session");
const std::string WebSessionManager::SERVICE_NAME("osp.web.session");


WebSessionManager::WebSessionManager():
	_serial(0),
	_cookiePersistence(COOKIE_PERSISTENT)
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


const std::type_info& WebSessionManager::type() const
{
	return typeid(WebSessionManager);
}


bool WebSessionManager::isA(const std::type_info& otherType) const
{
	std::string name(typeid(WebSessionManager).name());
	return name == otherType.name() || WebSessionService<Poco::Net::HTTPServerRequest>::isA(otherType);
}


WebSession::Ptr WebSessionManager::find(const std::string& appName, const Poco::Net::HTTPServerRequest& request)
{
	FastMutex::ScopedLock lock(_mutex);
	
	WebSession::Ptr pSession(_cache.get(getId(appName, request)));
	if (pSession)
	{
		if (pSession->clientAddress() == request.clientAddress().host())
		{
			pSession->access();
			_cache.add(pSession->id(), pSession);
			addCookie(appName, request, pSession);
		}
		else 
		{
			// possible attack: same session ID from different host - invalidate session
			_cache.remove(pSession->id());
			return 0;
		}
	}
	return pSession;
}


WebSession::Ptr WebSessionManager::get(const std::string& appName, const Poco::Net::HTTPServerRequest& request, int expireSeconds, BundleContext::Ptr pContext)
{
	WebSession::Ptr pSession = find(appName, request);
	if (!pSession)
		pSession = create(appName, request, expireSeconds, pContext);
	return pSession;
}


WebSession::Ptr WebSessionManager::create(const std::string& appName, const Poco::Net::HTTPServerRequest& request, int expireSeconds, BundleContext::Ptr pContext)
{
	FastMutex::ScopedLock lock(_mutex);
	WebSession::Ptr pSession(new WebSession(createSessionId(request), expireSeconds, request.clientAddress().host(), pContext));
	_cache.add(pSession->id(), pSession);
	addCookie(appName, request, pSession);
	pSession->setValue(WebSession::CSRF_TOKEN, createSessionId(request));
	return pSession;
}


void WebSessionManager::remove(WebSession::Ptr pSession)
{
	FastMutex::ScopedLock lock(_mutex);
	_cache.remove(pSession->id());
}


std::string WebSessionManager::getId(const std::string& appName, const Poco::Net::HTTPServerRequest& request)
{
	std::string id;
	std::string name(cookieName(appName));
	NameValueCollection cookies;
	request.getCookies(cookies);
	NameValueCollection::ConstIterator it = cookies.find(name);
	if (it != cookies.end())
		id = it->second;
	
	return id;
}


void WebSessionManager::addCookie(const std::string& appName, const Poco::Net::HTTPServerRequest& request, WebSession::Ptr pSession)
{
	Poco::Net::HTTPCookie cookie(cookieName(appName), pSession->id());
	if (_cookiePersistence == COOKIE_PERSISTENT)
	{
		cookie.setMaxAge(pSession->timeout());
	}
	cookie.setPath(cookiePath(appName));
	cookie.setDomain(cookieDomain(appName));
	cookie.setHttpOnly();
	request.response().addCookie(cookie);
}


std::string WebSessionManager::createSessionId(const Poco::Net::HTTPServerRequest& request)
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
