//
// OPCTestSuite.h
//
// $Id$
//
// Definition of the OPCTestSuite class.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef OPCTestSuite_INCLUDED
#define OPCTestSuite_INCLUDED


#include "CppUnit/TestSuite.h"


class OPCTestSuite
{
public:
	static CppUnit::Test* suite();
};


#endif // OPCTestSuite_INCLUDED
