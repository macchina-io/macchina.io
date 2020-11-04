//
// OSPUtilTestSuite.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "OSPUtilTestSuite.h"
#include "VersionRangeTest.h"
#include "PropertiesTest.h"
#include "QLParserTest.h"
#include "BundleStreamFactoryTest.h"


CppUnit::Test* OSPUtilTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("OSPUtilTestSuite");

	pSuite->addTest(VersionRangeTest::suite());
	pSuite->addTest(PropertiesTest::suite());
	pSuite->addTest(QLParserTest::suite());
	pSuite->addTest(BundleStreamFactoryTest::suite());

	return pSuite;
}
