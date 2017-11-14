//
// EventModerationPolicyTest.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "EventModerationPolicyTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "Poco/Delegate.h"


using namespace IoT::Devices;


EventModerationPolicyTest::EventModerationPolicyTest(const std::string& name): 
	CppUnit::TestCase(name),
	_eventValue(0),
	_eventCount(0)
{
	event += Poco::delegate(this, &EventModerationPolicyTest::onEvent);
}


EventModerationPolicyTest::~EventModerationPolicyTest()
{
	event -= Poco::delegate(this, &EventModerationPolicyTest::onEvent);
}


void EventModerationPolicyTest::testNoModerationPolicy()
{
	NoModerationPolicy<int> policy(event);
	
	policy.valueChanged(1);
	assert (_eventValue == 1);
	assert (_eventCount == 1);
}


void EventModerationPolicyTest::testMinimumDeltaModerationPolicy()
{
	MinimumDeltaModerationPolicy<int> policy(event, 0, 3);
	
	policy.valueChanged(1);
	assert (_eventValue == 0);
	assert (_eventCount == 0);

	policy.valueChanged(2);
	assert (_eventValue == 0);
	assert (_eventCount == 0);

	policy.valueChanged(3);
	assert (_eventValue == 3);
	assert (_eventCount == 1);

	policy.valueChanged(6);
	assert (_eventValue == 6);
	assert (_eventCount == 2);

	policy.valueChanged(3);
	assert (_eventValue == 3);
	assert (_eventCount == 3);
}


void EventModerationPolicyTest::testMaximumRateModerationPolicy()
{
	Poco::Util::Timer timer;
	MaximumRateModerationPolicy<int> policy(event, 0, 2000, timer);

	policy.valueChanged(1);
	assert (_eventValue == 1);
	assert (_eventCount == 1);

	policy.valueChanged(2);
	assert (_eventValue == 1);
	assert (_eventCount == 1);
	
	Poco::Thread::sleep(2200);
	assert (_eventValue == 2);
	assert (_eventCount == 2);
	
	policy.valueChanged(3);
	policy.valueChanged(4);
	assert (_eventValue == 2);
	assert (_eventCount == 2);
	Poco::Thread::sleep(2200);
	assert (_eventValue == 4);
	assert (_eventCount == 3);
}


void EventModerationPolicyTest::setUp()
{
	_eventValue = 0;
	_eventCount = 0;
}


void EventModerationPolicyTest::tearDown()
{
}


void EventModerationPolicyTest::onEvent(const void* sender, const int& value)
{
	_eventValue = value;
	_eventCount++;
}


CppUnit::Test* EventModerationPolicyTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("EventModerationPolicyTest");

	CppUnit_addTest(pSuite, EventModerationPolicyTest, testNoModerationPolicy);
	CppUnit_addTest(pSuite, EventModerationPolicyTest, testMinimumDeltaModerationPolicy);
	CppUnit_addTest(pSuite, EventModerationPolicyTest, testMaximumRateModerationPolicy);

	return pSuite;
}
