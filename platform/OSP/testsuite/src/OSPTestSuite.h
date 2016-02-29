//
// OSPTestSuite.h
//
// $Id: //poco/1.7/OSP/testsuite/src/OSPTestSuite.h#1 $
//
// Definition of the OSPTestSuite class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSPTestSuite_INCLUDED
#define OSPTestSuite_INCLUDED


#include "CppUnit/TestSuite.h"


class OSPTestSuite
{
public:
	static CppUnit::Test* suite();
};


#endif // OSPTestSuite_INCLUDED
