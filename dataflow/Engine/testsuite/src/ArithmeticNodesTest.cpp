//
// ArithmeticNodesTest.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "ArithmeticNodesTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Dataflow/Engine/ArithmeticNodes.h"
#include <iostream>
#include "TestHelper.h"

using namespace IoT::Dataflow::Engine;


ArithmeticNodesTest::ArithmeticNodesTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


ArithmeticNodesTest::~ArithmeticNodesTest()
{
}

void ArithmeticNodesTest::testAdd()
{
	Add<double>::Ptr pNode = new Add<double>("Add");

	try
	{
		double first = 1.2;
		double second = 3.4;
		Outlet<double>* pOut=defaultTest(pNode,first,second);

		pNode->update(first);

		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == first+second);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ArithmeticNodesTest::testSub()
{
	Sub<double>::Ptr pNode = new Sub<double>("Sub");

	try
	{
		double first = 5.6;
		double second = 3.4;
		Outlet<double>* pOut=defaultTest(pNode,first,second);

		pNode->update(first);

		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == first-second);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ArithmeticNodesTest::testMul()
{
	Mul<double>::Ptr pNode = new Mul<double>("Mul");

	try
	{
		double first = 5.6;
		double second = 3.4;
		Outlet<double>* pOut=defaultTest(pNode,first,second);

		pNode->update(first);

		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == first*second);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ArithmeticNodesTest::testDiv()
{
	Div<double>::Ptr pNode = new Div<double>("Div");

	try
	{
		double first = 5.6;
		double second = 3.4;
		Outlet<double>* pOut=defaultTest(pNode,first,second);

		pNode->update(first);

		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == first/second);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void ArithmeticNodesTest::testMod()
{
	Mod<int>::Ptr pNode = new Mod<int>("Mod");

	try
	{
		int first = 9;
		int second = 2;
		Outlet<int>* pOut=defaultTest(pNode,first,second);

		pNode->update(first);

		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first % second));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}


void ArithmeticNodesTest::setUp()
{
}


void ArithmeticNodesTest::tearDown()
{
}


CppUnit::Test* ArithmeticNodesTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ArithmeticNodesTest");

	CppUnit_addTest(pSuite, ArithmeticNodesTest, testAdd);
	CppUnit_addTest(pSuite, ArithmeticNodesTest, testSub);
	CppUnit_addTest(pSuite, ArithmeticNodesTest, testMul);
	CppUnit_addTest(pSuite, ArithmeticNodesTest, testDiv);
	CppUnit_addTest(pSuite, ArithmeticNodesTest, testMod);

	return pSuite;
}
