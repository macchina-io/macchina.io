//
// EventModerationPolicyTest.h
//
// Definition of the EventModerationPolicyTest class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef EventModerationPolicyTest_INCLUDED
#define EventModerationPolicyTest_INCLUDED


#include "IoT/Devices/Devices.h"
#include "CppUnit/TestCase.h"
#include "Poco/BasicEvent.h"


class EventModerationPolicyTest: public CppUnit::TestCase
{
public:
	EventModerationPolicyTest(const std::string& name);
	~EventModerationPolicyTest();
	
	Poco::BasicEvent<const int> event;

	void testNoModerationPolicy();
	void testMinimumDeltaModerationPolicy();
	void testMaximumRateModerationPolicy();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

protected:
	void onEvent(const void* sender, const int& value);
	
private:
	int _eventValue;
	int _eventCount;
};


#endif // EventModerationPolicyTest_INCLUDED
