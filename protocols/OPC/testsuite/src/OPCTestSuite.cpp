//
// OPCTestSuite.cpp
//
// $Id: //poco/1.4/OPC/testsuite/src/OPCTestSuite.cpp#1 $
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "OPCTestSuite.h"
#include "OPCTest.h"


CppUnit::Test* OPCTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("OPCTestSuite");

	pSuite->addTest(OPCTest::suite());

	return pSuite;
}
