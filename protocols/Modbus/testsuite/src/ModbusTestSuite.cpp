//
// ModbusTestSuite.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "ModbusTestSuite.h"
#include "PDUWriterTest.h"
#include "PDUReaderTest.h"
#include "ModbusMasterTest.h"


CppUnit::Test* ModbusTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ModbusTestSuite");

	pSuite->addTest(PDUWriterTest::suite());
	pSuite->addTest(PDUReaderTest::suite());
	pSuite->addTest(ModbusMasterTest::suite());

	return pSuite;
}
