//
// Extensible.cpp
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
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/ExtensionPointService.h"
#include "Poco/OSP/Unit/TestFactory.h"
#include "Poco/OSP/Unit/LogTestResult.h"
#include "Poco/OSP/Unit/TestCase.h"
#include "Poco/AutoPtr.h"
#include "Poco/ClassLibrary.h"
#include "Poco/LogStream.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::ServiceRef;
using Poco::OSP::ExtensionPoint;
using Poco::OSP::ExtensionPointService;
using Poco::OSP::Unit::TestFactory;
using Poco::OSP::Unit::TestCase;
using Poco::OSP::Unit::LogTestResult;
using Poco::AutoPtr;
using Poco::Logger;
using Poco::LogStream;


class TestExtensionPoint: public ExtensionPoint
{
public:
	TestExtensionPoint(BundleContext::Ptr pContext):
		_pContext(pContext)
	{
	}
	
	void handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem)
	{
		std::string name = pBundle->name();
		std::string symbolicName = pBundle->symbolicName();
		std::string msg(Poco::format("Running tests in bundle \"%s\" (%s)...", name, symbolicName));

		_pContext->logger().information(std::string(msg.size(), '='));
		_pContext->logger().information(msg);
		_pContext->logger().information(std::string(msg.size(), '-'));
		
		BundleContext::Ptr pContext = _pContext->contextForBundle(pBundle);
		TestCase::resetContext(pContext);

		LogStream logStream(pContext->logger());
		TestFactory::TestVec tests = TestFactory::instance().get(name);
		TestFactory::TestVec::iterator it = tests.begin();
		TestFactory::TestVec::iterator end = tests.end();
		int nTests = 0;
		int nErrors = 0;
		int nFailures = 0;
		for (; it != end; ++it)
		{
			LogTestResult ltr(logStream);
			(*it)->run(&ltr);
			ltr.print(logStream);
			nTests += ltr.runTests();
			nErrors += ltr.testErrors();
			nFailures += ltr.testFailures();
		}
		
		if (nErrors > 0)
		{
			if (nErrors == 1)
				_pContext->logger().error("There was 1 error in bundle \"%s\" (%s).", name, symbolicName);
			else
				_pContext->logger().error("There were %d errors in bundle \"%s\" (%s).", nErrors, name, symbolicName);
		}

		if (nFailures > 0)
		{
			if (nFailures == 1)
				_pContext->logger().error("There was 1 failure in bundle \"%s\" (%s).", name, symbolicName);
			else
				_pContext->logger().error("There were %d failures in bundle \"%s\" (%s).", nFailures, name, symbolicName);
		}
		
		if (nTests == 1)
			msg = Poco::format("Ran 1 test in bundle \"%s\" (%s).", name, symbolicName);
		else
			msg = Poco::format("Ran %d tests in bundle \"%s\" (%s).", nTests, name, symbolicName);

		_pContext->logger().information(std::string(msg.size(), '-'));
		_pContext->logger().information(msg);
		_pContext->logger().information(std::string(msg.size(), '='));

	}

private:
	BundleContext::Ptr _pContext;
};


class TestRunnerBundleActivator: public BundleActivator
	/// The BundleActivator for the Extensible.
	/// Registes the Extensible with the Service Registry.
{
public:
	TestRunnerBundleActivator()
	{
	}
	
	~TestRunnerBundleActivator()
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
			ExtensionPoint::Ptr pXP = new TestExtensionPoint(pContext);
			
			// Register ExtensionPoint
			pXPS->registerExtensionPoint(pContext->thisBundle(), "com.appinf.osp.unit.test", pXP);
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
	POCO_EXPORT_CLASS(TestRunnerBundleActivator)
POCO_END_MANIFEST
