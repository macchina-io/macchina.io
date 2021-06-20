//
// WebSession.cpp
//
// Library: OSP/Web
// Package: Web
// Module:  WebSession
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionStore.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/Timespan.h"
#include "Poco/Delegate.h"
#include "Poco/Exception.h"


using Poco::Delegate;


namespace Poco {
namespace OSP {
namespace Web {


const std::string WebSession::CSRF_TOKEN("#csrfToken");


WebSession::WebSession(const std::string& id, const std::string& csrfToken, Poco::Int64 version, int timeoutSeconds, const Poco::Net::IPAddress& clientAddress, Poco::AutoPtr<WebSessionStore> pStore, BundleContext::Ptr pContext):
	_id(id),
	_version(version),
	_timeout(timeoutSeconds, 0),
	_pContext(pContext),
	_clientAddress(clientAddress),
	_pStore(pStore)
{
	_pContext->events().bundleStopping += Delegate<WebSession, BundleEvent>(this, &WebSession::onBundleStopping);
	accessImpl();
	_attrs[CSRF_TOKEN] = csrfToken;
}


WebSession::WebSession(const std::string& id, Poco::Int64 version, int timeoutSeconds, const Poco::Net::IPAddress& clientAddress, Poco::AutoPtr<WebSessionStore> pStore, BundleContext::Ptr pContext, Poco::Timestamp created, const Attributes& attrs):
	_id(id),
	_version(version),
	_timeout(timeoutSeconds, 0),
	_pContext(pContext),
	_created(created),
	_clientAddress(clientAddress),
	_attrs(attrs),
	_pStore(pStore)
{
	_pContext->events().bundleStopping += Delegate<WebSession, BundleEvent>(this, &WebSession::onBundleStopping);
	accessImpl();
}


WebSession::~WebSession()
{
	try
	{
		_pContext->events().bundleStopping -= Delegate<WebSession, BundleEvent>(this, &WebSession::onBundleStopping);
		const WebSession* pThis(this);
		sessionEnds.notify(this, pThis);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


bool WebSession::has(const std::string& key) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Attributes::const_iterator it = _attrs.find(key);
	return it != _attrs.end();
}


const Poco::Any& WebSession::get(const std::string& key) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Attributes::const_iterator it = _attrs.find(key);
	if (it != _attrs.end())
		return it->second;
	else
		throw Poco::NotFoundException(key);
}


void WebSession::set(const std::string& key, const Poco::Any& value)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_attrs[key] = value;

	if (_pStore)
	{
		updateVersion(_pStore->saveValue(_id, key, value));
	}
}


void WebSession::erase(const std::string& key)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_attrs.erase(key);

	if (_pStore)
	{
		updateVersion(_pStore->removeValue(_id, key));
	}
}


void WebSession::clear()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::Any token;
	auto it = _attrs.find(CSRF_TOKEN);
	if (it != _attrs.end())
	{
		token = it->second;
	}

	clearImpl();

	if (!token.empty())
	{
		_attrs[CSRF_TOKEN] = token;
	}
}


void WebSession::clearImpl()
{
	_attrs.clear();

	if (_pStore)
	{
		updateVersion(_pStore->clearValues(_id));
	}
}


void WebSession::access()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	accessImpl();

	if (_pStore)
	{
		_pStore->expireSession(_id, _timeout);
	}
}


void WebSession::accessImpl()
{
	_expiration.update();
	_expiration += _timeout.totalMicroseconds();
}


void WebSession::updateVersion(Poco::Int64 version)
{
	if (version == _version + 1)
	{
		_version = version;
	}
}


void WebSession::onBundleStopping(const void* pSender, BundleEvent& ev)
{
	if (ev.bundle() == _pContext->thisBundle())
	{
		clearImpl();
	}
}


} } } // namespace Poco::OSP
