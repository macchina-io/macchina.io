//
// ModuleExtensionPoint.cpp
//
// Library: OSP/JS
// Package: Module
// Module:  ModuleExtensionPoint
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/JS/ModuleExtensionPoint.h"
#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/OSP/OSPException.h"
#include "Poco/Delegate.h"


namespace Poco {
namespace OSP {
namespace JS {


const std::string ModuleExtensionPoint::EXTPOINT("com.appinf.osp.js.module");
const std::string ModuleExtensionPoint::ATTR_MODULE("module");
const std::string ModuleExtensionPoint::ATTR_CLASS("class");
const std::string ModuleExtensionPoint::ATTR_LIBRARY("library");
const std::string ModuleExtensionPoint::MANIFEST_NAME("Module");


ModuleExtensionPoint::ModuleExtensionPoint(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext),
	_pModuleRegistry(new Poco::JS::Core::ModuleRegistry)
{
	_pContext->events().bundleStopped += Poco::delegate(this, &ModuleExtensionPoint::onBundleStopped);
}


ModuleExtensionPoint::~ModuleExtensionPoint()
{
	try
	{
		_pContext->events().bundleStopped -= Poco::delegate(this, &ModuleExtensionPoint::onBundleStopped);

		LibBundleMap::iterator itLib = _libBundleMap.begin();
		while (itLib != _libBundleMap.end())
		{
			_loader.unloadLibrary(itLib->first);
			++itLib;
		}
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void ModuleExtensionPoint::handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (pExtensionElem)
	{
		const Poco::XML::XMLString& extPoint = pExtensionElem->getAttribute(ExtensionPointService::POINT_ATTR);
		if (extPoint == EXTPOINT)
			handleModule(pBundle, pExtensionElem);
		else
			throw Poco::OSP::BundleException("Failed to parse extension point");
	}
}


void ModuleExtensionPoint::handleModule(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
{
	const std::string& module    = pExtensionElem->getAttribute(ATTR_MODULE);
	const std::string& className = pExtensionElem->getAttribute(ATTR_CLASS);
	std::string library = pExtensionElem->getAttribute(ATTR_LIBRARY);

	if (library.empty())
		library = pBundle->symbolicName();

	std::string libraryPath = _pContext->pathForLibrary(library);
	if (!_loader.isLibraryLoaded(libraryPath))
	{
		_loader.loadLibrary(libraryPath, MANIFEST_NAME);
		_libBundleMap[libraryPath] = pBundle;
	}

	FactoryPtr pFactory = _loader.create(className);
	Poco::OSP::BundleContext::Ptr pContext = _pContext->contextForBundle(pBundle);
	pFactory->init(pContext);

	_pModuleRegistry->registerModule(module, pFactory->createModule());

	_modBundleMap[module] = pBundle;
}


void ModuleExtensionPoint::onBundleStopped(const void* pSender, Poco::OSP::BundleEvent& ev)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Bundle::ConstPtr pBundle = ev.bundle();

	ModBundleMap::iterator itMod = _modBundleMap.begin();
	while (itMod != _modBundleMap.end())
	{
		if (itMod->second == pBundle)
		{
			_pModuleRegistry->unregisterModule(itMod->first);
			ModBundleMap::iterator delIt(itMod);
			++itMod;
			_modBundleMap.erase(delIt);
		}
		else ++itMod;
	}

	// Note: since the module provided by the bundle may still be in use
	// by some scripts we don't know about, we do not unload the library here
	// to avoid a crash.
}


} } } // namespace Poco::OSP::JS
