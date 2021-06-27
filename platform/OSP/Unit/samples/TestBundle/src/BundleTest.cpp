//
// BundleTest.cpp
//
// Copyright (c) 2011-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "BundleTest.h"
#include "Poco/OSP/Unit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Exception.h"
#include "Poco/Format.h"


using Poco::UnhandledException;
using Poco::format;


BundleTest::BundleTest(const std::string& name): Poco::OSP::Unit::TestCase(name),
	_setUp(false),
	_tornDown(false)
{
}


BundleTest::~BundleTest()
{
}


void BundleTest::testSuccess()
{
	context()->logger().information("Hello, world!");
}


void BundleTest::testError()
{
	error(UnhandledException);
}


void BundleTest::testFailure()
{
	failmsg("This is failure testing. Ignore.");
}


void BundleTest::setUp()
{
	_setUp = true;
}


void BundleTest::testSetUp()
{
	assert(_setUp);
}


void BundleTest::testTornDown()
{
	assert(!_tornDown);
}


void BundleTest::tearDown()
{
	_tornDown = true;
}


CppUnit::Test* BundleTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("BundleTest");

	OSPUnit_addTest(pSuite, BundleTest, testSetUp);
	OSPUnit_addTest(pSuite, BundleTest, testSuccess);
	OSPUnit_addTest(pSuite, BundleTest, testError);
	OSPUnit_addTest(pSuite, BundleTest, testFailure);
	OSPUnit_addTest(pSuite, BundleTest, testTornDown);

	return pSuite;
}
