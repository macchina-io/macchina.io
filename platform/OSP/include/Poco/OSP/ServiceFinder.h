//
// ServiceFinder.h
//
// Library: OSP
// Package: Service
// Module:  ServiceFinder
//
// Definition of the ServiceFinder class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_ServiceFinder_INCLUDED
#define OSP_ServiceFinder_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Service.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/Exception.h"


namespace Poco {
namespace OSP {


class OSP_API ServiceFinder
	/// A utility class that simplifies service
	/// lookup and instantiation.
{
public:
	template <typename Svc>
	static Poco::AutoPtr<Svc> findByName(Poco::OSP::BundleContext::Ptr pContext, const std::string& name)
		/// Looks up the service with the given name, casts it to the class
		/// given by the template argument and returns it.
		///
		/// Throws a Poco::NotFoundException if the service cannot be found.
		/// Throws a Poco::BadCastException if the cast cannot be performed.
	{
		Poco::OSP::ServiceRef::Ptr pSvcRef = pContext->registry().findByName(name);
		if (!pSvcRef) throw Poco::NotFoundException(name);
		return pSvcRef->castedInstance<Svc>();
	}
	
	template <typename Svc>
	static Poco::AutoPtr<Svc> find(Poco::OSP::BundleContext::Ptr pContext)
		/// Looks up the service with the name given by Svc::SERVICE_NAME, 
		/// casts it to the class given by the template argument and returns it.
		///
		/// Throws a Poco::NotFoundException if the service cannot be found.
		/// Throws a Poco::BadCastException if the cast cannot be performed.
	{
		return findByName<Svc>(pContext, Svc::SERVICE_NAME);
	}
};


} } // namespace Poco::OSP


#endif // OSP_ServiceFinder_INCLUDED
