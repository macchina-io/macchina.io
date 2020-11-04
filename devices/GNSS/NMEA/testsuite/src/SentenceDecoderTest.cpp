//
// SentenceDecoderTest.cpp
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "SentenceDecoderTest.h"
#include "IoT/GNSS/NMEA/SentenceDecoder.h"
#include "Poco/Delegate.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"


using namespace IoT::GNSS::NMEA;


SentenceDecoderTest::SentenceDecoderTest(const std::string& name): CppUnit::TestCase(name)
{
}


SentenceDecoderTest::~SentenceDecoderTest()
{
}


void SentenceDecoderTest::testValidSentences()
{
	const std::string sentences = 
		"$GPGGA,163026.489,,,,,0,00,,,M,0.0,M,,0000*53\r\n"
		"$GPGSA,A,3,15,24,09,17,05,,,,,,,,4.3,2.6,3.4*3E\r\n"
		"$GPRMC,163030.186,A,4729.6845,N,00941.3582,E,1.30,213.65,100313,,,A*60\r\n";
	
	SentenceDecoder sc;
	sc.sentenceReceived += Poco::delegate(this, &SentenceDecoderTest::onSentenceReceived);
	
	sc.processBuffer(sentences.data(), sentences.size());
	
	assert (_sentences.size() == 3);
	
	assert (_sentences[0].talkerId() == "GP");
	assert (_sentences[0].type() == "GGA");
	assert (_sentences[0].size() == 14);
	assert (_sentences[0][0] == "163026.489");
	assert (_sentences[0][1] == "");
	assert (_sentences[0][2] == "");
	assert (_sentences[0][3] == "");
	assert (_sentences[0][4] == "");
	assert (_sentences[0][5] == "0");
	assert (_sentences[0][6] == "00");
	assert (_sentences[0][7] == "");
	assert (_sentences[0][8] == "");
	assert (_sentences[0][9] == "M");
	assert (_sentences[0][10] == "0.0");
	assert (_sentences[0][11] == "M");
	assert (_sentences[0][12] == "");
	assert (_sentences[0][13] == "0000");

	assert (_sentences[1].talkerId() == "GP");
	assert (_sentences[1].type() == "GSA");
	assert (_sentences[1].size() == 17);
	assert (_sentences[1][0] == "A");
	assert (_sentences[1][1] == "3");
	assert (_sentences[1][2] == "15");
	assert (_sentences[1][3] == "24");
	assert (_sentences[1][4] == "09");
	assert (_sentences[1][5] == "17");
	assert (_sentences[1][6] == "05");
	assert (_sentences[1][7] == "");
	assert (_sentences[1][8] == "");
	assert (_sentences[1][9] == "");
	assert (_sentences[1][10] == "");
	assert (_sentences[1][11] == "");
	assert (_sentences[1][12] == "");
	assert (_sentences[1][13] == "");
	assert (_sentences[1][14] == "4.3");
	assert (_sentences[1][15] == "2.6");
	assert (_sentences[1][16] == "3.4");

	assert (_sentences[2].talkerId() == "GP");
	assert (_sentences[2].type() == "RMC");
	assert (_sentences[2].size() == 12);
	assert (_sentences[2][0] == "163030.186");
	assert (_sentences[2][1] == "A");
	assert (_sentences[2][2] == "4729.6845");
	assert (_sentences[2][3] == "N");
	assert (_sentences[2][4] == "00941.3582");
	assert (_sentences[2][5] == "E");
	assert (_sentences[2][6] == "1.30");
	assert (_sentences[2][7] == "213.65");
	assert (_sentences[2][8] == "100313");
	assert (_sentences[2][9] == "");
	assert (_sentences[2][10] == "");
	assert (_sentences[2][11] == "A");
}


void SentenceDecoderTest::testInvalidSentences()
{
	const std::string sentences = 
		"asdflkji$adfkj\r\n\r\n" // gargabe
		"$GPRMC,163029.486,V,,,,,,,100313,,,N*49\r\n" // bad checksum
		"$GPGGA,163026.489,,,,,0,00,,,M,0.0,M,,0000*53\r\n" // ok
		"\r\n" 
		"$GPGGA,163029.486,,,,,0\r\n" // incomplete
		"$GPGSA,A,3,15,24,09,17,05,,,,,,,,4.3,2.6,3.4*3E\r\n" // ok
		"$GPRMC,163030.186,A,4729.6845,N,00941.3582,E,1.30,213.65,100313,,,A*60\r\n"; // ok
	
	SentenceDecoder sc;
	sc.sentenceReceived += Poco::delegate(this, &SentenceDecoderTest::onSentenceReceived);
	
	sc.processBuffer(sentences.data(), sentences.size());
	
	assert (_sentences.size() == 3);
	
	assert (_sentences[0].talkerId() == "GP");
	assert (_sentences[0].type() == "GGA");
	assert (_sentences[0].size() == 14);
	assert (_sentences[0][0] == "163026.489");
	assert (_sentences[0][1] == "");
	assert (_sentences[0][2] == "");
	assert (_sentences[0][3] == "");
	assert (_sentences[0][4] == "");
	assert (_sentences[0][5] == "0");
	assert (_sentences[0][6] == "00");
	assert (_sentences[0][7] == "");
	assert (_sentences[0][8] == "");
	assert (_sentences[0][9] == "M");
	assert (_sentences[0][10] == "0.0");
	assert (_sentences[0][11] == "M");
	assert (_sentences[0][12] == "");
	assert (_sentences[0][13] == "0000");

	assert (_sentences[1].talkerId() == "GP");
	assert (_sentences[1].type() == "GSA");
	assert (_sentences[1].size() == 17);
	assert (_sentences[1][0] == "A");
	assert (_sentences[1][1] == "3");
	assert (_sentences[1][2] == "15");
	assert (_sentences[1][3] == "24");
	assert (_sentences[1][4] == "09");
	assert (_sentences[1][5] == "17");
	assert (_sentences[1][6] == "05");
	assert (_sentences[1][7] == "");
	assert (_sentences[1][8] == "");
	assert (_sentences[1][9] == "");
	assert (_sentences[1][10] == "");
	assert (_sentences[1][11] == "");
	assert (_sentences[1][12] == "");
	assert (_sentences[1][13] == "");
	assert (_sentences[1][14] == "4.3");
	assert (_sentences[1][15] == "2.6");
	assert (_sentences[1][16] == "3.4");

	assert (_sentences[2].talkerId() == "GP");
	assert (_sentences[2].type() == "RMC");
	assert (_sentences[2].size() == 12);
	assert (_sentences[2][0] == "163030.186");
	assert (_sentences[2][1] == "A");
	assert (_sentences[2][2] == "4729.6845");
	assert (_sentences[2][3] == "N");
	assert (_sentences[2][4] == "00941.3582");
	assert (_sentences[2][5] == "E");
	assert (_sentences[2][6] == "1.30");
	assert (_sentences[2][7] == "213.65");
	assert (_sentences[2][8] == "100313");
	assert (_sentences[2][9] == "");
	assert (_sentences[2][10] == "");
	assert (_sentences[2][11] == "A");
}


void SentenceDecoderTest::setUp()
{
	_sentences.clear();
}


void SentenceDecoderTest::tearDown()
{
}


void SentenceDecoderTest::onSentenceReceived(const IoT::GNSS::NMEA::Sentence& sentence)
{
	_sentences.push_back(sentence);
}


CppUnit::Test* SentenceDecoderTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SentenceDecoderTest");

	CppUnit_addTest(pSuite, SentenceDecoderTest, testValidSentences);
	CppUnit_addTest(pSuite, SentenceDecoderTest, testInvalidSentences);

	return pSuite;
}
