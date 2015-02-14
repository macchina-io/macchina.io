//
// RMCProcessorTest.cpp
//
// $Id$
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "RMCProcessorTest.h"
#include "IoT/GNSS/NMEA/SentenceDecoder.h"
#include "Poco/DateTime.h"
#include "Poco/Delegate.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"


using namespace Poco::Geo;
using namespace IoT::GNSS::NMEA;


RMCProcessorTest::RMCProcessorTest(const std::string& name): CppUnit::TestCase(name)
{
}


RMCProcessorTest::~RMCProcessorTest()
{
}


void RMCProcessorTest::testRMCProcessor()
{
	const std::string sentences = 
		"$GPGGA,163026.489,,,,,0,00,,,M,0.0,M,,0000*53\r\n"
		"$GPGSA,A,3,15,24,09,17,05,,,,,,,,4.3,2.6,3.4*3E\r\n"
		"$GPRMC,163030.186,A,4729.6845,N,00941.3582,E,1.30,213.65,100313,,,A*60\r\n";
		
	RMCProcessor rmcp;
	SentenceDecoder sc;
	sc.sentenceReceived += Poco::delegate(&rmcp, &RMCProcessor::processSentence);
	rmcp.rmcReceived += Poco::delegate(this, &RMCProcessorTest::onRMCReceived);
	
	sc.processBuffer(sentences.data(), sentences.size());
	
	Poco::DateTime dt(2013, 03, 10, 16, 30, 30, 186);
	assert (_rmc.timestamp == dt.timestamp());
		
	assertEquals (47.4947, _rmc.position.latitude().degrees(), 0.0001);
	assertEquals (9.6893, _rmc.position.longitude().degrees(), 0.0001);
	
	assertEquals (213.65, _rmc.heading.degrees(), 0.001);
	assertEquals (1.3, _rmc.speed, 0.01);
}


void RMCProcessorTest::setUp()
{
}


void RMCProcessorTest::tearDown()
{
}


void RMCProcessorTest::onRMCReceived(const RMCProcessor::RMC& rmc)
{
	_rmc = rmc;
}


CppUnit::Test* RMCProcessorTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("RMCProcessorTest");

	CppUnit_addTest(pSuite, RMCProcessorTest, testRMCProcessor);

	return pSuite;
}
