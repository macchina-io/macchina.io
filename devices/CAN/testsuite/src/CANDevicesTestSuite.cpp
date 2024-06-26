//
// CANDevicesTestSuite.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "CANDevicesTestSuite.h"
#include "BitStreamTest.h"


CppUnit::Test* CANDevicesTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("CANDevicesTestSuite");

	pSuite->addTest(BitStreamTest::suite());

	return pSuite;
}
