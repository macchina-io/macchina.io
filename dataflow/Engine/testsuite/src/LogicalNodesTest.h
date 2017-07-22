//
// LogicalNodesTest.h
//
// $Id$
//
// Definition of the LogicalNodesTest class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef LogicalNodesTest_INCLUDED
#define LogicalNodesTest_INCLUDED


#include "CppUnit/TestCase.h"
#include "IoT/Dataflow/Engine/Node.h"

using namespace IoT::Dataflow::Engine;

class LogicalNodesTest: public CppUnit::TestCase
{
public:
	LogicalNodesTest(const std::string& name);
	~LogicalNodesTest();

	void testNot();
	void testAnd();
	void testOr();
	void testXor();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // LogicalNodesTest_INCLUDED
