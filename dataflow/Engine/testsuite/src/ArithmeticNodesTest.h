//
// ArithmeticNodesTest.h
//
// $Id$
//
// Definition of the ArithmeticNodesTest class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef ArithmeticNodesTest_INCLUDED
#define ArithmeticNodesTest_INCLUDED


#include "CppUnit/TestCase.h"
#include "IoT/Dataflow/Engine/Node.h"

using namespace IoT::Dataflow::Engine;

class ArithmeticNodesTest: public CppUnit::TestCase
{
public:
	ArithmeticNodesTest(const std::string& name);
	~ArithmeticNodesTest();

	template <typename T> Outlet<T>* test(Node::Ptr ptrNode, T first, T second);
	void testAdd();
	void testSub();
	void testMul();
	void testDiv();
	void testMod();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // ArithmeticNodesTest_INCLUDED
