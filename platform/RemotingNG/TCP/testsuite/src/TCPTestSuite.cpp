//
// TCPTestSuite.cpp
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "TCPTestSuite.h"
#include "RemotingTest.h"


CppUnit::Test* TCPTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TCPTestSuite");

	pSuite->addTest(RemotingTest::suite());
	pSuite->addTest(RemotingTestCompressed::suite());

	return pSuite;
}
