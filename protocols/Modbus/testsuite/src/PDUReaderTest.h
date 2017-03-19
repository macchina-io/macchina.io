//
// PDUReaderTest.h
//
// $Id$
//
// Definition of the PDUReaderTest class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef PDUReaderTest_INCLUDED
#define PDUReaderTest_INCLUDED


#include "CppUnit/TestCase.h"


class PDUReaderTest: public CppUnit::TestCase
{
public:
	PDUReaderTest(const std::string& name);
	~PDUReaderTest();
	
	void testGenericMessage();
	void testModbusExceptionMessage();
	// ...

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // PDUReaderTest_INCLUDED
