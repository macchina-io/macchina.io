//
// WinDriver.cpp
//
// $Id: //poco/1.6/RemotingNG/testsuite/src/WinDriver.cpp#1 $
//
// Windows test driver for Poco RemotingNG.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "WinTestRunner/WinTestRunner.h"
#include "RemotingTestSuite.h"


class TestDriver: public CppUnit::WinTestRunnerApp
{
	void TestMain()
	{
		CppUnit::WinTestRunner runner;
		runner.addTest(RemotingTestSuite::suite());
		runner.run();
	}
};


TestDriver theDriver;
