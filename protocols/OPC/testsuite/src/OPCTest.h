//
// OPCTest.h
//
// $Id: //poco/1.4/OPC/testsuite/src/OPCTest.h#1 $
//
// Definition of the OPCTest class.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef IoT_OPCTest_INCLUDED
#define IoT_OPCTest_INCLUDED


#include "IoT/OPC/OPC.h"
#include "CppUnit/TestCase.h"


class OPCTest: public CppUnit::TestCase
{
public:
	OPCTest(const std::string& name);
	~OPCTest();

	void testString();
	void testEmptyNodeID();
	void testNumericNodeID();
	void testStringNodeID();
	void testByteStringNodeID();
	void testGuidNodeID();

	void testDataTypeMember();

	void testDateTime();
	void testClient();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // IoT_OPCTest_INCLUDED
