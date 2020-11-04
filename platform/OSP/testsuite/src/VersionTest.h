//
// VersionTest.h
//
// Definition of the VersionTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef VersionTest_INCLUDED
#define VersionTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"


class VersionTest: public CppUnit::TestCase
{
public:
	VersionTest(const std::string& name);
	~VersionTest();

	void testConstruct();
	void testCompare();
	void testToString();
	void testParse();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // VersionTest_INCLUDED
