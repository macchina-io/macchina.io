//
// Greeter.cpp
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/ClassLibrary.h"
#include "GreetingService.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRef;
using Poco::OSP::Service;


class GreeterBundleActivator: public BundleActivator
	/// The GreeterBundleActivator for the Greeter bundle.
	/// This activator looks up the GreetingService using
	/// the ServiceRegistry and invokes it.
{
public:
	GreeterBundleActivator()
	{
	}
	
	~GreeterBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		// Obtain the GreetingService object from the Service Registry.
		ServiceRef::Ptr pServiceRef = pContext->registry().findByName("com.appinf.osp.samples.GreetingService");
		if (pServiceRef)
		{
			// Service is available - let's invoke it
			GreetingService::Ptr pService = pServiceRef->castedInstance<GreetingService>();
			std::string greeting = pService->greeting();
			std::string msg("****** ");
			msg += greeting;
			msg += " ******";
			pContext->logger().information(msg);
		}
		else
		{
			// The service is not available
			pContext->logger().error("The GreetingService is not available.");
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(GreeterBundleActivator)
POCO_END_MANIFEST
