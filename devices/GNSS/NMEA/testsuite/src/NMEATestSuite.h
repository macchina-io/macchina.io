//
// NMEATestSuite.h
//
// Definition of the NMEATestSuite class.
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef NMEATestSuite_INCLUDED
#define NMEATestSuite_INCLUDED


#include "CppUnit/TestSuite.h"


class NMEATestSuite
{
public:
	static CppUnit::Test* suite();
};


#endif // NMEATestSuite_INCLUDED
