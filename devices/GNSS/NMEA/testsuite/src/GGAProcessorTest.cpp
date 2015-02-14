//
// GGAProcessorTest.cpp
//
// $Id$
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "GGAProcessorTest.h"
#include "IoT/GNSS/NMEA/SentenceDecoder.h"
#include "Poco/DateTime.h"
#include "Poco/Delegate.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"


using namespace Poco::Geo;
using namespace IoT::GNSS::NMEA;


GGAProcessorTest::GGAProcessorTest(const std::string& name): CppUnit::TestCase(name)
{
}


GGAProcessorTest::~GGAProcessorTest()
{
}


void GGAProcessorTest::testGGAProcessor()
{
	const std::string sentences = 
		"$GPRMC,111012.00,A,4724.5404000,N,00937.0524110,E,0.01,217.60,280213,0.00,E,D*05\r\n"
		"$GNGGA,111013.00,4724.5404000,N,00937.0524110,E,3,07,1.0,471.512,M,,,,*2C\r\n";
		
	GGAProcessor ggap;
	SentenceDecoder sc;
	sc.sentenceReceived += Poco::delegate(&ggap, &GGAProcessor::processSentence);
	ggap.ggaReceived += Poco::delegate(this, &GGAProcessorTest::onGGAReceived);
	
	sc.processBuffer(sentences.data(), sentences.size());
	
	Poco::DateTime dt(_gga.utc);
	assert (dt.hour() == 11);
	assert (dt.minute() == 10);
	assert (dt.second() == 13);
	
	assert (_gga.quality == GGAProcessor::FIX_PPS);
	assert (_gga.satellitesInView == 7);
	assert (_gga.hdop == 1.0);
	assertEquals (_gga.altitude, 471.512, 0.001);
			
	assertEquals (47.4090, _gga.position.latitude().degrees(), 0.0001);
	assertEquals (9.6175, _gga.position.longitude().degrees(), 0.0001);
}


void GGAProcessorTest::setUp()
{
}


void GGAProcessorTest::tearDown()
{
}


void GGAProcessorTest::onGGAReceived(const GGAProcessor::GGA& gga)
{
	_gga = gga;
}


CppUnit::Test* GGAProcessorTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("GGAProcessorTest");

	CppUnit_addTest(pSuite, GGAProcessorTest, testGGAProcessor);

	return pSuite;
}
