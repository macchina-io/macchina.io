//
// MediaTypeMapperTest.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "MediaTypeMapperTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Path.h"
#include "Poco/OSP/Web/MediaTypeMapper.h"
#include <sstream>


using namespace Poco::OSP::Web;


MediaTypeMapperTest::MediaTypeMapperTest(const std::string& name): CppUnit::TestCase(name)
{
}


MediaTypeMapperTest::~MediaTypeMapperTest()
{
}


void MediaTypeMapperTest::testLoad()
{
	std::string mimeTypes(
		"# This is a comment\n"
		"application/activemessage\n"
		"application/atom+xml\tatom\n"
		"application/pdf\tpdf\n"
		"image/jpeg \t jpeg  jpg \t jpe");
	std::istringstream istr(mimeTypes);
	
	MediaTypeMapper mapper;

	mapper.load(istr);
	poco_assert(mapper.find("atom") != mapper.end());
	poco_assert(mapper.find("pdf") != mapper.end());
	poco_assert(mapper.find("unknown") == mapper.end());
}


void MediaTypeMapperTest::setUp()
{
}


void MediaTypeMapperTest::tearDown()
{
}


CppUnit::Test* MediaTypeMapperTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("MediaTypeMapperTest");

	CppUnit_addTest(pSuite, MediaTypeMapperTest, testLoad);

	return pSuite;
}
