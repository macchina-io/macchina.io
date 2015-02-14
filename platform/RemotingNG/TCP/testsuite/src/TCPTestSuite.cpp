//
// TCPTestSuite.cpp
//
// $Id: //poco/1.6/RemotingNG/TCP/testsuite/src/TCPTestSuite.cpp#1 $
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
