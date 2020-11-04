//
// OSPCoreTestSuite.h
//
// Definition of the OSPCoreTestSuite class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
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
