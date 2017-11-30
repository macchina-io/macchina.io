//
// TestBundleSuite.h
//
// Definition of the TestBundleSuite class.
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
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
