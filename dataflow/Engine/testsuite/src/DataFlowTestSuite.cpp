//
// DataFlowTestSuite.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "DataFlowTestSuite.h"
#include "DataFlowMasterTest.h"
#include "ArithmeticNodesTest.h"
#include "LogicalNodesTest.h"
#include "RelationalNodesTest.h"
#include "ComputationNodesTest.h"
#include "FlowNodesTest.h"
#include "TimingNodesTest.h"

CppUnit::Test* DataFlowTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DataFlowTestSuite");

	pSuite->addTest(DataFlowMasterTest::suite());
	pSuite->addTest(ArithmeticNodesTest::suite());
	pSuite->addTest(LogicalNodesTest::suite());
	pSuite->addTest(RelationalNodesTest::suite());
	pSuite->addTest(ComputationNodesTest::suite());
	pSuite->addTest(FlowNodesTest::suite());
	pSuite->addTest(TimingNodesTest::suite());

	return pSuite;
}
