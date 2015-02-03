//
// BundleManifestTest.h
//
// $Id: //poco/1.4/OSP/testsuite/src/BundleManifestTest.h#2 $
//
// Definition of the BundleManifestTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef BundleManifestTest_INCLUDED
#define BundleManifestTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"


class BundleManifestTest: public CppUnit::TestCase
{
public:
	BundleManifestTest(const std::string& name);
	~BundleManifestTest();

	void testBasicProperties1();
	void testBasicProperties2();
	void testActivator1();
	void testActivator2();
	void testActivator3();
	void testRequired1();
	void testRequired2();
	void testRequired3();
	void testRequired4();
	void testRequired5();
	void testRequired6();
	void testRequired7();
	void testRequired8();
	void testRequired9();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // BundleManifestTest_INCLUDED
