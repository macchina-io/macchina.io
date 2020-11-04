//
// NetBundleActivator.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/FTPStreamFactory.h"
#include "Poco/Net/HTTPSessionInstantiator.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::PreferencesService;
using Poco::OSP::ServiceFinder;
using Poco::Net::HTTPStreamFactory;
using Poco::Net::FTPStreamFactory;
using Poco::Net::HTTPSessionInstantiator;


class NetBundleActivator: public BundleActivator
{
public:
	NetBundleActivator()
	{
	}
	
	~NetBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		Poco::Net::initializeNetwork();
		HTTPStreamFactory::registerFactory();
		FTPStreamFactory::registerFactory();
		HTTPSessionInstantiator::registerInstantiator();

		PreferencesService::Ptr pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		if (pPrefs)
		{
			Poco::Net::HTTPClientSession::ProxyConfig proxyConfig;
			proxyConfig.host          = pPrefs->configuration()->getString("http.proxy.host", "");
			proxyConfig.port          = static_cast<Poco::UInt16>(pPrefs->configuration()->getInt("http.proxy.port", 80));
			proxyConfig.username      = pPrefs->configuration()->getString("http.proxy.username", "");
			proxyConfig.password      = pPrefs->configuration()->getString("http.proxy.password", "");
			proxyConfig.nonProxyHosts = pPrefs->configuration()->getString("http.proxy.nonProxyHosts", "");
			if (!proxyConfig.host.empty())
			{
				Poco::Net::HTTPClientSession::setGlobalProxyConfig(proxyConfig);
			}
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		HTTPSessionInstantiator::unregisterInstantiator();
		HTTPStreamFactory::unregisterFactory();
		FTPStreamFactory::unregisterFactory();
		Poco::Net::uninitializeNetwork();
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(NetBundleActivator)
POCO_END_MANIFEST
