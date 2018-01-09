//
// OSPCoreTestSuite.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "OSPCoreTestSuite.h"
#include "VersionTest.h"


CppUnit::Test* OSPCoreTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("OSPCoreTestSuite");

	pSuite->addTest(VersionTest::suite());

	return pSuite;
}
