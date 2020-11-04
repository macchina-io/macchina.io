//
// MediaTypeMapperTest.h
//
// Definition of the MediaTypeMapperTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef MediaTypeMapperTest_INCLUDED
#define MediaTypeMapperTest_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "CppUnit/TestCase.h"


class MediaTypeMapperTest: public CppUnit::TestCase
{
public:
	MediaTypeMapperTest(const std::string& name);
	~MediaTypeMapperTest();

	void testLoad();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // MediaTypeMapperTest_INCLUDED
