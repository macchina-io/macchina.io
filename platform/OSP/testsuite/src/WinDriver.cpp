//
// WinDriver.cpp
//
// Windows test driver for Poco OSPCore.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "WinTestRunner/WinTestRunner.h"
#include "OSPTestSuite.h"


class TestDriver: public CppUnit::WinTestRunnerApp
{
	void TestMain()
	{
		CppUnit::WinTestRunner runner;
		runner.addTest(OSPTestSuite::suite());
		runner.run();
	}
};


TestDriver theDriver;
