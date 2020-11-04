//
// BundleTest.h
//
// Definition of the BundleTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef BundleTest_INCLUDED
#define BundleTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"
#include "Poco/OSP/BundleEvent.h"
#include <vector>


class BundleTest: public CppUnit::TestCase
{
public:
	BundleTest(const std::string& name);
	~BundleTest();

	void testLoadOne();
	void testVersionConflict();
	void testProperties();
	void testPropertiesLocalization1();
	void testPropertiesLocalization2();
	void testBundleFile();
	void testResolve();
	void testResolveModules();
	void testStart();
	void testActivator();
	void testStopAll();
	void testResolveStartStopUnloadAll();
	void testExtensionBundle();
	void testSealedBundle();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

protected:
	std::string findBundle(const std::string& name);

	void handleEvent(const void* sender, Poco::OSP::BundleEvent& event);
	void handleStartingEvent(const void* sender, Poco::OSP::BundleEvent& event);
	void handleStartedEvent(const void* sender, Poco::OSP::BundleEvent& event);
	void handleStoppingEvent(const void* sender, Poco::OSP::BundleEvent& event);
	void handleStoppedEvent(const void* sender, Poco::OSP::BundleEvent& event);

private:
	std::vector<Poco::OSP::BundleEvent> _events;
};


#endif // BundleTest_INCLUDED
