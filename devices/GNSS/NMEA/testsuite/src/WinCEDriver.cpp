//
// WinCEDriver.cpp
//
// $Id$
//
// Console-based test driver for Windows CE.
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "CppUnit/TestRunner.h"
#include "NMEATestSuite.h"
#include <cstdlib>


int _tmain(int argc, wchar_t* argv[])
{
	std::vector<std::string> args;
	for (int i = 0; i < argc; ++i)
	{
		char buffer[1024];
		std::wcstombs(buffer, argv[i], sizeof(buffer));
		args.push_back(std::string(buffer));
	}
	CppUnit::TestRunner runner;	
	runner.addTest("NMEATestSuite", NMEATestSuite::suite());
	return runner.run(args) ? 0 : 1;
}
