//
// BitStreamTest.h
//
// Definition of the BitStreamTest class.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef BitStreamTest_INCLUDED
#define BitStreamTest_INCLUDED


#include "CppUnit/TestCase.h"


class BitStreamTest: public CppUnit::TestCase
{
public:
	BitStreamTest(const std::string& name);
	~BitStreamTest();

	void testBigEndianBits();
	void testBigEndianBytes();
	void testBigEndianSigned();
	void testBigEndianUnsigned();
	void testBigEndianFloat();
	void testLittleEndianBits();
	void testLittleEndianBytes();
	void testLittleEndianSigned();
	void testLittleEndianUnsigned();
	void testLittleEndianFloat();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // BitStreamTest_INCLUDED
