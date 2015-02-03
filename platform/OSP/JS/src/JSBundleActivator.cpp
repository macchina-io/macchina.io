//
// JSBundleActivator.cpp
//
// $Id: //poco/1.4/OSP/JS/src/JSBundleActivator.cpp#6 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/JS/Bridge/Listener.h"
#include "Poco/JS/Bridge/BridgeWrapper.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "JSExtensionPoint.h"
#include "JSServletFilter.h"
#include "JSServerPageFilter.h"


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
	
		// find ExtensionPointService using the Service Registry
		Poco::OSP::ServiceRef::Ptr pXPSRef = pContext->registry().findByName("osp.core.xp");
		if (pXPSRef)
		{
			_pXPS = pXPSRef->castedInstance<ExtensionPointService>();
			Poco::OSP::ExtensionPoint::Ptr pXP = new JSExtensionPoint(pContext);
			_pXPS->registerExtensionPoint(pContext->thisBundle(), "com.appinf.osp.js", pXP);
		}
		else
		{
			pContext->logger().error("The OSP ExtensionPointService is not available.");
		}
		
		Poco::JS::Bridge::Listener::Ptr pListener = new Poco::JS::Bridge::Listener;
		_jsBridgeListenerId = Poco::RemotingNG::ORB::instance().registerListener(pListener);
		
		std::vector<ServiceRef::Ptr> services;
		pContext->registry().find("name", services);
		for (std::vector<ServiceRef::Ptr>::iterator it = services.begin(); it != services.end(); ++it)
		{
			registerServiceWithORB(*it);
		}
		
		pContext->registry().serviceRegistered   += Poco::delegate(this, &JSBundleActivator::handleServiceRegistered);
		pContext->registry().serviceUnregistered += Poco::delegate(this, &JSBundleActivator::handleServiceUnregistered);
		
		Poco::JS::Bridge::BridgeWrapper::registerTransportFactory();
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		if (_pXPS)
		{
			_pXPS->unregisterExtensionPoint("com.appinf.osp.js");
			_pXPS = 0;
		}
	
		Poco::RemotingNG::ORB::instance().unregisterListener(_jsBridgeListenerId, true);
		Poco::JS::Bridge::BridgeWrapper::unregisterTransportFactory();

		pContext->registry().serviceRegistered   -= Poco::delegate(this, &JSBundleActivator::handleServiceRegistered);
		pContext->registry().serviceUnregistered -= Poco::delegate(this, &JSBundleActivator::handleServiceUnregistered);

		_pContext = 0;
	}

	void handleServiceRegistered(const void* sender, ServiceEvent& event)
	{
		_pContext->logger().information("Service registered: " + event.service()->name());
		registerServiceWithORB(event.service());
	}

	void handleServiceUnregistered(const void* sender, ServiceEvent& event)
	{
		if (event.service()->properties().has("jsbridge"))
		{
			_pContext->logger().information("Unregistering service with ORB: " + event.service()->name());

			std::string uri = event.service()->properties().get("jsbridge");
			Poco::RemotingNG::ORB::instance().unregisterObject(uri);
		}
	}
	
	void registerServiceWithORB(ServiceRef::Ptr pServiceRef)
	{
		Poco::OSP::Service::Ptr pService = pServiceRef->instance();
		if (dynamic_cast<Poco::RemotingNG::RemoteObject*>(pService.get()))
		{
			_pContext->logger().information("Registering service with ORB: " + pServiceRef->name());
			Poco::RemotingNG::RemoteObject::Ptr pRemoteObject = pService.cast<Poco::RemotingNG::RemoteObject>();
			std::string uri = Poco::RemotingNG::ORB::instance().registerObject(pRemoteObject, _jsBridgeListenerId);		
			pRemoteObject->remoting__enableRemoteEvents("jsbridge");	
			pServiceRef->properties().set("jsbridge", uri);
		}
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::ExtensionPointService::Ptr _pXPS;
	std::string _jsBridgeListenerId;
};


} } } // namespace Poco::OSP::JS


POCO_BEGIN_NAMED_MANIFEST(WebFilter, Poco::OSP::Web::WebFilterFactory)
	POCO_EXPORT_CLASS(Poco::OSP::JS::JSServletFilterFactory)
	POCO_EXPORT_CLASS(Poco::OSP::JS::JSServerPageFilterFactory)
POCO_END_MANIFEST


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(Poco::OSP::JS::JSBundleActivator)
POCO_END_MANIFEST
