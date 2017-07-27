//
// RelationalNodesTest.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "RelationalNodesTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Dataflow/Engine/RelationalNodes.h"
#include <iostream>
#include "TestHelper.h"

using namespace IoT::Dataflow::Engine;


RelationalNodesTest::RelationalNodesTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


RelationalNodesTest::~RelationalNodesTest()
{
}

void RelationalNodesTest::testGreaterThan()
{
	GreaterThan<double>::Ptr pNode = new GreaterThan<double>("GreaterThan");

	try
	{
		double first = 1.2;
		double second = 3.4;
		Outlet<bool>* pOut=defaultTestBool(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first > second));

		pOut=defaultTestBool(pNode,second,first);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (second > first));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void RelationalNodesTest::testGreaterThanOrEqual()
{
	GreaterThanOrEqual<double>::Ptr pNode = new GreaterThanOrEqual<double>("GreaterThanOrEqual");

	try
	{
		double first = 1.2;
		double second = 3.4;
		Outlet<bool>* pOut=defaultTestBool(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first > second));

		pOut=defaultTestBool(pNode,second,first);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (second > first));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void RelationalNodesTest::testLessThan()
{
	LessThan<double>::Ptr pNode = new LessThan<double>("LessThan");

	try
	{
		double first = 1.2;
		double second = 3.4;
		Outlet<bool>* pOut=defaultTestBool(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first < second));

		pOut=defaultTestBool(pNode,second,first);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (second < first));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void RelationalNodesTest::testLessThanOrEqual()
{
	LessThanOrEqual<double>::Ptr pNode = new LessThanOrEqual<double>("LessThanOrEqual");

	try
	{
		double first = 1.2;
		double second = 3.4;
		Outlet<bool>* pOut=defaultTestBool(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first < second));

		pOut=defaultTestBool(pNode,second,first);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (second < first));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void RelationalNodesTest::testEqual()
{
	Equal<double>::Ptr pNode = new Equal<double>("Equal");

	try
	{
		double first = 1.2;
		double second = 3.4;
		Outlet<bool>* pOut=defaultTestBool(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first == second));

		second=first;
		pOut=defaultTestBool(pNode,second,first);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (second == first));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void RelationalNodesTest::testNotEqual()
{
	NotEqual<double>::Ptr pNode = new NotEqual<double>("NotEqual");

	try
	{
		double first = 1.2;
		double second = 3.4;
		Outlet<bool>* pOut=defaultTestBool(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first != second));

		second=first;
		pOut=defaultTestBool(pNode,second,first);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (second != first));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void RelationalNodesTest::setUp()
{
}


void RelationalNodesTest::tearDown()
{
}


CppUnit::Test* RelationalNodesTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("RelationalNodesTest");

	CppUnit_addTest(pSuite, RelationalNodesTest, testGreaterThan);
	CppUnit_addTest(pSuite, RelationalNodesTest, testGreaterThanOrEqual);
	CppUnit_addTest(pSuite, RelationalNodesTest, testLessThan);
	CppUnit_addTest(pSuite, RelationalNodesTest, testLessThanOrEqual);
	CppUnit_addTest(pSuite, RelationalNodesTest, testEqual);
	CppUnit_addTest(pSuite, RelationalNodesTest, testNotEqual);
	return pSuite;
}
