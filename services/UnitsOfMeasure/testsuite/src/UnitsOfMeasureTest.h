//
// UnitsOfMeasureTest.h
//
// Definition of the UnitsOfMeasureTest class.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef UnitsOfMeasureTest_INCLUDED
#define UnitsOfMeasureTest_INCLUDED


#include "CppUnit/TestCase.h"
#include "IoT/UnitsOfMeasure/UnitsOfMeasureServiceImpl.h"


class UnitsOfMeasureTest: public CppUnit::TestCase
{
public:
	UnitsOfMeasureTest(const std::string& name);
	~UnitsOfMeasureTest();

	void testFindPrefix();
	void testFindBaseUnit();
	void testFindUnit();
	void testResolve();
	void testPrint();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
	IoT::UnitsOfMeasure::UnitsOfMeasureServiceImpl::Ptr _pUoM;
};


#endif // UnitsOfMeasureTest_INCLUDED
