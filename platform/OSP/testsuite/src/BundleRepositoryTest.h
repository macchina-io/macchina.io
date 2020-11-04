//
// BundleRepositoryTest.h
//
// Definition of the BundleRepositoryTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef BundleRepositoryTest_INCLUDED
#define BundleRepositoryTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"


class BundleRepositoryTest: public CppUnit::TestCase
{
public:
	BundleRepositoryTest(const std::string& name);
	~BundleRepositoryTest();

	void testLoad();
	void testInstall();
	void testBundleFilterAcceptAll();
	void testBundleFilterRejectAll();
	void testBundleFilterAcceptOne();
	
	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

protected:
	std::string findBundleRepository();
};


#endif // BundleRepositoryTest_INCLUDED
