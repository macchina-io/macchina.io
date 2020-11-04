//
// OSPCoreTestSuite.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "OSPCoreTestSuite.h"
#include "VersionTest.h"


CppUnit::Test* OSPCoreTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("OSPCoreTestSuite");

	pSuite->addTest(VersionTest::suite());

	return pSuite;
}
