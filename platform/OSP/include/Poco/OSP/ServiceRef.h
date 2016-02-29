//
// ServiceRef.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/ServiceRef.h#1 $
//
// Library: OSP
// Package: Service
// Module:  ServiceRef
//
// Definition of the ServiceRef class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_ServiceRef_INCLUDED
#define OSP_ServiceRef_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Service.h"
#include "Poco/OSP/Properties.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Exception.h"


namespace Poco {
namespace OSP {


class OSP_API ServiceRef: public Poco::RefCountedObject
	/// ServiceRef objects are used by the ServiceRegistry class
	/// to manage service registrations.
{
public:
	typedef Poco::AutoPtr<ServiceRef> Ptr;
	typedef const Ptr ConstPtr;

	ServiceRef(const std::string& name, const Properties& props, Service::Ptr pService);
		/// Creates the ServiceRef, using the given arguments.

	const std::string& name() const;
		/// Returns the name under which the service
		/// has been registered.
		
	const Properties& properties() const;
		/// Returns the service properties.
		
	Properties& properties();
		/// Returns the service properties.
		
	Service::Ptr instance() const;
		/// Returns an instance of the Service.
		///
		/// If a ServiceFactory has been registered for the service,
		/// creates and returns a new instance of the Service class.
		/// Otherwise, returns the registered Service object.
		
	template <class Svc>
	Poco::AutoPtr<Svc> castedInstance() const
		/// Returns an instance of the Service.
		///
		/// If a ServiceFactory has been registered for the service,
		/// creates and returns a new instance of the Service class.
		/// Otherwise, returns the registered Service object.
		///
		/// Throws a Poco::BadCastException if the service object
		/// cannot be casted to the desired type.
	{
		Service::Ptr pService = instance();
		if (pService->isA(typeid(Svc)))
		{
			// We'd like to use AutoPtr::unsafeCast<Svc>() here,
			// but older GCC versions don't like it.
			Svc* pCasted = static_cast<Svc*>(pService.get());
			return Poco::AutoPtr<Svc>(pCasted, true);
		}
		else 
		{
			std::string msg("Cannot cast from ");
			msg += pService->type().name();
			msg += " to ";
			msg += typeid(Svc).name();
			throw Poco::BadCastException(msg);
		}
	}

protected:
	~ServiceRef();
		/// Destroys the ServiceRef.

private:
	ServiceRef();
	ServiceRef(const ServiceRef&);
	ServiceRef& operator = (const ServiceRef&);

	std::string  _name;
	Properties   _props;
	Service::Ptr _pService;
};


//
// inlines
//
inline const std::string& ServiceRef::name() const
{
	return _name;
}


inline const Properties& ServiceRef::properties() const
{
	return _props;
}

	
inline Properties& ServiceRef::properties()
{
	return _props;
}


} } // namespace Poco::OSP


#endif // OSP_ServiceRef_INCLUDED
