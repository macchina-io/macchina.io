//
// OSPBundleTestSuite.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "OSPBundleTestSuite.h"
#include "BundleDirectoryTest.h"
#include "BundleFileTest.h"
#include "BundleManifestTest.h"
#include "BundleTest.h"
#include "BundleRepositoryTest.h"


CppUnit::Test* OSPBundleTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("OSPBundleTestSuite");

	pSuite->addTest(BundleDirectoryTest::suite());
	pSuite->addTest(BundleFileTest::suite());
	pSuite->addTest(BundleManifestTest::suite());
	pSuite->addTest(BundleTest::suite());
	pSuite->addTest(BundleRepositoryTest::suite());

	return pSuite;
}
