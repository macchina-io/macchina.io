//
// TestBundleActivator.cpp
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/ClassLibrary.h"
#include "Poco/OSP/Unit/TestFactory.h"
#include "BundleTest.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Unit::TestFactory;


class TestBundleActivator: public BundleActivator
	/// TestBundle activator.
{
public:
	TestBundleActivator()
	{
	}
	
	~TestBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		TestFactory::instance().add(pContext->thisBundle()->name(), BundleTest::suite());
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		TestFactory::instance().remove(pContext->thisBundle()->name());
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(TestBundleActivator)
POCO_END_MANIFEST
