//
// ServiceTestSuite.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "ServiceTestSuite.h"
#include "ServiceRegistryTest.h"
#include "ServiceListenerTest.h"


CppUnit::Test* ServiceTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ServiceTestSuite");

	pSuite->addTest(ServiceRegistryTest::suite());
	pSuite->addTest(ServiceListenerTest::suite());

	return pSuite;
}

