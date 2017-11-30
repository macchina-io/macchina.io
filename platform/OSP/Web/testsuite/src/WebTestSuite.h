//
// WebTestSuite.h
//
// Definition of the WebTestSuite class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef WebTestSuite_INCLUDED
#define WebTestSuite_INCLUDED


#include "CppUnit/TestSuite.h"


class WebTestSuite
{
public:
	static CppUnit::Test* suite();
};


#endif // WebTestSuite_INCLUDED
