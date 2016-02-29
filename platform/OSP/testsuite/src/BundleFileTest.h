//
// BundleFileTest.h
//
// $Id: //poco/1.7/OSP/testsuite/src/BundleFileTest.h#1 $
//
// Definition of the BundleFileTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
