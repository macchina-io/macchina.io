//
// UnitsOfMeasureTestSuite.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "UnitsOfMeasureTestSuite.h"
#include "UnitsOfMeasureTest.h"


CppUnit::Test* UnitsOfMeasureTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("UnitsOfMeasureTestSuite");

	pSuite->addTest(UnitsOfMeasureTest::suite());

	return pSuite;
}
