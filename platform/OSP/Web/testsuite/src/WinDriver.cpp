//
// WinDriver.cpp
//
// Windows test driver for Poco OSP Web.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "WinTestRunner/WinTestRunner.h"
#include "WebTestSuite.h"


class TestDriver: public CppUnit::WinTestRunnerApp
{
	void TestMain()
	{
		CppUnit::WinTestRunner runner;
		runner.addTest(WebTestSuite::suite());
		runner.run();
	}
};


TestDriver theDriver;
