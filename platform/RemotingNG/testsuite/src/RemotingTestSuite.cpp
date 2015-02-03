//
// RemotingTestSuite.cpp
//
// $Id: //poco/1.4/RemotingNG/testsuite/src/RemotingTestSuite.cpp#2 $
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "RemotingTestSuite.h"
#include "RemotingTest.h"


CppUnit::Test* RemotingTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("RemotingTestSuite");

	pSuite->addTest(RemotingTest::suite());

	return pSuite;
}
