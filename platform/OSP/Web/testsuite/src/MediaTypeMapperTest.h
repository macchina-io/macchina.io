//
// MediaTypeMapperTest.h
//
// $Id: //poco/1.7/OSP/Web/testsuite/src/MediaTypeMapperTest.h#1 $
//
// Definition of the MediaTypeMapperTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
