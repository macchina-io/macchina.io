//
// RemotingTestSuite.cpp
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "RemotingTestSuite.h"
#include "RemotingTest.h"
#include "EventFilterTest.h"


CppUnit::Test* RemotingTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("RemotingTestSuite");

	pSuite->addTest(RemotingTest::suite());
	pSuite->addTest(EventFilterTest::suite());

	return pSuite;
}
