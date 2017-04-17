//
// ModbusTestSuite.h
//
// $Id$
//
// Definition of the GENATestSuite class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef ModbusTestSuite_INCLUDED
#define ModbusTestSuite_INCLUDED


#include "CppUnit/TestSuite.h"


class ModbusTestSuite
{
public:
	static CppUnit::Test* suite();
};


#endif // ModbusTestSuite_INCLUDED
