//
// TestBundleSuite.cpp
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "TestBundleSuite.h"
#include "BundleTest.h"


CppUnit::Test* TestBundleSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TestBundleSuite");

	pSuite->addTest(BundleTest::suite());

	return pSuite;
}
