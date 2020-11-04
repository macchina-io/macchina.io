//
// OSPTestSuite.h
//
// Definition of the OSPTestSuite class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
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
