//
// RMCProcessorTest.h
//
// $Id$
//
// Definition of the RMCProcessorTest class.
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RMCProcessorTest_INCLUDED
#define RMCProcessorTest_INCLUDED


#include "Poco/Geo/Geo.h"
#include "CppUnit/TestCase.h"
#include "IoT/GNSS/NMEA/RMCProcessor.h"


class RMCProcessorTest: public CppUnit::TestCase
{
public:
	RMCProcessorTest(const std::string& name);
	~RMCProcessorTest();

	void testRMCProcessor();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

protected:
	void onRMCReceived(const IoT::GNSS::NMEA::RMCProcessor::RMC& rmc);
	
private:
	IoT::GNSS::NMEA::RMCProcessor::RMC _rmc;
};


#endif // RMCProcessorTest_INCLUDED
