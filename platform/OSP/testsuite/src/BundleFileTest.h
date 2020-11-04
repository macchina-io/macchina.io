//
// BundleFileTest.h
//
// Definition of the BundleFileTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef BundleFileTest_INCLUDED
#define BundleFileTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"


class BundleFileTest: public CppUnit::TestCase
{
public:
	BundleFileTest(const std::string& name);
	~BundleFileTest();

	void testResource();
	void testDirectory();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // BundleFileTest_INCLUDED
