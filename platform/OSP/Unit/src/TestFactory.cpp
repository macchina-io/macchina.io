//
// TestFactory.cpp
//
// Library: OSP/Unit
// Package: Unit
// Module:  TestFactory
//
// Copyright (c) 2011-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Unit/TestFactory.h"
#include "CppUnit/Test.h"


using CppUnit::Test;


namespace Poco {
namespace OSP {
namespace Unit {


TestFactory::TestFactory()
{
}


TestFactory::~TestFactory()
{
}


namespace
{
	static TestFactory testFactory;
}


TestFactory& TestFactory::instance()
{
	return testFactory;
}


void TestFactory::add(const std::string& key, Test* pTest)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	_tests.insert(TestMap::value_type(key, pTest));
}


void TestFactory::remove(const std::string& key)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	_tests.erase(key);
}


TestFactory::TestVec TestFactory::get(const std::string& test)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	TestMap::iterator it = _tests.lower_bound(test);
	TestMap::iterator end = _tests.upper_bound(test);
	TestVec testVec;
	for (; it != end; ++it) testVec.push_back(it->second);
	return testVec;
}


} } } // namespace Poco::OSP::Unit
