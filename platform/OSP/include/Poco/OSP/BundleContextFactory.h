//
// BundleContextFactory.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/BundleContextFactory.h#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleContextFactory
//
// Definition of the BundleContextFactory class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_BundleContextFactory_INCLUDED
#define OSP_BundleContextFactory_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Path.h"


namespace Poco {
namespace OSP {


class BundleContext;
class BundleEvents;
class SystemEvents;
class BundleLoader;
class ServiceRegistry;


class OSP_API BundleContextFactory: public Poco::RefCountedObject
	/// This is a factory for BundleContext objects,
	/// used by the BundleLoader.
{
public:
	typedef Poco::AutoPtr<BundleContextFactory> Ptr;
	typedef const Ptr ConstPtr;

	BundleContextFactory(ServiceRegistry& registry, SystemEvents& systemEvents);
		/// Creates the BundleContextFactory.

	BundleContextFactory(ServiceRegistry& registry, SystemEvents& systemEvents, const Path& persistencyDir);
		/// Creates the BundleContextFactory.
		
	virtual BundleContext* createBundleContext(BundleLoader& loader, Bundle::ConstPtr pBundle, BundleEvents& events);
		/// Creates and returns a new BundleContext object.

protected:
	~BundleContextFactory();
		/// Destroys the BundleContextFactory.

private:
	ServiceRegistry& _registry;
	SystemEvents&    _systemEvents;
	Poco::Path       _persistencyDir;
};


} } // namespace Poco::OSP


#endif // OSP_BundleContextFactory_INCLUDED
