//
// ModbusMasterTest.h
//
// Definition of the ModbusMasterTest class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef ModbusMasterTest_INCLUDED
#define ModbusMasterTest_INCLUDED


#include "CppUnit/TestCase.h"


class ModbusMasterTest: public CppUnit::TestCase
{
public:
	ModbusMasterTest(const std::string& name);
	~ModbusMasterTest();
	
	void testSomething();
	// ...

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // ModbusMasterTest_INCLUDED
