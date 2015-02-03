//
// ServiceTestSuite.h
//
// $Id: //poco/1.4/OSP/testsuite/src/ServiceTestSuite.h#2 $
//
// Definition of the ServiceTestSuite class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
