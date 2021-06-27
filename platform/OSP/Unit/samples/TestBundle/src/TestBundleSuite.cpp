//
// TestBundleSuite.cpp
//
// Copyright (c) 2011-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "TestBundleSuite.h"
#include "BundleTest.h"


CppUnit::Test* TestBundleSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TestBundleSuite");

	pSuite->addTest(BundleTest::suite());

	return pSuite;
}
