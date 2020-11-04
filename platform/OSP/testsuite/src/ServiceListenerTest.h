//
// ServiceListenerTest.h
//
// Definition of the ServiceListenerTest class.
//
// Copyright (c) 2007-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef ServiceListenerTest_INCLUDED
#define ServiceListenerTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"
#include "Poco/OSP/ServiceRef.h"
#include <set>


class ServiceListenerTest: public CppUnit::TestCase
{
public:
	ServiceListenerTest(const std::string& name);
	~ServiceListenerTest();

	void testListener();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

protected:
	void handleRegistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef);
	void handleUnregistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef);

private:
	std::set<Poco::OSP::ServiceRef::Ptr> _refs;
};


#endif // ServiceListenerTest_INCLUDED
