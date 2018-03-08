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
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/Timespan.h"
#include "Poco/Delegate.h"
#include "Poco/Exception.h"


using Poco::Delegate;


namespace Poco {
namespace OSP {
namespace Web {


const std::string WebSession::CSRF_TOKEN("#csrfToken");


WebSession::WebSession(const std::string& id, int timeoutSeconds, const Poco::Net::IPAddress& clientAddress, BundleContext::Ptr pContext):
	_id(id),
	_timeout(timeoutSeconds, 0),
	_pContext(pContext),
	_clientAddress(clientAddress)
{
	_pContext->events().bundleStopping += Delegate<WebSession, BundleEvent>(this, &WebSession::onBundleStopping);
	access();
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
}


void WebSession::erase(const std::string& key)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_attrs.erase(key);
}


void WebSession::clear()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_attrs.clear();
}


void WebSession::access()
{
	_expiration.update();
	_expiration += _timeout.totalMicroseconds();
}


void WebSession::onBundleStopping(const void* pSender, BundleEvent& ev)
{
	if (ev.bundle() == _pContext->thisBundle())
	{
		clear();
	}
}


} } } // namespace Poco::OSP
