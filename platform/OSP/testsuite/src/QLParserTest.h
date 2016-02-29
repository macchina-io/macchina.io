//
// QLParserTest.h
//
// $Id: //poco/1.7/OSP/testsuite/src/QLParserTest.h#1 $
//
// Definition of the QLParserTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef QLParserTest_INCLUDED
#define QLParserTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"


class QLParserTest: public CppUnit::TestCase
{
public:
	QLParserTest(const std::string& name);
	~QLParserTest();

	void testParser();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // QLParserTest_INCLUDED
