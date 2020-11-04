//
// VersionRangeTest.h
//
// Definition of the VersionRangeTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef VersionRangeTest_INCLUDED
#define VersionRangeTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"


class VersionRangeTest: public CppUnit::TestCase
{
public:
	VersionRangeTest(const std::string& name);
	~VersionRangeTest();

	void testVersionRange();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // VersionRangeTest_INCLUDED
