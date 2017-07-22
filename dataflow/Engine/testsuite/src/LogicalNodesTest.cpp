//
// LogicalNodesTest.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "LogicalNodesTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Dataflow/Engine/LogicalNodes.h"
#include <iostream>
#include "TestHelper.h"

using namespace IoT::Dataflow::Engine;


LogicalNodesTest::LogicalNodesTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


LogicalNodesTest::~LogicalNodesTest()
{
}

void LogicalNodesTest::testNot()
{
	Not<bool>::Ptr pNode = new Not<bool>("Not");

	try
	{
		bool value = true;

		Outlet<bool> input("input");
		Inlet<bool> output("output");
		pNode->outlet("output")->connect(output);
		pNode->inlet("input")->connect(input);
		input.set(value);

		pNode->update(value);

		std::cerr << "result=" << output.value() << std::endl;
		assert (output.value() == !value);

		value = false;
		input.set(value);
		pNode->update(value);

		std::cerr << "result=" << output.value() << std::endl;
		assert (output.value() == !value);
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void LogicalNodesTest::testAnd()
{
	And<bool>::Ptr pNode = new And<bool>("And");

	try
	{
		bool first = false;
		bool second = false;
		Outlet<bool>* pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first && second));

		first = false;
		second = true;
		pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first && second));

		first = true;
		second = false;
		pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first && second));

		first = true;
		second = true;
		pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first && second));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void LogicalNodesTest::testOr()
{
	Or<bool>::Ptr pNode = new Or<bool>("Or");

	try
	{
		bool first = false;
		bool second = false;
		Outlet<bool>* pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first || second));

		first = false;
		second = true;
		pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first || second));

		first = true;
		second = false;
		pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first || second));

		first = true;
		second = true;
		pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first || second));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}

void LogicalNodesTest::testXor()
{
	Xor<bool>::Ptr pNode = new Xor<bool>("Xor");

	try
	{
		bool first = false;
		bool second = false;
		Outlet<bool>* pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first ^ second));

		first = false;
		second = true;
		pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first ^ second));

		first = true;
		second = false;
		pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first ^ second));

		first = true;
		second = true;
		pOut=defaultTest(pNode,first,second);
		pNode->update(first);
		std::cerr << "result=" << pOut->value() << std::endl;
		assert (pOut->value() == (first ^ second));
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}


void LogicalNodesTest::setUp()
{
}


void LogicalNodesTest::tearDown()
{
}


CppUnit::Test* LogicalNodesTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("LogicalNodesTest");

	CppUnit_addTest(pSuite, LogicalNodesTest, testNot);
	CppUnit_addTest(pSuite, LogicalNodesTest, testAnd);
	CppUnit_addTest(pSuite, LogicalNodesTest, testOr);
	CppUnit_addTest(pSuite, LogicalNodesTest, testXor);
	return pSuite;
}
