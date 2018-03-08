//
// BundleActivator.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/Exception.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "AppRegistry.h"
#include "AppExtensionPoint.h"
#include "LoginPage.h"
#include "ControllerRequestHandler.h"
#include "SessionJSON.h"
#include "LauncherAppsJSON.h"


namespace IoT {
namespace Web {
namespace Launcher {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}
	
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = Poco::OSP::ServiceFinder::find<Poco::OSP::PreferencesService>(pContext);
		
		_pAppRegistry = new AppRegistry;
		_pAppRegistryRef = pContext->registry().registerService(AppRegistry::SERVICE_NAME, _pAppRegistry, Poco::OSP::Properties());

		Poco::AutoPtr<Poco::OSP::ExtensionPointService> pXPS = Poco::OSP::ServiceFinder::find<Poco::OSP::ExtensionPointService>(pContext);
		if (pXPS)
		{
			Poco::OSP::ExtensionPoint::Ptr pXP = new AppExtensionPoint(pContext, _pAppRegistry);
			pXPS->registerExtensionPoint(pContext->thisBundle(), AppExtensionPoint::ID, pXP);
		}
				
		pContext->events().bundleStopping += Poco::delegate(this, &BundleActivator::onBundleStopping);
	}
		
	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
		pContext->events().bundleStopping -= Poco::delegate(this, &BundleActivator::onBundleStopping);
		pContext->registry().unregisterService(_pAppRegistryRef);

		_pAppRegistryRef = 0;
		_pAppRegistry = 0;
		_pPrefs = 0;
		_pContext = 0;
	}

protected:
	bool getBoolConfig(const std::string& key)
	{
		return _pPrefs->configuration()->getBool(key, _pContext->thisBundle()->properties().getBool(key));
	}

	int getIntConfig(const std::string& key)
	{
		return _pPrefs->configuration()->getInt(key, _pContext->thisBundle()->properties().getInt(key));
	}
	
	std::string getStringConfig(const std::string& key)
	{
		return _pPrefs->configuration()->getString(key, _pContext->thisBundle()->properties().getString(key));
	}
	
	std::string getStringConfig(const std::string& key, const std::string& deflt)
	{
		return _pPrefs->configuration()->getString(key, _pContext->thisBundle()->properties().getString(key, deflt));
	}
	
	void onBundleStopping(const void*, Poco::OSP::BundleEvent& event)
	{
		_pContext->logger().information("Removing bundle from Launcher: " + event.bundle()->symbolicName());
		_pAppRegistry->remove(event.bundle()->symbolicName());
	}
	
private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::PreferencesService::Ptr _pPrefs;
	AppRegistry::Ptr _pAppRegistry;
	Poco::OSP::ServiceRef::Ptr _pAppRegistryRef;
};


} } } // namespace IoT::Web::Launcher


POCO_BEGIN_NAMED_MANIFEST(WebServer, Poco::OSP::Web::WebRequestHandlerFactory)
	POCO_EXPORT_CLASS(IoT::Web::Launcher::ControllerRequestHandlerFactory)
	POCO_EXPORT_CLASS(IoT::Web::Launcher::LoginPageFactory)
	POCO_EXPORT_CLASS(IoT::Web::Launcher::SessionJSONFactory)
	POCO_EXPORT_CLASS(IoT::Web::Launcher::LauncherAppsJSONFactory)
POCO_END_MANIFEST


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Web::Launcher::BundleActivator)
POCO_END_MANIFEST
