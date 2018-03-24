//
// BitStreamTest.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "BitStreamTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/CAN/BitStream.h"


using namespace IoT::CAN;


BitStreamTest::BitStreamTest(const std::string& name):
	CppUnit::TestCase(name)
{
}


BitStreamTest::~BitStreamTest()
{
}


void BitStreamTest::testBigEndianBits()
{
 	const char buffer[] = {0x0A, 0x05};

 	BigEndianBitStream s1(buffer, 3, 12);

 	assert (s1.readBit());
 	assert (!s1.readBit());
 	assert (s1.readBit());
 	assert (!s1.readBit());

 	assert (!s1.readBit());
 	assert (!s1.readBit());
 	assert (!s1.readBit());
 	assert (!s1.readBit());

 	assert (!s1.readBit());
 	assert (s1.readBit());
 	assert (!s1.readBit());
 	assert (s1.readBit());
}


void BitStreamTest::testBigEndianBytes()
{
 	const char buffer[] = {0x76, 0x54};

 	BigEndianBitStream s1(buffer, 7, 16);
 	char c = s1.readByte();
 	assert (c == 0x76);
 	c = s1.readByte();
 	assert (c == 0x54);

 	BigEndianBitStream s2(buffer, 3, 8);
 	c = s2.readByte();
 	assert (c == 0x65);
}


void BitStreamTest::testBigEndianSigned()
{
 	const char buffer[] = {0x0A, 0x33};

 	BigEndianBitStream s1(buffer, 3, 12);

 	Poco::Int32 n = s1.readSigned();
 	assert (n == 0xFFFFFA33);

 	BigEndianBitStream s2(buffer, 7, 16);

 	n = s2.readUnsigned();
 	assert (n == 0x0A33);
}


void BitStreamTest::testBigEndianUnsigned()
{
 	const char buffer[] = {0x5A, 0x30};

 	BigEndianBitStream s1(buffer, 7, 12);

 	Poco::UInt32 n = s1.readUnsigned();
 	assert (n == 0x05A3);

 	BigEndianBitStream s2(buffer, 7, 16);

 	n = s2.readUnsigned();
 	assert (n == 0x5A30);
}


void BitStreamTest::testBigEndianFloat()
{
	char buffer[4];
	const float pi = 3.1415926;
	const char* pPi = reinterpret_cast<const char*>(&pi);
#if defined(POCO_ARCH_BIG_ENDIAN)
	buffer[0] = pPi[0];
	buffer[1] = pPi[1];
	buffer[2] = pPi[2];
	buffer[3] = pPi[3];
#else
	buffer[0] = pPi[3];
	buffer[1] = pPi[2];
	buffer[2] = pPi[1];
	buffer[3] = pPi[0];
#endif

 	BigEndianBitStream s1(buffer, 7, 32);
	float f = s1.readFloat<float>();

	assert (f == pi);
}


void BitStreamTest::testLittleEndianBits()
{
 	const char buffer[] = {0x0A, 0x05};

 	LittleEndianBitStream s1(buffer, 0, 12);

 	assert (!s1.readBit());
 	assert (s1.readBit());
 	assert (!s1.readBit());
 	assert (s1.readBit());

 	assert (!s1.readBit());
 	assert (!s1.readBit());
 	assert (!s1.readBit());
 	assert (!s1.readBit());

 	assert (s1.readBit());
 	assert (!s1.readBit());
 	assert (s1.readBit());
 	assert (!s1.readBit());
}


void BitStreamTest::testLittleEndianBytes()
{
 	const char buffer[] = {0x76, 0x54};

 	LittleEndianBitStream s1(buffer, 0, 16);
 	char c = s1.readByte();
 	assert (c == 0x76);
 	c = s1.readByte();
 	assert (c == 0x54);

 	LittleEndianBitStream s2(buffer, 4, 8);
 	c = s2.readByte();
 	assert (c == 0x47);
}


void BitStreamTest::testLittleEndianSigned()
{
 	const char buffer[] = {0x33, 0x0A};

 	LittleEndianBitStream s1(buffer, 0, 12);

 	Poco::Int32 n = s1.readSigned();
 	assert (n == 0xFFFFFA33);

 	LittleEndianBitStream s2(buffer, 0, 16);

 	n = s2.readUnsigned();
 	assert (n == 0x0A33);
}


void BitStreamTest::testLittleEndianUnsigned()
{
 	const char buffer[] = {0x30, 0x5A};

 	LittleEndianBitStream s1(buffer, 4, 12);

 	Poco::UInt32 n = s1.readUnsigned();
 	assert (n == 0x05A3);

 	LittleEndianBitStream s2(buffer, 0, 16);

 	n = s2.readUnsigned();
 	assert (n == 0x5A30);
}


void BitStreamTest::testLittleEndianFloat()
{
	char buffer[4];
	const float pi = 3.1415926;
	const char* pPi = reinterpret_cast<const char*>(&pi);
#if defined(POCO_ARCH_BIG_ENDIAN)
	buffer[0] = pPi[3];
	buffer[1] = pPi[2];
	buffer[2] = pPi[1];
	buffer[3] = pPi[0];
#else
	buffer[0] = pPi[0];
	buffer[1] = pPi[1];
	buffer[2] = pPi[2];
	buffer[3] = pPi[3];
#endif

 	LittleEndianBitStream s1(buffer, 0, 32);
	float f = s1.readFloat<float>();

	assert (f == pi);
}


void BitStreamTest::setUp()
{
}


void BitStreamTest::tearDown()
{
}


CppUnit::Test* BitStreamTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("BitStreamTest");

	CppUnit_addTest(pSuite, BitStreamTest, testBigEndianBits);
	CppUnit_addTest(pSuite, BitStreamTest, testBigEndianBytes);
	CppUnit_addTest(pSuite, BitStreamTest, testBigEndianSigned);
	CppUnit_addTest(pSuite, BitStreamTest, testBigEndianUnsigned);
	CppUnit_addTest(pSuite, BitStreamTest, testBigEndianFloat);
	CppUnit_addTest(pSuite, BitStreamTest, testLittleEndianBits);
	CppUnit_addTest(pSuite, BitStreamTest, testLittleEndianBytes);
	CppUnit_addTest(pSuite, BitStreamTest, testLittleEndianSigned);
	CppUnit_addTest(pSuite, BitStreamTest, testLittleEndianUnsigned);
	CppUnit_addTest(pSuite, BitStreamTest, testLittleEndianFloat);

	return pSuite;
}
