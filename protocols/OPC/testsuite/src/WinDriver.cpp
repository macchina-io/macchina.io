//
// WinDriver.cpp
//
// $Id: //poco/1.4/OPC/testsuite/src/WinDriver.cpp#1 $
//
// Windows test driver for Poco OPC.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "WinTestRunner/WinTestRunner.h"
#include "OPCTestSuite.h"


class TestDriver: public CppUnit::WinTestRunnerApp
{
	void TestMain()
	{
		CppUnit::WinTestRunner runner;
		runner.addTest(OPCTestSuite::suite());
		runner.run();
	}
};


TestDriver theDriver;
