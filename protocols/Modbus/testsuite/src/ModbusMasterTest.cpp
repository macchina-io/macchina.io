//
// ModbusMasterTest.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "ModbusMasterTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Modbus/PDUReader.h"
#include "Poco/BinaryReader.h"
#include "Poco/MemoryStream.h"


using namespace IoT::Modbus;


ModbusMasterTest::ModbusMasterTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


ModbusMasterTest::~ModbusMasterTest()
{
}


void ModbusMasterTest::testSomething()
{
}


void ModbusMasterTest::setUp()
{
}


void ModbusMasterTest::tearDown()
{
}


CppUnit::Test* ModbusMasterTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ModbusMasterTest");

	CppUnit_addTest(pSuite, ModbusMasterTest, testSomething);
	// TODO

	return pSuite;
}
