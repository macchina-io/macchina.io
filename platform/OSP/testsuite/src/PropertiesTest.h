//
// PropertiesTest.h
//
// Definition of the PropertiesTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef PropertiesTest_INCLUDED
#define PropertiesTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"


class PropertiesTest: public CppUnit::TestCase
{
public:
	PropertiesTest(const std::string& name);
	~PropertiesTest();

	void testProperties();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // PropertiesTest_INCLUDED
