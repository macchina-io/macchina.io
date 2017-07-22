//
// ComputationNodesTest.h
//
// $Id$
//
// Definition of the ComputationNodesTest class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef ComputationNodesTest_INCLUDED
#define ComputationNodesTest_INCLUDED

#include "CppUnit/TestCase.h"

class ComputationNodesTest: public CppUnit::TestCase
{
public:
	ComputationNodesTest(const std::string& name);
	~ComputationNodesTest();

	void testScale();
	void testMax();
	void testMin();
	void testAverage();
	void testCount();
	void testAbs();
	void testDelta();
	void testAccumulate();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // ComputationNodesTest_INCLUDED
