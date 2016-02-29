//
// VersionRangeTest.h
//
// $Id: //poco/1.7/OSP/testsuite/src/VersionRangeTest.h#1 $
//
// Definition of the VersionRangeTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
