//
// ServiceListenerTest.cpp
//
// Copyright (c) 2007-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "ServiceListenerTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceListener.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/Service.h"
#include "Poco/OSP/Properties.h"
#include "Poco/Delegate.h"
#include "Poco/Exception.h"


using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceListener;
using Poco::OSP::ServiceRef;
using Poco::OSP::Service;
using Poco::OSP::Properties;
using Poco::delegate;


namespace
{
	class TestService: public Service
	{
	public:
		using Ptr = Poco::AutoPtr<TestService>;

		const std::type_info& type() const
		{
			return typeid(TestService);
		}

		bool isA(const std::type_info& otherType) const
		{
			std::string name(typeid(TestService).name());
			return name == otherType.name() || Service::isA(otherType);
		}
	};
}


ServiceListenerTest::ServiceListenerTest(const std::string& name): CppUnit::TestCase(name)
{
}


ServiceListenerTest::~ServiceListenerTest()
{
}


void ServiceListenerTest::testListener()
{
	ServiceRegistry reg;
	ServiceListener::Ptr pListener1 = reg.createListener("name == \"Service1\"",
		delegate(this, &ServiceListenerTest::handleRegistered),
		delegate(this, &ServiceListenerTest::handleUnregistered));

	Service::Ptr pService1 = new TestService;
	ServiceRef::Ptr pServiceRef1 = reg.registerService("Service1", pService1, Properties());

	assert (_refs.size() == 1);
	assert (_refs.find(pServiceRef1) != _refs.end());

	Service::Ptr pService2 = new TestService;
	ServiceRef::Ptr pServiceRef2 = reg.registerService("Service2", pService2, Properties());

	assert (_refs.size() == 1);

	reg.unregisterService(pServiceRef1);

	assert (_refs.size() == 0);

	ServiceListener::Ptr pListener2 = reg.createListener("name == \"Service2\"",
		delegate(this, &ServiceListenerTest::handleRegistered),
		delegate(this, &ServiceListenerTest::handleUnregistered));

	assert (_refs.size() == 1);
	assert (_refs.find(pServiceRef2) != _refs.end());

	reg.unregisterService(pServiceRef2);

	assert (_refs.size() == 0);
}


void ServiceListenerTest::handleRegistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef)
{
	_refs.insert(pServiceRef);
}


void ServiceListenerTest::handleUnregistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef)
{
	_refs.erase(pServiceRef);
}


void ServiceListenerTest::setUp()
{
	_refs.clear();
}


void ServiceListenerTest::tearDown()
{
}


CppUnit::Test* ServiceListenerTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ServiceListenerTest");

	CppUnit_addTest(pSuite, ServiceListenerTest, testListener);

	return pSuite;
}
