//
// Extensible.cpp
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/AutoPtr.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::ServiceRef;
using Poco::OSP::ExtensionPoint;
using Poco::OSP::ExtensionPointService;
using Poco::AutoPtr;


class SampleExtensionPoint: public ExtensionPoint
{
public:
	SampleExtensionPoint(BundleContext::Ptr pContext):
		_pContext(pContext)
	{
	}
	
	void handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
	{
		std::string msg("Handling extension; bundle: ");
		msg += pBundle->symbolicName();
		msg += "; message: ";
		msg += pExtensionElem->getAttribute("message");
		_pContext->logger().information(msg);
	}

private:
	BundleContext::Ptr _pContext;
};


class ExtensibleBundleActivator: public BundleActivator
	/// The BundleActivator for the Extensible.
	/// Registes the Extensible with the Service Registry.
{
public:
	ExtensibleBundleActivator()
	{
	}
	
	~ExtensibleBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		// find ExtensionPointService using the Service Registry
		ServiceRef::Ptr pXPSRef = pContext->registry().findByName("osp.core.xp");
		if (pXPSRef)
		{
			// ExtensionPointService is available
			AutoPtr<ExtensionPointService> pXPS = pXPSRef->castedInstance<ExtensionPointService>();
			
			// Create an ExtensionPoint
			ExtensionPoint::Ptr pXP = new SampleExtensionPoint(pContext);
			
			// Register ExtensionPoint
			pXPS->registerExtensionPoint(pContext->thisBundle(), "com.appinf.sample.xp", pXP);
		}
		else
		{
			// The service is not available
			pContext->logger().error("The ExtensionPointService is not available.");
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		// Nothing to do here.
		// The ExtensionPointService will automatically unregister our
		// extension point when we are stopped.
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(ExtensibleBundleActivator)
POCO_END_MANIFEST
