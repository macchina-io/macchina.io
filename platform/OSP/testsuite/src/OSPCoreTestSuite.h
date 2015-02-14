//
// OSPCoreTestSuite.h
//
// $Id: //poco/1.6/OSP/testsuite/src/OSPCoreTestSuite.h#1 $
//
// Definition of the OSPCoreTestSuite class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSPCoreTestSuite_INCLUDED
#define OSPCoreTestSuite_INCLUDED


#include "CppUnit/TestSuite.h"


class OSPCoreTestSuite
{
public:
	static CppUnit::Test* suite();
};


#endif // OSPCoreTestSuite_INCLUDED
