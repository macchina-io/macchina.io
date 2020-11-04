//
// BundleContextFactory.cpp
//
// Library: OSP
// Package: Bundle
// Module:  BundleContextFactory
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleContextFactory.h"
#include "Poco/OSP/BundleContext.h"


namespace Poco {
namespace OSP {


BundleContextFactory::BundleContextFactory(ServiceRegistry& registry, SystemEvents& systemEvents):
	_registry(registry),
	_systemEvents(systemEvents),
	_persistencyDir(Poco::Path::current() + "data")
{
}


BundleContextFactory::BundleContextFactory(ServiceRegistry& registry, SystemEvents& systemEvents, const Poco::Path& persistencyDir):
	_registry(registry),
	_systemEvents(systemEvents),
	_persistencyDir(persistencyDir)
{
}


BundleContextFactory::~BundleContextFactory()
{
}


BundleContext* BundleContextFactory::createBundleContext(BundleLoader& loader, Bundle::ConstPtr pBundle, BundleEvents& events)
{
	return new BundleContext(loader, pBundle, events, _systemEvents, _registry, _persistencyDir);
}


} } // namespace Poco::OSP
