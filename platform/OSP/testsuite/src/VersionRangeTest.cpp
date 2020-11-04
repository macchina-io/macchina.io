//
// VersionRangeTest.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "VersionRangeTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/OSP/VersionRange.h"


using Poco::OSP::Version;
using Poco::OSP::VersionRange;


VersionRangeTest::VersionRangeTest(const std::string& name): CppUnit::TestCase(name)
{
}


VersionRangeTest::~VersionRangeTest()
{
}


void VersionRangeTest::testVersionRange()
{
	Version v100(1, 0, 0);
	Version v200(2, 0, 0);
	Version v050(0, 5, 0);
	Version v150(1, 5, 0);
	Version v300(3, 0, 0);
	
	VersionRange vr1(v100, true, v200, true);
	assert (vr1.isInRange(v100));
	assert (vr1.isInRange(v150));
	assert (vr1.isInRange(v200));
	assert (!vr1.isInRange(v050));
	assert (!vr1.isInRange(v300));
	assert (!vr1.isEmpty());
	
	VersionRange vr2(v100, false, v200, false);
	assert (!vr2.isInRange(v100));
	assert (vr2.isInRange(v150));
	assert (!vr2.isInRange(v200));
	assert (!vr2.isInRange(v050));
	assert (!vr2.isInRange(v300));
	assert (!vr2.isEmpty());
	
	VersionRange vr3(v150, true, v150, true);
	assert (vr3.isInRange(v150));
	assert (!vr3.isInRange(v100));
	assert (!vr3.isInRange(v200));
	assert (!vr3.isEmpty());

	VersionRange vr4;
	assert (!vr3.isInRange(v100));
	assert (!vr3.isInRange(v200));
	assert (vr4.isEmpty());
}


void VersionRangeTest::setUp()
{
}


void VersionRangeTest::tearDown()
{
}


CppUnit::Test* VersionRangeTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("VersionRangeTest");

	CppUnit_addTest(pSuite, VersionRangeTest, testVersionRange);

	return pSuite;
}
