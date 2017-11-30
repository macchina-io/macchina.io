//
// PDUWriterTest.h
//
// Definition of the PDUWriterTest class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef PDUWriterTest_INCLUDED
#define PDUWriterTest_INCLUDED


#include "CppUnit/TestCase.h"


class PDUWriterTest: public CppUnit::TestCase
{
public:
	PDUWriterTest(const std::string& name);
	~PDUWriterTest();
	
	enum
	{
		MODBUS_MAX_PDU_SIZE = 32
	};
	
	void testGenericMessage();
	void testReadCoilsRequest();
	void testReadDiscreteInputsRequest();
	void testReadHoldingRegistersRequest();
	void testReadInputRegistersRequest();
	void testWriteSingleCoilRequest();
	void testWriteSingleRegisterRequest();
	void testReadExceptionStatusRequest();
	void testWriteMultipleCoilsRequest();
	void testWriteMultipleRegistersRequest();
	void testMaskWriteRegisterRequest();
	void testReadWriteMultipleRegistersRequest();
	void testReadFIFOQueueRequest();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // PDUWriterTest_INCLUDED
