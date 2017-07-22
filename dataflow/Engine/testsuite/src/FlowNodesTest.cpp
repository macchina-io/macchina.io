//
// FlowNodesTest.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "FlowNodesTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Dataflow/Engine/FlowNodes.h"
#include "IoT/Dataflow/Engine/DataFlow.h"

using namespace IoT::Dataflow::Engine;


FlowNodesTest::FlowNodesTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


FlowNodesTest::~FlowNodesTest()
{
}


#define MAX_ITERATIONS 5

void FlowNodesTest::testThreshold(bool exceed)
{
	try
	{
		Dataflow flow;
		Threshold<double>::Ptr pNode = new Threshold<double>("threshold", (exceed)?MAX_ITERATIONS/2:MAX_ITERATIONS);

		Inlet<bool> output("output");
		pNode->outlet("output")->connect(output);

		flow.testWithNode(pNode,MAX_ITERATIONS);

		std::cerr << "threshold=" << output.value() << std::endl;
		assert (output.value() == exceed);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void FlowNodesTest::testThresholdExceeded()
{
	return testThreshold(true);
}
void FlowNodesTest::testThresholdNotExceeded()
{
	return testThreshold(false);
}

void FlowNodesTest::testGate()
{
	try
	{
		Gate<bool>::Ptr pNode = new Gate<bool>("Gate");

		Inlet<bool> output("output");
		pNode->outlet("output")->connect(output);
		Outlet<bool> input("input");
		pNode->inlet("input")->connect(input);
		Outlet<bool> open("open");
		pNode->inlet("open")->connect(open);

		open.set(false); // gate is closed
		bool inputValue= true;
		input.set(inputValue);

		pNode->update(inputValue);
		std::cerr << "output=" << output.value() << std::endl;
		assert (output.value() != inputValue);

		open.set(true); // gate is open
		input.set(inputValue);
		pNode->update(inputValue);
		std::cerr << "output=" << output.value() << std::endl;
		assert (output.value() == inputValue);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void FlowNodesTest::testSplitter()
{
	try
	{
		Splitter<double>::Ptr pNode = new Splitter<double>("Splitter", 2);

		Outlet<double> input("input");
		pNode->inlet("input")->connect(input);

		Inlet<double> outlet0("outlet0");
		pNode->outlet("outlet0")->connect(outlet0);
		Inlet<double> outlet1("outlet1");
		pNode->outlet("outlet1")->connect(outlet1);

		double inputValue= 1.2345;
		input.set(inputValue);
		pNode->update(inputValue);

		std::cerr << "outlet0=" << outlet0.value() << std::endl;
		assert (outlet0.value() == inputValue);
		std::cerr << "outlet1=" << outlet1.value() << std::endl;
		assert (outlet1.value() == inputValue);

		inputValue= 6.7890;
		input.set(inputValue);
		pNode->update(inputValue);

		std::cerr << "outlet0=" << outlet0.value() << std::endl;
		assert (outlet0.value() == inputValue);
		std::cerr << "outlet1=" << outlet1.value() << std::endl;
		assert (outlet1.value() == inputValue);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void FlowNodesTest::testCast()
{
	testCast<double,int>(1.2345);
	testCast<int,bool>(0);
	testCast<double,bool>(1.2345);
	testCast<char,int>('A');
}

template <typename Tin, typename Tout>
void FlowNodesTest::testCast(Tin value)
{
	try
	{
		Cast<Tin,Tout>* pNode;
		pNode = new Cast<Tin,Tout>("cast");

		Outlet<Tin> input("input");
		pNode->inlet("input")->connect(input);
		Inlet<Tout> output("output");
		pNode->outlet("output")->connect(output);

		Tin inputValue = value;
		input.set(inputValue);
		pNode->update(inputValue);

		std::cerr << "output=" << output.value() << std::endl;
		assert (output.value() == static_cast<Tout>(inputValue));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void FlowNodesTest::setUp()
{
}


void FlowNodesTest::tearDown()
{
}


CppUnit::Test* FlowNodesTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("FlowNodesTest");

	CppUnit_addTest(pSuite, FlowNodesTest, testThresholdExceeded);
	CppUnit_addTest(pSuite, FlowNodesTest, testThresholdNotExceeded);
	CppUnit_addTest(pSuite, FlowNodesTest, testGate);
	CppUnit_addTest(pSuite, FlowNodesTest, testSplitter);
	CppUnit_addTest(pSuite, FlowNodesTest, testCast);
	return pSuite;
}
