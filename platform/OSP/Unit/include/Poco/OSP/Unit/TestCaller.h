//
// TestCaller.h
//
// Library: OSP/Unit
// Package: Unit
// Module:  TestCaller
//
// Definition of the TestCaller class.
//
// Copyright (c) 2011-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_Unit_TestCaller_INCLUDED
#define OSP_Unit_TestCaller_INCLUDED


#include "CppUnit/CppUnit.h"
#include "Poco/OSP/Unit/TestCase.h"
#include <memory>


namespace Poco {
namespace OSP {
namespace Unit {


template <class Fixture>
class TestCaller: public Poco::OSP::Unit::TestCase
	/// TestCaller class. This is a replacement for the
	/// CppUnit::TestCaller that enforces calling of the
	/// OSP Unit's TestCase class.
{
public:
	typedef void (Fixture::*TestMethod)();

	TestCaller(const std::string& name, TestMethod test):
		TestCase(name),
		_test(test),
		_fixture(new Fixture(name))
	{
	}

protected:
	void runTest()
	{
		(_fixture.get()->*_test)();
	}

	void setUp()
	{
		_fixture.get()->setUp();
	}

	void tearDown()
	{
		_fixture.get()->tearDown();
	}

private:
	TestCaller(const TestCaller& other);
	TestCaller& operator = (const TestCaller& other);

	TestMethod             _test;
	std::unique_ptr<Fixture> _fixture;
};


} } } // namespace Poco::OSP::Unit


#define error(exceptionClass) throw exceptionClass(__FILE__, __LINE__);


#define OSPUnit_addTest(suite, cls, mth) \
	suite->addTest(new Poco::OSP::Unit::TestCaller<cls>(#mth, &cls::mth))


#endif // OSP_Unit_TestCaller_INCLUDED
