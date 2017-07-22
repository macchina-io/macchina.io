//
// FlowNodesTest.h
//
// $Id$
//
// Definition of the FlowNodesTest class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef FlowNodesTest_INCLUDED
#define FlowNodesTest_INCLUDED


#include "CppUnit/TestCase.h"

class FlowNodesTest: public CppUnit::TestCase
{
public:
	FlowNodesTest(const std::string& name);
	~FlowNodesTest();

	void testThreshold(bool exceed);
	void testThresholdNotExceeded();
	void testThresholdExceeded();
	void testGate();
	void testSplitter();
	void testCast();
	template <typename Tin, typename Tout>
	void testCast(Tin value);

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // FlowNodesTest_INCLUDED
