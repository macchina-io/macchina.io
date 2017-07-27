//
// TimingNodesTest.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "TimingNodesTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Dataflow/Engine/TimingNodes.h"
#include "IoT/Dataflow/Engine/Inlet.h"
#include "IoT/Dataflow/Engine/Outlet.h"
#include "IoT/Dataflow/Engine/DataFlow.h"
#include "TestHelper.h"

using namespace IoT::Dataflow::Engine;


TimingNodesTest::TimingNodesTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


TimingNodesTest::~TimingNodesTest()
{
}

void TimingNodesTest::testStopwatch()
{
	try
	{
		Node::Ptr pNode = new Stopwatch<double>("stopwatch");

		int timeToSleep = 1000; //milliseconds
		Outlet<bool> trigger("trigger");
		Inlet<Poco::Int64> elapsed("elapsed");
		pNode->outlet("elapsed")->connect(elapsed);
		pNode->inlet("trigger")->connect(trigger);
		trigger.set(true);
		Sleep(timeToSleep);
		trigger.set(false);

		std::cerr << "elapsed=" << elapsed.value() << " ("  << elapsed.value()/1000 << " milliseconds)" << std::endl;
		assert (elapsed.value() - timeToSleep*1000 < 10000);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void TimingNodesTest::testTick()
{
	//TODO
}

void TimingNodesTest::setUp()
{
}


void TimingNodesTest::tearDown()
{
}


CppUnit::Test* TimingNodesTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TimingNodesTest");

	CppUnit_addTest(pSuite, TimingNodesTest, testStopwatch);
	CppUnit_addTest(pSuite, TimingNodesTest, testTick);
	return pSuite;
}
