//
// BundleContext.cpp
//
// Library: OSP
// Package: Bundle
// Module:  BundleContext
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/BundleLoader.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/File.h"
#include "Poco/Exception.h"


using Poco::File;
using Poco::Path;
using Poco::Logger;


namespace Poco {
namespace OSP {


BundleContext::BundleContext(BundleLoader& loader, Bundle::ConstPtr pBundle, BundleEvents& events, SystemEvents& systemEvents, ServiceRegistry& registry, const Path& persistencyDir):
	_loader(loader),
	_pBundle(pBundle),
	_events(events),
	_systemEvents(systemEvents),
	_registry(registry),
	_logger(Logger::get(loggerName(pBundle)))
{
	initPersistency(persistencyDir);
}


BundleContext::~BundleContext()
{
	try
	{
		File f(_temporaryDir);
		if (f.exists())
			f.remove(true);
	}
	catch (...)
	{
	}
}


Bundle::ConstPtr BundleContext::findBundle(const std::string& name) const
{
	return _loader.findBundle(name);
}


Bundle::ConstPtr BundleContext::findBundle(int id) const
{
	return _loader.findBundle(id);
}


void BundleContext::listBundles(std::vector<Bundle::Ptr>& bundles) const
{
	_loader.listBundles(bundles);
}


void BundleContext::listBundles(std::vector<Bundle::Ptr>& bundles, BundleFilter::Ptr pFilter) const
{
	_loader.listBundles(bundles, pFilter);
}


std::string BundleContext::pathForLibrary(const std::string& libraryName)
{
	return _loader.pathForLibrary(libraryName);
}


const Poco::Path& BundleContext::temporaryDirectory() const
{
	File f(_temporaryDir);
	f.createDirectories();
	return _temporaryDir;
}


const Poco::Path& BundleContext::persistentDirectory() const
{
	File f(_persistentDir);
	f.createDirectories();
	return _persistentDir;
}


BundleContext::Ptr BundleContext::contextForBundle(Bundle::ConstPtr pBundle) const
{
	return _loader.contextForBundle(pBundle);
}


void BundleContext::initPersistency(const Poco::Path& persistencyPath)
{
	_temporaryDir  = persistencyPath;
	_persistentDir = persistencyPath;
	_temporaryDir.makeDirectory();
	_persistentDir.makeDirectory();
	_temporaryDir.pushDirectory(_pBundle->symbolicName());
	_persistentDir.pushDirectory(_pBundle->symbolicName());
	_temporaryDir.pushDirectory("tmp");
	_persistentDir.pushDirectory("var");
}


std::string BundleContext::loggerName(const Bundle* pBundle)
{
	std::string loggerName("osp.bundle.");
	loggerName.append(pBundle->symbolicName());
	return loggerName;
}


} } // namespace Poco::OSP
