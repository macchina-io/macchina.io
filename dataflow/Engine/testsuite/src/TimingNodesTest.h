//
// TimingNodesTest.h
//
// $Id$
//
// Definition of the TimingNodesTest class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TimingNodesTest_INCLUDED
#define TimingNodesTest_INCLUDED

#include "CppUnit/TestCase.h"

class TimingNodesTest: public CppUnit::TestCase
{
public:
	TimingNodesTest(const std::string& name);
	~TimingNodesTest();

	void testStopwatch();
	void testTick();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // TimingNodesTest_INCLUDED
