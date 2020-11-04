//
// ServiceTestSuite.h
//
// Definition of the ServiceTestSuite class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef ServiceTestSuite_INCLUDED
#define ServiceTestSuite_INCLUDED


#include "CppUnit/TestSuite.h"


class ServiceTestSuite
{
public:
	static CppUnit::Test* suite();
};


#endif // ServiceTestSuite_INCLUDED
