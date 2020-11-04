//
// WebServerTestSuite.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "WebTestSuite.h"
#include "WebServerDispatcherTest.h"
#include "MediaTypeMapperTest.h"


CppUnit::Test* WebTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("WebTestSuite");

	pSuite->addTest(WebServerDispatcherTest::suite());
	pSuite->addTest(MediaTypeMapperTest::suite());

	return pSuite;
}
