//
// BundleDirectoryTest.h
//
// Definition of the BundleDirectoryTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef BundleDirectoryTest_INCLUDED
#define BundleDirectoryTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"


class BundleDirectoryTest: public CppUnit::TestCase
{
public:
	BundleDirectoryTest(const std::string& name);
	~BundleDirectoryTest();

	void testResource();
	void testDirectory();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // BundleDirectoryTest_INCLUDED
