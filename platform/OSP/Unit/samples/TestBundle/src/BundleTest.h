//
// CoreTest.h
//
// Definition of the BundleTest class.
//
// Copyright (c) 2011-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef BundleTest_INCLUDED
#define BundleTest_INCLUDED


#include "Poco/OSP/Unit/TestCase.h"


class BundleTest: public Poco::OSP::Unit::TestCase
{
public:
	BundleTest(const std::string& name);
	~BundleTest();

	void testSetUp();
	void testSuccess();
	void testError();
	void testFailure();
	void testTornDown();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	bool _setUp;
	bool _tornDown;
};


#endif // BundleTest_INCLUDED
