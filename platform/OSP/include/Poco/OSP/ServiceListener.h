//
// ServiceListener.h
//
// Library: OSP
// Package: Service
// Module:  ServiceListener
//
// Definition of the ServiceListener class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_ServiceListener_INCLUDED
#define OSP_ServiceListener_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/QLExpr.h"
#include "Poco/BasicEvent.h"
#include "Poco/AutoPtr.h"
#include "Poco/Mutex.h"
#include <set>


namespace Poco {
namespace OSP {


class ServiceRegistry;
class ServiceEvent;


class OSP_API ServiceListener: public Poco::RefCountedObject
	/// ServiceListener objects are used to dynamically react to service
	/// registrations and unregistrations.
	///
	/// A ServiceListener is created with a query string (in same format
	/// as the one passed to ServiceRegistry::find()), as well as two
	/// event delegates by calling ServiceRegistry::createListener().
	///
	/// Whenever a service is registered that matches the given query,
	/// the serviceRegistered event is fired.
	///
	/// Correspondingly, when a matching service is unregistered,
	/// the serviceUnregistered event is fired.
	///
	/// When the ServiceListener is created and there are already services
	/// registered that match the query, the serviceRegistered delegate
	/// is immediately called for each service.
{
public:
	using Ptr = Poco::AutoPtr<ServiceListener>;
	using ConstPtr = const Ptr;

	Poco::BasicEvent<const ServiceRef::Ptr> serviceRegistered;
		/// Fired when a service matching the query string has
		/// been newly registered.

	Poco::BasicEvent<const ServiceRef::Ptr> serviceUnregistered;
		/// Fired when a previously registered service
		/// matching the query string has been unregistered.

	~ServiceListener();
		/// Destroys the ServiceListener.

protected:
	template <typename Delegate>
	ServiceListener(ServiceRegistry& registry, const std::string& query, const Delegate& registeredDelegate, const Delegate& unregisteredDelegate);

	void init(const std::string& query);
	void onServiceRegistered(ServiceEvent& event);
	void onServiceUnregistered(ServiceEvent& event);
	void onServiceRefRegistered(const ServiceRef::Ptr& pServiceRef);
	void onServiceRefUnregistered(const ServiceRef::Ptr& pServiceRef);

private:
	ServiceRegistry& _registry;
	std::set<ServiceRef::Ptr> _refs;
	QLExpr::Ptr _pExpr;
	Poco::FastMutex _mutex;

	friend class ServiceRegistry;
};


//
// inlines
//
template <typename Delegate>
ServiceListener::ServiceListener(ServiceRegistry& registry, const std::string& query, const Delegate& registeredDelegate, const Delegate& unregisteredDelegate):
	_registry(registry)
{
	serviceRegistered += registeredDelegate;
	serviceUnregistered += unregisteredDelegate;
	init(query);
}


} } // namespace Poco::OSP


#endif // OSP_ServiceListener_INCLUDED
