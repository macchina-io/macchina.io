//
// OSPTestSuite.cpp
//
// $Id: //poco/1.7/OSP/testsuite/src/OSPTestSuite.cpp#1 $
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
