//
// GreetingService.cpp
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "GreetingService.h"
#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::Properties;
using Poco::OSP::ServiceRef;


class GreetingServiceImpl: public GreetingService
{
public:
	GreetingServiceImpl(BundleContext::Ptr pContext):
		_pContext(pContext)
	{
	}
	
	~GreetingServiceImpl()
	{
	}
	
	std::string greeting()
	{
		// The greeting text is stored in a localized bundle property.
		// The framework will automatically return the greeting in the
		// correct language, if it exists, or in English otherwise.
		
		return _pContext->thisBundle()->properties().getString("greeting");
	}
	
	const std::type_info& type() const
	{
		return typeid(GreetingService);
	}
	
	bool isA(const std::type_info& otherType) const
	{
		std::string name(typeid(GreetingService).name());
		return name == otherType.name() || Service::isA(otherType);
	}

private:
	BundleContext::Ptr _pContext;
};


class GreetingServiceBundleActivator: public BundleActivator
	/// The BundleActivator for the GreetingService.
	/// Registers the GreetingService with the Service Registry.
{
public:
	GreetingServiceBundleActivator()
	{
	}
	
	~GreetingServiceBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		// Create an instance of the GreetingService
		GreetingService::Ptr pService = new GreetingServiceImpl(pContext);
		// Register the GreetingService with the ServiceRegistry.
		_pService = pContext->registry().registerService("com.appinf.osp.samples.GreetingService", pService, Properties());
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		// Unregister the GreetingService
		pContext->registry().unregisterService(_pService);
	}
	
private:
	ServiceRef::Ptr _pService;
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(GreetingServiceBundleActivator)
POCO_END_MANIFEST
