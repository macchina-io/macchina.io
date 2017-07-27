//
// DataFlowMasterTest.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "DataFlowMasterTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Dataflow/Engine/ArithmeticNodes.h"
#include "IoT/Dataflow/Engine/ComputationNodes.h"
#include "IoT/Dataflow/Engine/Engine.h"
#include "IoT/Dataflow/Engine/FastEvent.h"
#include "IoT/Dataflow/Engine/FlowNodes.h"
#include "IoT/Dataflow/Engine/Inlet.h"
#include "IoT/Dataflow/Engine/LogicalNodes.h"
#include "IoT/Dataflow/Engine/Node.h"
#include "IoT/Dataflow/Engine/Outlet.h"
#include "IoT/Dataflow/Engine/Port.h"
#include "IoT/Dataflow/Engine/RelationalNodes.h"
//#include "IoT/Dataflow/Engine/TimingNodes.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/AbstractDelegate.h"
#include "Poco/DefaultStrategy.h"
#include "Poco/Delegate.h"
#include "Poco/Exception.h"
#include "Poco/Format.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include <deque>
#include <limits>
#include <typeinfo>
#include <cmath>
#include <iostream>

using namespace IoT::Dataflow::Engine;


DataFlowMasterTest::DataFlowMasterTest(const std::string& name): 
	CppUnit::TestCase(name)
{
}


DataFlowMasterTest::~DataFlowMasterTest()
{
}

void DataFlowMasterTest::setUp()
{
}


void DataFlowMasterTest::tearDown()
{
}

void DataFlowMasterTest::testAdd()
{
	try
	{
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
	}
}


CppUnit::Test* DataFlowMasterTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DataFlowMasterTest");

	//CppUnit_addTest(pSuite, DataFlowMasterTest, testAdd);

	return pSuite;
}
