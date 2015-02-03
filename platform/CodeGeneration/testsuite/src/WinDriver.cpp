//
// WinDriver.cpp
//
// $Id: //poco/1.4/CodeGeneration/testsuite/src/WinDriver.cpp#2 $
//
// Windows test driver for Poco CodeGeneration.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "WinTestRunner/WinTestRunner.h"
#include "CodeGenerationTestSuite.h"


class TestDriver: public CppUnit::WinTestRunnerApp
{
	void TestMain()
	{
		CppUnit::WinTestRunner runner;
		runner.addTest(CodeGenerationTestSuite::suite());
		runner.run();
	}
};


TestDriver theDriver;
