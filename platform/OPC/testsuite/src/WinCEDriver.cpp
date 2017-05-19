//
// WinCEDriver.cpp
//
// $Id: //poco/1.4/OPC/testsuite/src/WinCEDriver.cpp#1 $
//
// Console-based test driver for Windows CE.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "CppUnit/TestRunner.h"
#include "OPCTestSuite.h"
#include <cstdlib>


int wmain(int argc, wchar_t* argv[])
{
	std::vector<std::string> args;
	for (int i = 0; i < argc; ++i)
	{
		char buffer[1024];
		std::wcstombs(buffer, argv[i], sizeof(buffer));
		args.push_back(std::string(buffer));
	}
	CppUnit::TestRunner runner;	
	runner.addTest("OPCTestSuite", OPCTestSuite::suite());
	return runner.run(args) ? 0 : 1;
}
