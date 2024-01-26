//
// JSBundleActivator.cpp
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/JS/Bridge/Listener.h"
#include "Poco/JS/Bridge/BridgeWrapper.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "Poco/OSP/JS/JSExecutor.h"
#include "Poco/OSP/JS/JSExtensionPoint.h"
#include "Poco/OSP/JS/ModuleExtensionPoint.h"
#include "v8.h"


using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace JS {


class JSBundleActivator: public Poco::OSP::BundleActivator
{
public:
	JSBundleActivator()
	{
	}

	~JSBundleActivator()
	{
	}

	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pContext = pContext;

		Poco::JS::Core::initialize();

		_pPrefs = Poco::OSP::ServiceFinder::find<Poco::OSP::PreferencesService>(_pContext);
		_pXPS = Poco::OSP::ServiceFinder::find<Poco::OSP::ExtensionPointService>(_pContext);

		JSExtensionPoint::Ptr pScriptXP = new JSExtensionPoint(pContext);
		_pXPS->registerExtensionPoint(pContext->thisBundle(), "com.appinf.osp.js"s, pScriptXP);

		ModuleExtensionPoint::Ptr pModuleXP = new ModuleExtensionPoint(pContext);
		_pXPS->registerExtensionPoint(pContext->thisBundle(), "com.appinf.osp.js.module"s, pModuleXP);

		JSExecutor::setGlobalModuleRegistry(pModuleXP->moduleRegistry());

		Poco::JS::Bridge::Listener::Ptr pListener = new Poco::JS::Bridge::Listener;
		_jsBridgeListenerId = Poco::RemotingNG::ORB::instance().registerListener(pListener);

		std::vector<ServiceRef::Ptr> services;
		pContext->registry().find("name"s, services);
		for (std::vector<ServiceRef::Ptr>::iterator it = services.begin(); it != services.end(); ++it)
		{
			registerServiceWithORB(*it);
		}

		pContext->registry().serviceRegistered   += Poco::delegate(this, &JSBundleActivator::handleServiceRegistered);
		pContext->registry().serviceUnregistered += Poco::delegate(this, &JSBundleActivator::handleServiceUnregistered);

		Poco::JS::Bridge::BridgeWrapper::registerTransportFactory();

		std::string paths = _pPrefs->configuration()->getString("osp.js.moduleSearchPaths"s, ""s);
		Poco::StringTokenizer pathsTok(paths, ",;", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		JSExecutor::setGlobalModuleSearchPaths(std::vector<std::string>(pathsTok.begin(), pathsTok.end()));

		std::string v8Options = _pPrefs->configuration()->getString("osp.js.v8.flags"s, ""s);
		Poco::StringTokenizer v8OptionsTok(v8Options, ",;"s, Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
		for (Poco::StringTokenizer::Iterator it = v8OptionsTok.begin(); it != v8OptionsTok.end(); ++it)
		{
			v8::V8::SetFlagsFromString(it->data(), it->size());
		}

		Poco::UInt64 memoryLimit = _pPrefs->configuration()->getUInt64("osp.js.memoryLimit"s, JSExecutor::getDefaultMemoryLimit());
		JSExecutor::setDefaultMemoryLimit(memoryLimit);

		std::string v8Version =  v8::V8::GetVersion();
		_pContext->logger().information("Using V8 version: %s"s, v8Version);
	}

	void stop(BundleContext::Ptr pContext)
	{
		_pXPS->unregisterExtensionPoint("com.appinf.osp.js"s);
		_pXPS.reset();
		_pPrefs.reset();

		Poco::RemotingNG::ORB::instance().unregisterListener(_jsBridgeListenerId, true);
		Poco::JS::Bridge::BridgeWrapper::unregisterTransportFactory();

		pContext->registry().serviceRegistered   -= Poco::delegate(this, &JSBundleActivator::handleServiceRegistered);
		pContext->registry().serviceUnregistered -= Poco::delegate(this, &JSBundleActivator::handleServiceUnregistered);

		_pContext.reset();

		Poco::JS::Core::uninitialize();
	}

	void handleServiceRegistered(const void* sender, ServiceEvent& event)
	{
		_pContext->logger().information("Service registered: "s + event.service()->name());
		registerServiceWithORB(event.service());
	}

	void handleServiceUnregistered(const void* sender, ServiceEvent& event)
	{
		if (event.service()->properties().has("jsbridge"s))
		{
			_pContext->logger().information("Unregistering service with ORB: "s + event.service()->name());

			std::string uri = event.service()->properties().get("jsbridge"s);
			Poco::RemotingNG::ORB::instance().unregisterObject(uri);
		}
	}

	void registerServiceWithORB(ServiceRef::Ptr pServiceRef)
	{
		Poco::OSP::Service::Ptr pService = pServiceRef->instance();
		if (dynamic_cast<Poco::RemotingNG::RemoteObject*>(pService.get()))
		{
			_pContext->logger().information("Registering service with ORB: "s + pServiceRef->name());
			Poco::RemotingNG::RemoteObject::Ptr pRemoteObject = pService.cast<Poco::RemotingNG::RemoteObject>();
			std::string uri = Poco::RemotingNG::ORB::instance().registerObject(pRemoteObject, _jsBridgeListenerId);
			pRemoteObject->remoting__enableRemoteEvents("jsbridge"s);
			pServiceRef->properties().set("jsbridge"s, uri);
		}
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::ExtensionPointService::Ptr _pXPS;
	Poco::OSP::PreferencesService::Ptr _pPrefs;
	std::string _jsBridgeListenerId;
};


} } } // namespace Poco::OSP::JS


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(Poco::OSP::JS::JSBundleActivator)
POCO_END_MANIFEST
