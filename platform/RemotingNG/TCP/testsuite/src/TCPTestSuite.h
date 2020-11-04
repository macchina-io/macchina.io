//
// TCPTestSuite.h
//
// Definition of the TCPTestSuite class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TCPTestSuite_INCLUDED
#define TCPTestSuite_INCLUDED


#include "CppUnit/TestSuite.h"


class TCPTestSuite
{
public:
	static CppUnit::Test* suite();
};


#endif // TCPTestSuite_INCLUDED
