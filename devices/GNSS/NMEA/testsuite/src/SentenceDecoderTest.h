//
// SentenceDecoderTest.h
//
// $Id$
//
// Definition of the SentenceDecoderTest class.
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef SentenceDecoderTest_INCLUDED
#define SentenceDecoderTest_INCLUDED


#include "IoT/GNSS/NMEA/NMEA.h"
#include "IoT/GNSS/NMEA/Sentence.h"
#include "CppUnit/TestCase.h"


class SentenceDecoderTest: public CppUnit::TestCase
{
public:
	SentenceDecoderTest(const std::string& name);
	~SentenceDecoderTest();

	void testValidSentences();
	void testInvalidSentences();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

protected:
	void onSentenceReceived(const IoT::GNSS::NMEA::Sentence& sentence);

private:
	std::vector<IoT::GNSS::NMEA::Sentence> _sentences;
};


#endif // SentenceDecoderTest_INCLUDED
