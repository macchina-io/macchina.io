//
// WinDriver.cpp
//
// Windows test driver for IoT GNSS NMEA.
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "WinTestRunner/WinTestRunner.h"
#include "NMEATestSuite.h"


class TestDriver: public CppUnit::WinTestRunnerApp
{
	void TestMain()
	{
		CppUnit::WinTestRunner runner;
		runner.addTest(NMEATestSuite::suite());
		runner.run();
	}
};


TestDriver theDriver;
