//
// WinDriver.cpp
//
// Windows test driver for Poco RemotingNG.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
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
