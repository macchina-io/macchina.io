//
// ServiceRegistry.cpp
//
// Library: OSP
// Package: Service
// Module:  ServiceRegistry
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/QLExpr.h"
#include "Poco/OSP/QLParser.h"
#include "Poco/Exception.h"


using namespace std::string_literals;


using Poco::Logger;
using Poco::FastMutex;


namespace Poco {
namespace OSP {


const std::string ServiceRegistry::PROP_NAME("name");
const std::string ServiceRegistry::PROP_TYPE("type");
const std::string ServiceRegistry::PROP_DEMANGLED_TYPE("dtype");


ServiceRegistry::ServiceRegistry():
	_logger(Logger::get("osp.core.ServiceRegistry"s))
{
}


ServiceRegistry::~ServiceRegistry()
{
}


ServiceRef::Ptr ServiceRegistry::registerService(const std::string& name, Service::Ptr pService, const Properties& props)
{
	Poco::ScopedLockWithUnlock<FastMutex> lock(_mutex);

	ServiceMap::iterator it = _services.find(name);
	if (it == _services.end())
	{
		const char* type = pService->type().name();
		const std::string dtype = ServiceRef::demangle(type);
		ServiceRef::Ptr pServiceRef(new ServiceRef(name, props, pService));
		pServiceRef->properties().set(PROP_NAME, name);
		pServiceRef->properties().set(PROP_TYPE, std::string(type));
		pServiceRef->properties().set(PROP_DEMANGLED_TYPE, dtype);
		_services[name] = pServiceRef;

		lock.unlock();

		ServiceEvent registeredEvent(pServiceRef, ServiceEvent::EV_SERVICE_REGISTERED);
		serviceRegistered(this, registeredEvent);

		_logger.information("Service registered: %s [%s]."s, name, dtype);

		return pServiceRef;
	}
	else throw Poco::ExistsException(name);
}


void ServiceRegistry::unregisterService(const std::string& name)
{
	Poco::ScopedLockWithUnlock<FastMutex> lock(_mutex);

	ServiceMap::iterator it = _services.find(name);
	if (it != _services.end())
	{
		ServiceEvent unregisteredEvent(it->second, ServiceEvent::EV_SERVICE_UNREGISTERED);
		_services.erase(it);

		lock.unlock();

		serviceUnregistered(this, unregisteredEvent);

		_logger.information("Service unregistered: %s"s, name);
	}
	else throw Poco::NotFoundException(name);
}


void ServiceRegistry::unregisterService(ServiceRef::Ptr pServiceRef)
{
	if (pServiceRef)
	{
		unregisterService(pServiceRef->name());
	}
}


ServiceRef::ConstPtr ServiceRegistry::findByName(const std::string& name) const
{
	FastMutex::ScopedLock lock(_mutex);

	ServiceMap::const_iterator it = _services.find(name);
	if (it != _services.end())
		return it->second;
	else
		return ServiceRef::Ptr();
}


std::size_t ServiceRegistry::find(const std::string& query, std::vector<ServiceRef::Ptr>& results) const
{
	QLParser parser(query);
	QLExpr::Ptr pExpr(parser.parse());

	return find(*pExpr, results);
}


std::size_t ServiceRegistry::find(const QLExpr& expr, std::vector<ServiceRef::Ptr>& results) const
{
	results.clear();

	FastMutex::ScopedLock lock(_mutex);

	std::size_t count(0);
	for (ServiceMap::const_iterator it = _services.begin(); it != _services.end(); ++it)
	{
		ServiceRef::Ptr pService(it->second);
		if (expr.evaluate(pService->properties()))
		{
			results.push_back(pService);
			++count;
		}
	}
	return count;
}


} } // namespace Poco::OSP
