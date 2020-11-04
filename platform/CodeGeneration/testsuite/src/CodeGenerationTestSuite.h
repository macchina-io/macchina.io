//
// CodeGenerationTestSuite.h
//
// Definition of the CodeGenerationTestSuite class.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef CodeGenerationTestSuite_INCLUDED
#define CodeGenerationTestSuite_INCLUDED


#ifndef CppUnit_TestSuite_INCLUDED
#include "CppUnit/TestSuite.h"
#endif


class CodeGenerationTestSuite
{
public:
	static CppUnit::Test* suite();
};


#endif // CodeGenerationTestSuite_INCLUDED
