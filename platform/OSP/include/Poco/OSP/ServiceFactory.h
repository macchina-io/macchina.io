//
// ServiceFactory.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/ServiceFactory.h#1 $
//
// Library: OSP
// Package: Service
// Module:  ServiceFactory
//
// Definition of the ServiceFactory class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_ServiceFactory_INCLUDED
#define OSP_ServiceFactory_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Service.h"


namespace Poco {
namespace OSP {


class OSP_API ServiceFactory: public Service
	/// A ServiceFactory is a special Service that, as its name
	/// implies, acts as a factory for Service objects.
	///
	/// If a subclass of ServiceFactory is registered as a
	/// service, the factory will be used to create a new
	/// instance of the service whenever the service is
	/// requested from the ServiceRegistry.
{
public:
	virtual Service::Ptr createService() = 0;
		/// Creates and returns a new instance of a Service.
		
	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;
		
protected:
	ServiceFactory();
		/// Creates the ServiceFactory.

	~ServiceFactory();
		/// Destroys the ServiceFactory.
};


} } // namespace Poco::OSP


#endif // OSP_ServiceFactory_INCLUDED
