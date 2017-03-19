//
// PDUReaderTest.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "PDUReaderTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Modbus/PDUReader.h"
#include "Poco/BinaryReader.h"
#include "Poco/MemoryStream.h"


using namespace IoT::Modbus;


PDUReaderTest::PDUReaderTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


PDUReaderTest::~PDUReaderTest()
{
}


void PDUReaderTest::testGenericMessage()
{
	char buffer[] = {
		0x01,
		0x02,
		0x10,
		0x11
	};
	
	Poco::MemoryInputStream istr(buffer, sizeof(buffer));
	Poco::BinaryReader binaryReader(istr, Poco::BinaryReader::BIG_ENDIAN_BYTE_ORDER);
	
	PDUReader pduReader(binaryReader);

	GenericMessage message;
	pduReader.read(message);
	
	assert (message.slaveOrUnitAddress == 0x01);
	assert (message.functionCode == 0x02);
	assert (message.data.size() == 2);	
	assert (message.data[0] == 0x10);
	assert (message.data[1] == 0x11);	
}


void PDUReaderTest::testModbusExceptionMessage()
{
}


void PDUReaderTest::setUp()
{
}


void PDUReaderTest::tearDown()
{
}


CppUnit::Test* PDUReaderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("PDUReaderTest");

	CppUnit_addTest(pSuite, PDUReaderTest, testGenericMessage);
	CppUnit_addTest(pSuite, PDUReaderTest, testModbusExceptionMessage);
	// TODO

	return pSuite;
}
