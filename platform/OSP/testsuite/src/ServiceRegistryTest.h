//
// ServiceRegistryTest.h
//
// Definition of the ServiceRegistryTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef ServiceRegistryTest_INCLUDED
#define ServiceRegistryTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"
#include "Poco/OSP/ServiceEvent.h"
#include <vector>


class ServiceRegistryTest: public CppUnit::TestCase
{
public:
	ServiceRegistryTest(const std::string& name);
	~ServiceRegistryTest();

	void testRegistry();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

protected:
	void handleEvent(const void* sender, Poco::OSP::ServiceEvent& event);

private:
	std::vector<Poco::OSP::ServiceEvent> _events;
};


#endif // ServiceRegistryTest_INCLUDED
