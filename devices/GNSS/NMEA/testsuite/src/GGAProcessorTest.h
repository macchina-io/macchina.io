//
// GGAProcessorTest.h
//
// Definition of the GGAProcessorTest class.
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef GGAProcessorTest_INCLUDED
#define GGAProcessorTest_INCLUDED


#include "Poco/Geo/Geo.h"
#include "CppUnit/TestCase.h"
#include "IoT/GNSS/NMEA/GGAProcessor.h"


class GGAProcessorTest: public CppUnit::TestCase
{
public:
	GGAProcessorTest(const std::string& name);
	~GGAProcessorTest();

	void testGGAProcessor();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

protected:
	void onGGAReceived(const IoT::GNSS::NMEA::GGAProcessor::GGA& rmc);
	
private:
	IoT::GNSS::NMEA::GGAProcessor::GGA _gga;
};


#endif // GGAProcessorTest_INCLUDED
