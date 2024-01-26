//
// ServiceListener.cpp
//
// Library: OSP
// Package: Service
// Module:  ServiceListener
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/ServiceListener.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceEvent.h"
#include "Poco/OSP/QLExpr.h"
#include "Poco/OSP/QLParser.h"
#include "Poco/Delegate.h"


namespace Poco {
namespace OSP {


ServiceListener::~ServiceListener()
{
	_registry.serviceRegistered   -= Poco::delegate(this, &ServiceListener::onServiceRegistered);
	_registry.serviceUnregistered -= Poco::delegate(this, &ServiceListener::onServiceUnregistered);
}


void ServiceListener::init(const std::string& query)
{
	QLParser parser(query);
	_pExpr = parser.parse();

	_registry.serviceRegistered   += Poco::delegate(this, &ServiceListener::onServiceRegistered);
	_registry.serviceUnregistered += Poco::delegate(this, &ServiceListener::onServiceUnregistered);

	std::vector<ServiceRef::Ptr> results;
	if (_registry.find(*_pExpr, results))
	{
		for (std::vector<ServiceRef::Ptr>::const_iterator it = results.begin(); it != results.end(); ++it)
		{
			onServiceRefRegistered(*it);
		}
	}
}


void ServiceListener::onServiceRegistered(ServiceEvent& event)
{
	onServiceRefRegistered(event.service());
}


void ServiceListener::onServiceUnregistered(ServiceEvent& event)
{
	onServiceRefUnregistered(event.service());
}


void ServiceListener::onServiceRefRegistered(const ServiceRef::Ptr& pServiceRef)
{
	if (_pExpr->evaluate(pServiceRef->properties()))
	{
		bool notify = false;
		Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);
		if (_refs.find(pServiceRef) == _refs.end())
		{
			_refs.insert(pServiceRef);
			notify = true;
		}
		lock.unlock();
		if (notify)
		{
			serviceRegistered(this, pServiceRef);
		}
	}
}


void ServiceListener::onServiceRefUnregistered(const ServiceRef::Ptr& pServiceRef)
{
	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);
	std::set<ServiceRef::Ptr>::iterator it = _refs.find(pServiceRef);
	if (it != _refs.end())
	{
		_refs.erase(it);
		lock.unlock();
		serviceUnregistered(this, pServiceRef);
	}
}


} } // namespace Poco::OSP
