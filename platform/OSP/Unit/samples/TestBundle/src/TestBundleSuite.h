//
// TestBundleSuite.h
//
// Definition of the TestBundleSuite class.
//
// Copyright (c) 2011-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TestBundleSuite_INCLUDED
#define TestBundleSuite_INCLUDED


#include "CppUnit/TestSuite.h"


class TestBundleSuite
{
public:
	static CppUnit::Test* suite();
};


#endif // TestBundleSuite_INCLUDED
