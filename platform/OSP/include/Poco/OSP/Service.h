//
// Service.h
//
// Library: OSP
// Package: Service
// Module:  Service
//
// Definition of the Service class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_Service_INCLUDED
#define OSP_Service_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include <typeinfo>


namespace Poco {
namespace OSP {


class OSP_API Service: public virtual Poco::RefCountedObject
	/// This is the base class for all services
	/// registered with the ServiceRegistry.
	///
	/// All subclasses of Service must override
	/// the type() and isA() member functions.
{
public:
	using Ptr = Poco::AutoPtr<Service>;
	using ConstPtr = const Ptr;

	virtual const std::type_info& type() const;
		/// Returns the type information for the object's class.
		///
		/// Subclasses must override this member function.
		///
		/// The implementation of isA() is usually as follows:
		///     const std::type_info& MyService::type() const
		///     {
		///         return typeid(MyService);
		///     }
		///
		/// If a service class implements a service interface,
		/// the type information for the interface class should
		/// be returned instead:
		///     const std::type_info& MyServiceImpl::type() const
		///     {
		///         return typeid(MyService);
		///     }

	virtual bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class
		/// given by type. Comparison must always be done by
		/// type name, not by simply comparing std::type_info object
		/// references.
		///
		/// Subclasses must override this member function.
		///
		/// The implementation of isA() is always as follows:
		///     bool MyService::isA(const std::type_info& otherType) const
		///     {
		///         std::string name(typeid(MyService).name());
		///         return name == otherType.name() || MyBaseClass::isA(otherType);
		///     }

protected:
	Service();
		/// Creates the Service.

	~Service();
		/// Destroys the Service.
};


} } // namespace Poco::OSP


#endif // OSP_Service_INCLUDED
