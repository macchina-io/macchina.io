//
// DataFlowMasterTest.h
//
// $Id$
//
// Definition of the DataFlowMasterTest class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef DataFlowMasterTest_INCLUDED
#define DataFlowMasterTest_INCLUDED


#include "CppUnit/TestCase.h"
#include "IoT/Dataflow/Engine/Node.h"

using namespace IoT::Dataflow::Engine;

class DataFlowMasterTest: public CppUnit::TestCase
{
public:
	DataFlowMasterTest(const std::string& name);
	~DataFlowMasterTest();

	void testAdd();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();
};


#endif // DataFlowMasterTest_INCLUDED
