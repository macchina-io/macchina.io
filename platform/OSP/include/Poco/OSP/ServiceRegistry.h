//
// ServiceRegistry.h
//
// Library: OSP
// Package: Service
// Module:  ServiceRegistry
//
// Definition of the ServiceRegistry class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_ServiceRegistry_INCLUDED
#define OSP_ServiceRegistry_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceEvent.h"
#include "Poco/OSP/ServiceListener.h"
#include "Poco/AbstractDelegate.h"
#include "Poco/BasicEvent.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"
#include <map>
#include <vector>
#include <cstddef>


namespace Poco {
namespace OSP {


class Properties;
class QLExpr;


class OSP_API ServiceRegistry
	/// The ServiceRegistry allows a bundle to provide services
	/// to other bundle, and to find services provided by
	/// other bundles.
	///
	/// A bundle can provide and register arbitrary services
	/// in the form of interface classes. Every service a bundle
	/// provides must be implemented in a class derived from
	/// Service. Service objects are reference counted.
	///
	/// A service can be implemented and registered as a singleton,
	/// meaning there exists exacty one instance of the service
	/// providing services to all bundles in the system.
	/// Alternatively, a service can be implemented and registered
	/// using a service factory. A service factory provides a unique
	/// instance of the service class to everyone requesting
	/// the Service object.
	///
	/// If a service is to be registered using a service factory,
	/// a corresponding subclass of ServiceFactory must be implemented
	/// for the Service class. An instance of the ServiceFactory
	/// must then be registered instead of the Service object itself.
{
public:
	ServiceRegistry();
		/// Creates the ServiceRegistry.

	~ServiceRegistry();
		/// Destroys the ServiceRegistry.

	Poco::BasicEvent<ServiceEvent> serviceRegistered;
		/// Fired whenever a new service has been registered.

	Poco::BasicEvent<ServiceEvent> serviceUnregistered;
		/// Fired whenever a service has been unregistered.

	ServiceRef::Ptr registerService(const std::string& name, Service::Ptr pService, const Properties& props);
		/// Registers the service object given in pService under the given name,
		/// and with the given service properties.
		///
		/// Returns a ServiceRef object for the registered service that can later
		/// be used to update the service properties.
		///
		/// Throws a Poco::ExistsException if a service with that name
		/// has already been registered.

	void unregisterService(const std::string& name);
		/// Unregisters the service with the given name.
		///
		/// Throws a Poco::NotFoundException if no service with
		/// the given name exists.

	void unregisterService(ServiceRef::Ptr pServiceRef);
		/// Unregisters the service specified by pServiceRef.

	ServiceRef::ConstPtr findByName(const std::string& name) const;
		/// Looks up a service with the given name.
		///
		/// Returns a ServiceRef for the given service,
		/// or a NULL pointer if the service does not exist.

	std::size_t find(const std::string& query, std::vector<ServiceRef::Ptr>& results) const;
		/// Looks up a service(s) with the properties specified
		/// by the given query.
		///
		/// The string given in query must be a valid query
		/// expression according to the syntax given below.
		///
		/// Fills the given results vector with ServiceRef objects
		/// matching the given query and returns the number
		/// of matches found.
		///
		/// The query language syntax is as follows:
		///     expr          ::= andExpr ["||" andExpr]
		///     andExpr       ::= relExpr ["&&" relExpr]
		///     relExpr       ::= ["!"] (id [relOp value | "=~" matchExpr]) | subExpr
		///     subExpr       ::= "(" expr ")"
		///     relOp         ::= "==" | "!=" | "<" | "<=" | ">" | ">="
		///     value         ::= numLiteral | boolLiteral | stringLiteral
		///     numLiteral    ::= [sign] digit*"."digit*["E"["+" | "-"]digit*]
		///     boolLiteral   ::= "true" | "false"
		///     stringLiteral ::= '"' char* '"'
		///     matchExpr     ::= stringLiteral | regExpr
		///     regExpr       ::= delim char+ delim /* valid Perl regular expression,
		///                                            enclosed in delim */
		///     delim         ::= "/" | "#"
		///
		/// Examples for valid queries:
		///     * name == "com.appinf.osp.sample.service" - a simple string comparison for equality.
		///     * majorVersion > 1 && minorVersion >= 5 - numeric comparisons and logical AND.
		///     * name =~ "com.appinf.osp.*" && someProperty - simple pattern matching and
		///       test for existence of someProperty.
		///     * someProperty =~ /[0-9]+/ - regular expression matching.

	std::size_t find(const QLExpr& expr, std::vector<ServiceRef::Ptr>& results) const;
		/// An overload of find() that takes a parsed query in the form of a QLExpr
		/// object instead of a query string.

	std::vector<ServiceRef::Ptr> find(const std::string& query) const;
		/// A convenience overload of find() that directly returns a vector of ServiceRef objects.

	template <typename Delegate>
	ServiceListener::Ptr createListener(const std::string& query, const Delegate& registeredDelegate, const Delegate& unregisteredDelegate);
		/// Returns a new ServiceListener instance that will listen for services matching
		/// the given query.
		///
		/// See find() for a description of the query language syntax.
		///
		/// The given registeredDelegate will be called when a new service has been
		/// registered that matches the given query. It will be added to the
		/// ServiceListener's serviceRegistered event.
		///
		/// The given unregisteredDelegate will be called when a previously matched
		/// service has been unregistered. It will be added to the
		/// ServiceListener's serviceUnregistered event.
		///
		/// If services that match the given query already have been registered,
		/// the registeredDelegate will be immediately called for each matching
		/// service.
		///
		/// Both delegates must accept a const Poco::OSP::ServiceRef::Ptr& as argument.

	static const std::string PROP_NAME;
	static const std::string PROP_TYPE;
	static const std::string PROP_DEMANGLED_TYPE;

private:
	ServiceRegistry(const ServiceRegistry&);
	ServiceRegistry& operator = (const ServiceRegistry&);

	using ServiceMap = std::map<std::string, ServiceRef::Ptr>;

	ServiceMap    _services;
	Poco::Logger& _logger;
	mutable Poco::FastMutex _mutex;
};


//
// inlines
//
template <typename Delegate>
ServiceListener::Ptr ServiceRegistry::createListener(const std::string& query, const Delegate& registeredDelegate, const Delegate& unregisteredDelegate)
{
	return new ServiceListener(*this, query, registeredDelegate, unregisteredDelegate);
}


inline std::vector<ServiceRef::Ptr> ServiceRegistry::find(const std::string& query) const
{
	std::vector<ServiceRef::Ptr> result;
	find(query, result);
	return result;
}


} } // namespace Poco::OSP


#endif // OSP_ServiceRegistry_INCLUDED
