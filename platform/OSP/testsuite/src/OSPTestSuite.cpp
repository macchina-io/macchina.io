//
// OSPTestSuite.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "OSPTestSuite.h"
#include "OSPCoreTestSuite.h"
#include "OSPUtilTestSuite.h"
#include "OSPBundleTestSuite.h"
#include "ServiceTestSuite.h"


CppUnit::Test* OSPTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("OSPTestSuite");

	pSuite->addTest(OSPCoreTestSuite::suite());
	pSuite->addTest(OSPUtilTestSuite::suite());
	pSuite->addTest(OSPBundleTestSuite::suite());
	pSuite->addTest(ServiceTestSuite::suite());

	return pSuite;
}
