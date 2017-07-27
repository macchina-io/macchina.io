//
// ComputationNodesTest.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "ComputationNodesTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Dataflow/Engine/ComputationNodes.h"
#include "IoT/Dataflow/Engine/DataFlow.h"
#include "TestHelper.h"

using namespace IoT::Dataflow::Engine;


ComputationNodesTest::ComputationNodesTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


ComputationNodesTest::~ComputationNodesTest()
{
}

#define MAX_ITERATIONS 3

void ComputationNodesTest::testScale()
{
	try
	{
		Dataflow flow;
		double scale = 2.0;
		double offset = 1.0;
		Scale<double>::Ptr pNode = new Scale<double>("scale",scale,offset);

		Outlet<double> outScale("scale");
		Outlet<double> outOffset("offset");
		Inlet<double> inOutput("output");
		pNode->outlet("output")->connect(inOutput);
		pNode->inlet("scale")->connect(outScale);
		outScale.set(scale);
		pNode->inlet("offset")->connect(outOffset);
		outOffset.set(offset);

		flow.testWithNode(pNode,MAX_ITERATIONS);
		double result = 0;
		for (int i = 0; i< MAX_ITERATIONS; i++)
			result = i*scale+offset;

		std::cerr << "output=" << inOutput.value() << std::endl;
		assert (inOutput.value() == result);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ComputationNodesTest::testMax()
{
	try
	{
		Dataflow flow;
		Max<double>::Ptr pNode = new Max<double>("max");

		Inlet<double> output("output");
		pNode->outlet("output")->connect(output);

		flow.testWithNode(pNode,MAX_ITERATIONS);

		std::cerr << "output=" << output.value() << std::endl;
		assert (output.value() == MAX_ITERATIONS-1);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ComputationNodesTest::testMin()
{
	try
	{
		Dataflow flow;
		Min<double>::Ptr pNode = new Min<double>("min");

		Inlet<double> output("output");
		pNode->outlet("output")->connect(output);

		flow.testWithNode(pNode,MAX_ITERATIONS,1000);

		std::cerr << "output=" << output.value() << std::endl;
		assert (output.value() == 0);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ComputationNodesTest::testAverage()
{
	try
	{
		Dataflow flow;
		Avg<double>::Ptr pNode = new Avg<double>("avg");

		Inlet<double> result("output");
		pNode->outlet("output")->connect(result);

		flow.testWithNode(pNode,MAX_ITERATIONS,1000);
		double average = 0;
		for (int i = 0; i< MAX_ITERATIONS; i++)
			average += i;
		average /= MAX_ITERATIONS;

		std::cerr << "output=" << result.value() << std::endl;
		assert (result.value() == average);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ComputationNodesTest::testCount()
{
	try
	{
		Dataflow flow;
		Count<int>::Ptr pNode = new Count<int>("count");

		Inlet<Poco::UInt32> output("counter");
		pNode->outlet("counter")->connect(output);
		//Outlet<bool> outletTrigger("trigger");
		//pNode->inlet("trigger")->connect(outletTrigger);
		//outletTrigger.set(true);

		for (int i=0;i<MAX_ITERATIONS;i++)
			pNode->update(true);

		std::cerr << "counter=" << output.value() << std::endl;
		assert (output.value() == MAX_ITERATIONS);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ComputationNodesTest::testAbs()
{
	try
	{
		Dataflow flow;
		Abs<double>::Ptr pNode = new Abs<double>("abs");

		double value = -11.1;
		Outlet<double> outletInput("input");
		pNode->inlet("input")->connect(outletInput);
		Inlet<double> inletResult("output");
		pNode->outlet("output")->connect(inletResult);
		outletInput.set(value);
		pNode->update(value);

		std::cerr << "output=" << inletResult.value() << std::endl;
		assert (inletResult.value() == std::abs(value));

		value = 1.1;
		outletInput.set(value);
		pNode->update(value);

		std::cerr << "output=" << inletResult.value() << std::endl;
		assert (inletResult.value() == std::abs(value));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ComputationNodesTest::testDelta()
{
	try
	{
		Dataflow flow;
		Delta<double>::Ptr pNode = new Delta<double>("delta");
		Inlet<double> inletResult("output");
		pNode->outlet("output")->connect(inletResult);

		flow.testWithNode(pNode,MAX_ITERATIONS);

		std::cerr << "output=" << inletResult.value() << std::endl;
		assert (inletResult.value() == 1);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ComputationNodesTest::testAccumulate()
{
	try
	{
		Dataflow flow;
		Accumulate<double>::Ptr pNode = new Accumulate<double>("accumulate");
		Inlet<double> result("output");
		pNode->outlet("output")->connect(result);

		flow.testWithNode(pNode,MAX_ITERATIONS);

		std::cerr << "output=" << result.value() << std::endl;
		double sum=0.0;
		for (int i=0;i<MAX_ITERATIONS;i++)
			sum += (double)i;
			
		assert (result.value() == sum);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ComputationNodesTest::setUp()
{
}


void ComputationNodesTest::tearDown()
{
}


CppUnit::Test* ComputationNodesTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ComputationNodesTest");

	CppUnit_addTest(pSuite, ComputationNodesTest, testScale);
	CppUnit_addTest(pSuite, ComputationNodesTest, testMax);
	CppUnit_addTest(pSuite, ComputationNodesTest, testMin);
	CppUnit_addTest(pSuite, ComputationNodesTest, testAverage);
	CppUnit_addTest(pSuite, ComputationNodesTest, testCount);
	CppUnit_addTest(pSuite, ComputationNodesTest, testAbs);
	CppUnit_addTest(pSuite, ComputationNodesTest, testDelta);
	CppUnit_addTest(pSuite, ComputationNodesTest, testAccumulate);
	return pSuite;
}
