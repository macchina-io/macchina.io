//
// RelationalNodesTest.h
//
// $Id$
//
// Definition of the RelationalNodesTest class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RelationalNodesTest_INCLUDED
#define RelationalNodesTest_INCLUDED


#include "CppUnit/TestCase.h"
#include "IoT/Dataflow/Engine/Node.h"

using namespace IoT::Dataflow::Engine;

class RelationalNodesTest: public CppUnit::TestCase
{
public:
	RelationalNodesTest(const std::string& name);
	~RelationalNodesTest();

	void testGreaterThan();
	void testGreaterThanOrEqual();
	void testLessThan();
	void testLessThanOrEqual();
	void testEqual();
	void testNotEqual();
	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // RelationalNodesTest_INCLUDED
