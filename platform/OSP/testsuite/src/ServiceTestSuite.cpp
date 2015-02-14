//
// ServiceTestSuite.cpp
//
// $Id: //poco/1.6/OSP/testsuite/src/ServiceTestSuite.cpp#1 $
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "ServiceTestSuite.h"
#include "ServiceRegistryTest.h"


CppUnit::Test* ServiceTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ServiceTestSuite");

	pSuite->addTest(ServiceRegistryTest::suite());

	return pSuite;
}
