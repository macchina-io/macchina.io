//
// PropertiesTest.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "PropertiesTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/OSP/Properties.h"


using Poco::OSP::Properties;


PropertiesTest::PropertiesTest(const std::string& name): CppUnit::TestCase(name)
{
}


PropertiesTest::~PropertiesTest()
{
}


void PropertiesTest::testProperties()
{
	Properties props;
	
	props.set("foo", "bar");
	assert (props.has("foo"));
	assert (props.has("Foo"));
	assert (props["foo"] == "bar");
	assert (props.get("foo") == "bar");
	assert (props.get("FOO") == "bar");
	
	assert (!props.has("f00"));
	
	try
	{
		props.get("fuu");
		fail("nonexistent property - must throw");
	}
	catch (Poco::NotFoundException&)
	{
	}
	assert (props.get("f00", "bar") == "bar");
	
	props.set("n", "42");
	props.set("x", "0.5");
	props.set("f", "false");
	props.set("t", "true");
	
	assert (props.getInt("n") == 42);
	assert (props.getInt("N") == 42);
	
	try
	{
		props.getInt("f00");
		fail("nonexistent property - must throw");
	}
	catch (Poco::NotFoundException&)
	{
	}
	assert (props.getInt("f00", 100) == 100);
	
	assert (props.getFloat("x") == 0.5);
	try
	{
		props.getFloat("f00");
		fail("nonexistent property - must throw");
	}
	catch (Poco::NotFoundException&)
	{
	}
	assert (props.getFloat("f00", 0.5) == 0.5);
	
	assert (props.getBool("f") == false);
	assert (props.getBool("t") == true);
	try
	{
		props.getBool("f00");
		fail("nonexistent property - must throw");
	}
	catch (Poco::NotFoundException&)
	{
	}
	assert (props.getBool("f00", true) == true);
	
	std::vector<std::string> keys;
	props.keys(keys);
	
	assert (keys.size() == 5);
	assert (keys[0] == "f");
	assert (keys[1] == "foo");
	assert (keys[2] == "n");
	assert (keys[3] == "t");
	assert (keys[4] == "x");
}


void PropertiesTest::setUp()
{
}


void PropertiesTest::tearDown()
{
}


CppUnit::Test* PropertiesTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("PropertiesTest");

	CppUnit_addTest(pSuite, PropertiesTest, testProperties);

	return pSuite;
}
