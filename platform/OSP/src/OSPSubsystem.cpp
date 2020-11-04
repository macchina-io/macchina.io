//
// OSPSubsystem.cpp
//
// Library: OSP
// Package: Util
// Module:  OSPSubsystem
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/OSPSubsystem.h"
#include "Poco/OSP/CodeCache.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/BundleFactory.h"
#include "Poco/OSP/BundleContextFactory.h"
#include "Poco/OSP/BundleLoader.h"
#include "Poco/OSP/BundleRepository.h"
#include "Poco/OSP/LanguageTag.h"
#include "Poco/OSP/BundleStreamFactory.h"
#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/OSP/BundleInstallerService.h"
#include "Poco/OSP/Properties.h"
#include "Poco/Util/Application.h"
#include "Poco/Exception.h"


namespace Poco {
namespace OSP {


OSPSubsystem::OSPSubsystem():
	_pCodeCache(0),
	_pServiceRegistry(0),
	_pBundleLoader(0),
	_pBundleRepository(0),
	_clearCache(false),
	_cancelInit(false)
{
}


OSPSubsystem::~OSPSubsystem()
{
	delete _pCodeCache;
	delete _pServiceRegistry;
	delete _pBundleLoader;
	delete _pBundleRepository;
}


void OSPSubsystem::cancelInit()
{
	_cancelInit = true;
}


void OSPSubsystem::setBundleFilter(BundleFilter::Ptr pFilter)
{
	_pBundleFilter = pFilter;
}

	
BundleFilter::Ptr OSPSubsystem::getBundleFilter() const
{
	return _pBundleFilter;
}


void OSPSubsystem::initialize(Poco::Util::Application& app)
{
	if (_cancelInit) return;

	std::string codeCache        = app.config().getString("osp.codeCache", app.config().expand("${application.dir}codeCache"));
	std::string bundleRepository = app.config().getString("osp.bundleRepository", app.config().expand("${application.dir}bundles"));
	std::string dataPath         = app.config().getString("osp.data", app.config().expand("${application.dir}data"));
	bool autoUpdateCodeCache     = app.config().getBool("osp.autoUpdateCodeCache", true);
	bool sharedCodeCache         = app.config().getBool("osp.sharedCodeCache", false);

	if (!_bundles.empty())
	{
		bundleRepository += ";";
		bundleRepository += _bundles;
	}

	LanguageTag languageTag;
	if (app.config().hasProperty("osp.language"))
	{
		languageTag = LanguageTag(app.config().getString("osp.language"));
	}
	
	_pCodeCache = new CodeCache(codeCache, sharedCodeCache);
	if (_clearCache)
	{
		try
		{
			app.logger().information("Clearing code cache");

			CodeCache::Lock ccLock(*_pCodeCache);
			_pCodeCache->clear();
		}
		catch (Poco::Exception& exc)
		{
			app.logger().warning(std::string("Cannot clear code cache: ") + exc.displayText());
		}
	}
	
	_pServiceRegistry  = new ServiceRegistry;
	BundleFactory::Ptr pBundleFactory(new BundleFactory(languageTag));
	BundleContextFactory::Ptr pBundleContextFactory(new BundleContextFactory(*_pServiceRegistry, _systemEvents, dataPath));
	_pBundleLoader     = new BundleLoader(*_pCodeCache, pBundleFactory, pBundleContextFactory, autoUpdateCodeCache);
	_pBundleRepository = new BundleRepository(bundleRepository, *_pBundleLoader, _pBundleFilter);
	
	BundleStreamFactory::registerFactory(*_pBundleLoader);
	
	Service::Ptr pExtensionPointService(new ExtensionPointService(_pBundleLoader->events()));
	Service::Ptr pPreferencesService(new PreferencesService(dataPath, &app.config()));
	Service::Ptr pBundleInstallerService(new BundleInstallerService(*_pBundleRepository));
	_pServiceRegistry->registerService(ExtensionPointService::SERVICE_NAME, pExtensionPointService, Properties());
	_pServiceRegistry->registerService(PreferencesService::SERVICE_NAME, pPreferencesService, Properties());
	_pServiceRegistry->registerService(BundleInstallerService::SERVICE_NAME, pBundleInstallerService, Properties());
	
	loadBundles(app);
	startBundles(app);

	app.logger().information("Startup complete.");
}


void OSPSubsystem::loadBundles(Poco::Util::Application& app)
{
	app.logger().information("Loading bundles...");
	_pBundleRepository->loadBundles();

	// Set osp.version if osp.core bundle exists
	Bundle::Ptr pCoreBundle = _pBundleLoader->findBundle("osp.core");
	if (pCoreBundle)
	{
		app.config().setString("osp.version", pCoreBundle->version().toString());
	}
	app.config().setString("osp.osname", _pBundleLoader->osName());
	app.config().setString("osp.osarch", _pBundleLoader->osArchitecture());
}


void OSPSubsystem::startBundles(Poco::Util::Application& app)
{
	app.logger().information("Resolving bundles...");
	_pBundleLoader->resolveAllBundles();
	
	app.logger().information("Starting bundles...");
	_pBundleLoader->startAllBundles();
	
	SystemEvents::EventKind systemEvent = SystemEvents::EV_SYSTEM_STARTED;
	_systemEvents.systemStarted(this, systemEvent);
}

	
void OSPSubsystem::uninitialize()
{
	if (_pBundleLoader)
	{
		BundleStreamFactory::unregisterFactory();
		
		Poco::Util::Application::instance().logger().information("Stopping bundles...");
		
		SystemEvents::EventKind systemEvent = SystemEvents::EV_SYSTEM_SHUTTING_DOWN;
		_systemEvents.systemShuttingDown(this, systemEvent);
		
		_pBundleLoader->stopAllBundles();
		
		_pServiceRegistry->unregisterService(ExtensionPointService::SERVICE_NAME);
		_pServiceRegistry->unregisterService(PreferencesService::SERVICE_NAME);
		_pServiceRegistry->unregisterService(BundleInstallerService::SERVICE_NAME);

		Poco::Util::Application::instance().logger().information("Shutdown complete.");
	}
}


void OSPSubsystem::defineOptions(Poco::Util::OptionSet& options)
{
	options.addOption(
		Poco::Util::Option("clean", "C", "Start with clean code cache.")
			.required(false)
			.repeatable(false)
			.callback(Poco::Util::OptionCallback<OSPSubsystem>(this, &OSPSubsystem::handleClear)));

	options.addOption(
		Poco::Util::Option("bundles", "B", "Specify a semicolon-separated list of bundles or bundle repositories.")
			.required(false)
			.repeatable(false)
			.argument("paths")
			.callback(Poco::Util::OptionCallback<OSPSubsystem>(this, &OSPSubsystem::handleBundles)));
}


const char* OSPSubsystem::name() const
{
	return "Open Service Platform";
}


void OSPSubsystem::handleClear(const std::string& name, const std::string& value)
{
	_clearCache = true;
}


void OSPSubsystem::handleBundles(const std::string& name, const std::string& value)
{
	_bundles = value;
}


} } // namespace Poco::OSP
