//
// PDUWriterTest.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "PDUWriterTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Modbus/PDUWriter.h"
#include "Poco/BinaryWriter.h"
#include "Poco/MemoryStream.h"


using namespace IoT::Modbus;


PDUWriterTest::PDUWriterTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


PDUWriterTest::~PDUWriterTest()
{
}


void PDUWriterTest::testGenericMessage()
{
	char buffer[MODBUS_MAX_PDU_SIZE];
	Poco::MemoryOutputStream ostr(buffer, sizeof(buffer));
	Poco::BinaryWriter binaryWriter(ostr, Poco::BinaryWriter::BIG_ENDIAN_BYTE_ORDER);
	
	GenericMessage message;
	message.slaveOrUnitAddress = 0x01;
	message.functionCode = 0x02;
	message.data.push_back(0x10);
	message.data.push_back(0x11);
	
	PDUWriter pduWriter(binaryWriter);
	pduWriter.write(message);
	
	assert (ostr.charsWritten() == 4);
	assert (buffer[0] == 0x01);
	assert (buffer[1] == 0x02);
	assert (buffer[2] == 0x10);
	assert (buffer[3] == 0x11);
}


void PDUWriterTest::testReadCoilsRequest()
{
}


void PDUWriterTest::setUp()
{
}


void PDUWriterTest::tearDown()
{
}


CppUnit::Test* PDUWriterTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("PDUWriterTest");

	CppUnit_addTest(pSuite, PDUWriterTest, testGenericMessage);
	CppUnit_addTest(pSuite, PDUWriterTest, testReadCoilsRequest);
	// TODO

	return pSuite;
}
