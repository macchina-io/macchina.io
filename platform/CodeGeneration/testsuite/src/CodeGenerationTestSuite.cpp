//
// CodeGenerationTestSuite.cpp
//
// $Id: //poco/1.7/CodeGeneration/testsuite/src/CodeGenerationTestSuite.cpp#1 $
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "CodeGenerationTestSuite.h"
#include "CodeGenerationTest.h"


CppUnit::Test* CodeGenerationTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("CodeGenerationTestSuite");

	pSuite->addTest(CodeGenerationTest::suite());

	return pSuite;
}
