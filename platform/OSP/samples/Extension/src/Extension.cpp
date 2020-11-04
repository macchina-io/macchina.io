//
// Extension.cpp
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;


class DummyBundleActivator: public BundleActivator
	/// This sample is a data-only bundle; no BundleActivator
	/// is thus required.
	/// The complete bundle is defined in the extensions.xml file.
	/// 
	/// This is a dummy class, just to give the build
	/// system something to do. The resulting library is 
	/// actually not included in the bundle.
{
public:
	DummyBundleActivator()
	{
	}
	
	~DummyBundleActivator()
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
	POCO_EXPORT_CLASS(DummyBundleActivator)
POCO_END_MANIFEST
