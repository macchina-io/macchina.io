//
// CoreBundleActivator.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;


class CoreBundleActivator: public BundleActivator
	/// The Core bundle is a data-only bundle; no BundleActivator
	/// is thus required.
	/// All the bundle provides is the OSP version information in the manifest.
	/// This gives other bundles the possibility to specify a dependency
	/// on a certain OSP version.
	/// 
	/// This is a dummy class, just to give the build
	/// system something to do. The resulting library is 
	/// actually not even included in the bundle.
{
public:
	CoreBundleActivator()
	{
	}
	
	~CoreBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
	}
		
	void stop(BundleContext::Ptr pContext)
	{
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(CoreBundleActivator)
POCO_END_MANIFEST
