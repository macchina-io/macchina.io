//
// BundleManifestTest.cpp
//
// $Id: //poco/1.7/OSP/testsuite/src/BundleManifestTest.cpp#1 $
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "BundleManifestTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/OSP/BundleManifest.h"
#include <sstream>


#undef major
#undef minor


using Poco::OSP::BundleManifest;


BundleManifestTest::BundleManifestTest(const std::string& name): CppUnit::TestCase(name)
{
}


BundleManifestTest::~BundleManifestTest()
{
}


void BundleManifestTest::testBasicProperties1()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-Vendor: Applied Informatics\n"
		"Bundle-Copyright: (c) 2007, Applied Informatics\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->name() == "Sample Bundle");
	assert (pManifest->vendor() == "Applied Informatics");
	assert (pManifest->copyright() == "(c) 2007, Applied Informatics");
	assert (pManifest->symbolicName() == "com.appinf.osp.sample");
	assert (pManifest->version().major() == 1);
	assert (pManifest->version().minor() == 0);
	assert (pManifest->version().revision() == 2);
	assert (pManifest->version().designation() == "b1");
	assert (!pManifest->lazyStart());
}


void BundleManifestTest::testBasicProperties2()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: ${bundleName}\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.2.3\n"
		"Bundle-LazyStart: true\n"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->name() == "${bundleName}");
	assert (pManifest->vendor() == "");
	assert (pManifest->copyright() == "");
	assert (pManifest->symbolicName() == "com.appinf.osp.sample");
	assert (pManifest->version().major() == 1);
	assert (pManifest->version().minor() == 2);
	assert (pManifest->version().revision() == 3);
	assert (pManifest->version().designation() == "");
	assert (pManifest->activatorClass() == "");
	assert (pManifest->activatorLibrary() == "");
	assert (pManifest->requiredBundles().empty());
	assert (pManifest->lazyStart());
}


void BundleManifestTest::testActivator1()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Bundle-Activator: SampleActivator\n"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->activatorClass() == "SampleActivator");
	assert (pManifest->activatorLibrary() == "");
}


void BundleManifestTest::testActivator2()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Bundle-Activator: SampleActivator;library=SampleLib\n"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->activatorClass() == "SampleActivator");
	assert (pManifest->activatorLibrary() == "SampleLib");
}


void BundleManifestTest::testActivator3()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Bundle-Activator: NS::SampleActivator ; library = SampleLib \n"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->activatorClass() == "NS::SampleActivator");
	assert (pManifest->activatorLibrary() == "SampleLib");
}


void BundleManifestTest::testRequired1()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Require-Bundle: com.appinf.osp.bundle1"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->requiredBundles().size() == 1);
	assert (pManifest->requiredBundles()[0].symbolicName == "com.appinf.osp.bundle1");
	assert (pManifest->requiredBundles()[0].versions.isEmpty());
}


void BundleManifestTest::testRequired2()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Require-Bundle: com.appinf.osp.bundle1;bundle-version=1.1"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->requiredBundles().size() == 1);
	assert (pManifest->requiredBundles()[0].symbolicName == "com.appinf.osp.bundle1");
	assert (pManifest->requiredBundles()[0].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().minor() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().revision() == 0);
	assert (pManifest->requiredBundles()[0].versions.upperBound() == pManifest->requiredBundles()[0].versions.lowerBound());
	assert (pManifest->requiredBundles()[0].versions.includeLower());
	assert (pManifest->requiredBundles()[0].versions.includeUpper());
}


void BundleManifestTest::testRequired3()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Require-Bundle: com.appinf.osp.bundle1 ; bundle-version = 1.1"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->requiredBundles().size() == 1);
	assert (pManifest->requiredBundles()[0].symbolicName == "com.appinf.osp.bundle1");
	assert (pManifest->requiredBundles()[0].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().minor() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().revision() == 0);
	assert (pManifest->requiredBundles()[0].versions.upperBound() == pManifest->requiredBundles()[0].versions.lowerBound());
	assert (pManifest->requiredBundles()[0].versions.includeLower());
	assert (pManifest->requiredBundles()[0].versions.includeUpper());
}


void BundleManifestTest::testRequired4()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Require-Bundle: com.appinf.osp.bundle1, com.appinf.osp.bundle2; bundle-version=1.2.3"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->requiredBundles().size() == 2);
	assert (pManifest->requiredBundles()[0].symbolicName == "com.appinf.osp.bundle1");
	assert (pManifest->requiredBundles()[0].versions.isEmpty());
	assert (pManifest->requiredBundles()[1].symbolicName == "com.appinf.osp.bundle2");
	assert (pManifest->requiredBundles()[1].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().minor() == 2);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().revision() == 3);
	assert (pManifest->requiredBundles()[1].versions.upperBound() == pManifest->requiredBundles()[1].versions.lowerBound());
	assert (pManifest->requiredBundles()[1].versions.includeLower());
	assert (pManifest->requiredBundles()[1].versions.includeUpper());
}


void BundleManifestTest::testRequired5()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Require-Bundle: com.appinf.osp.bundle1, com.appinf.osp.bundle2; bundle-version=1.2.3, com.appinf.osp.bundle3"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->requiredBundles().size() == 3);
	assert (pManifest->requiredBundles()[0].symbolicName == "com.appinf.osp.bundle1");
	assert (pManifest->requiredBundles()[0].versions.isEmpty());
	assert (pManifest->requiredBundles()[1].symbolicName == "com.appinf.osp.bundle2");
	assert (pManifest->requiredBundles()[1].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().minor() == 2);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().revision() == 3);
	assert (pManifest->requiredBundles()[1].versions.upperBound() == pManifest->requiredBundles()[1].versions.lowerBound());
	assert (pManifest->requiredBundles()[1].versions.includeLower());
	assert (pManifest->requiredBundles()[1].versions.includeUpper());
	assert (pManifest->requiredBundles()[2].symbolicName == "com.appinf.osp.bundle3");
	assert (pManifest->requiredBundles()[2].versions.isEmpty());
}


void BundleManifestTest::testRequired6()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Require-Bundle: com.appinf.osp.bundle1;bundle-version=[1.1,1.2), com.appinf.osp.bundle2;bundle-version=1.2"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->requiredBundles().size() == 2);
	assert (pManifest->requiredBundles()[0].symbolicName == "com.appinf.osp.bundle1");
	assert (pManifest->requiredBundles()[0].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().minor() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().revision() == 0);
	assert (pManifest->requiredBundles()[0].versions.upperBound().major() == 1);
	assert (pManifest->requiredBundles()[0].versions.upperBound().minor() == 2);
	assert (pManifest->requiredBundles()[0].versions.upperBound().revision() == 0);
	assert (pManifest->requiredBundles()[0].versions.includeLower());
	assert (!pManifest->requiredBundles()[0].versions.includeUpper());

	assert (pManifest->requiredBundles()[1].symbolicName == "com.appinf.osp.bundle2");
	assert (pManifest->requiredBundles()[1].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().minor() == 2);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().revision() == 0);
	assert (pManifest->requiredBundles()[1].versions.upperBound() == pManifest->requiredBundles()[1].versions.lowerBound());
	assert (pManifest->requiredBundles()[1].versions.includeLower());
	assert (pManifest->requiredBundles()[1].versions.includeUpper());
}


void BundleManifestTest::testRequired7()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Require-Bundle: com.appinf.osp.bundle1;bundle-version=(1.1,1.2], com.appinf.osp.bundle2;bundle-version=1.2"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->requiredBundles().size() == 2);
	assert (pManifest->requiredBundles()[0].symbolicName == "com.appinf.osp.bundle1");
	assert (pManifest->requiredBundles()[0].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().minor() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().revision() == 0);
	assert (pManifest->requiredBundles()[0].versions.upperBound().major() == 1);
	assert (pManifest->requiredBundles()[0].versions.upperBound().minor() == 2);
	assert (pManifest->requiredBundles()[0].versions.upperBound().revision() == 0);
	assert (!pManifest->requiredBundles()[0].versions.includeLower());
	assert (pManifest->requiredBundles()[0].versions.includeUpper());

	assert (pManifest->requiredBundles()[1].symbolicName == "com.appinf.osp.bundle2");
	assert (pManifest->requiredBundles()[1].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().minor() == 2);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().revision() == 0);
	assert (pManifest->requiredBundles()[1].versions.upperBound() == pManifest->requiredBundles()[1].versions.lowerBound());
	assert (pManifest->requiredBundles()[1].versions.includeLower());
	assert (pManifest->requiredBundles()[1].versions.includeUpper());
}


void BundleManifestTest::testRequired8()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Require-Bundle: com.appinf.osp.bundle1;bundle-version=(1.1,1.2), com.appinf.osp.bundle2;bundle-version=1.2"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->requiredBundles().size() == 2);
	assert (pManifest->requiredBundles()[0].symbolicName == "com.appinf.osp.bundle1");
	assert (pManifest->requiredBundles()[0].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().minor() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().revision() == 0);
	assert (pManifest->requiredBundles()[0].versions.upperBound().major() == 1);
	assert (pManifest->requiredBundles()[0].versions.upperBound().minor() == 2);
	assert (pManifest->requiredBundles()[0].versions.upperBound().revision() == 0);
	assert (!pManifest->requiredBundles()[0].versions.includeLower());
	assert (!pManifest->requiredBundles()[0].versions.includeUpper());

	assert (pManifest->requiredBundles()[1].symbolicName == "com.appinf.osp.bundle2");
	assert (pManifest->requiredBundles()[1].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().minor() == 2);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().revision() == 0);
	assert (pManifest->requiredBundles()[1].versions.upperBound() == pManifest->requiredBundles()[1].versions.lowerBound());
	assert (pManifest->requiredBundles()[1].versions.includeLower());
	assert (pManifest->requiredBundles()[1].versions.includeUpper());
}


void BundleManifestTest::testRequired9()
{
	std::string manifestData(
		"Manifest-Version: 1.0\n"
		"Bundle-Name: Sample Bundle\n"
		"Bundle-SymbolicName: com.appinf.osp.sample\n"
		"Bundle-Version: 1.0.2-b1\n"
		"Require-Bundle: com.appinf.osp.bundle1 ; bundle-version = ( 1.1 , 1.2 ) , com.appinf.osp.bundle2   ;bundle-version = 1.2"
	);
	std::istringstream istr(manifestData);
	BundleManifest::Ptr pManifest(new BundleManifest(istr));
	assert (pManifest->requiredBundles().size() == 2);
	assert (pManifest->requiredBundles()[0].symbolicName == "com.appinf.osp.bundle1");
	assert (pManifest->requiredBundles()[0].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().minor() == 1);
	assert (pManifest->requiredBundles()[0].versions.lowerBound().revision() == 0);
	assert (pManifest->requiredBundles()[0].versions.upperBound().major() == 1);
	assert (pManifest->requiredBundles()[0].versions.upperBound().minor() == 2);
	assert (pManifest->requiredBundles()[0].versions.upperBound().revision() == 0);
	assert (!pManifest->requiredBundles()[0].versions.includeLower());
	assert (!pManifest->requiredBundles()[0].versions.includeUpper());

	assert (pManifest->requiredBundles()[1].symbolicName == "com.appinf.osp.bundle2");
	assert (pManifest->requiredBundles()[1].versions.lowerBound().major() == 1);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().minor() == 2);
	assert (pManifest->requiredBundles()[1].versions.lowerBound().revision() == 0);
	assert (pManifest->requiredBundles()[1].versions.upperBound() == pManifest->requiredBundles()[1].versions.lowerBound());
	assert (pManifest->requiredBundles()[1].versions.includeLower());
	assert (pManifest->requiredBundles()[1].versions.includeUpper());
}


void BundleManifestTest::setUp()
{
}


void BundleManifestTest::tearDown()
{
}


CppUnit::Test* BundleManifestTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("BundleManifestTest");

	CppUnit_addTest(pSuite, BundleManifestTest, testBasicProperties1);
	CppUnit_addTest(pSuite, BundleManifestTest, testBasicProperties2);
	CppUnit_addTest(pSuite, BundleManifestTest, testActivator1);
	CppUnit_addTest(pSuite, BundleManifestTest, testActivator2);
	CppUnit_addTest(pSuite, BundleManifestTest, testActivator3);
	CppUnit_addTest(pSuite, BundleManifestTest, testRequired1);
	CppUnit_addTest(pSuite, BundleManifestTest, testRequired2);
	CppUnit_addTest(pSuite, BundleManifestTest, testRequired3);
	CppUnit_addTest(pSuite, BundleManifestTest, testRequired4);
	CppUnit_addTest(pSuite, BundleManifestTest, testRequired5);
	CppUnit_addTest(pSuite, BundleManifestTest, testRequired6);
	CppUnit_addTest(pSuite, BundleManifestTest, testRequired7);
	CppUnit_addTest(pSuite, BundleManifestTest, testRequired8);
	CppUnit_addTest(pSuite, BundleManifestTest, testRequired9);

	return pSuite;
}
