//
// ServiceRegistryTest.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "ServiceRegistryTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/Service.h"
#include "Poco/OSP/ServiceFactory.h"
#include "Poco/OSP/Properties.h"
#include "Poco/Delegate.h"
#include "Poco/Exception.h"


using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::Service;
using Poco::OSP::ServiceFactory;
using Poco::OSP::ServiceEvent;
using Poco::OSP::Properties;
using Poco::Delegate;


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

	class OtherTestService: public Service
	{
	public:
		using Ptr = Poco::AutoPtr<OtherTestService>;

		const std::type_info& type() const
		{
			return typeid(OtherTestService);
		}

		bool isA(const std::type_info& otherType) const
		{
			std::string name(typeid(OtherTestService).name());
			return name == otherType.name() || Service::isA(otherType);
		}
	};

	class TestServiceFactory: public ServiceFactory
	{
	public:
		Service::Ptr createService()
		{
			return new TestService;
		}
	};
}


ServiceRegistryTest::ServiceRegistryTest(const std::string& name): CppUnit::TestCase(name)
{
}


ServiceRegistryTest::~ServiceRegistryTest()
{
}


void ServiceRegistryTest::testRegistry()
{
	ServiceRegistry reg;
	reg.serviceRegistered   += Delegate<ServiceRegistryTest, ServiceEvent>(this, &ServiceRegistryTest::handleEvent);
	reg.serviceUnregistered += Delegate<ServiceRegistryTest, ServiceEvent>(this, &ServiceRegistryTest::handleEvent);

	_events.clear();

	Service::Ptr pService1 = new TestService;
	reg.registerService("Service1", pService1, Properties());

	assert (_events.size() == 1);
	assert (_events[0].service()->name() == "Service1");
	assert (_events[0].what() == ServiceEvent::EV_SERVICE_REGISTERED);

	ServiceRef::Ptr pRef = reg.findByName("Service1");
	assert (pRef->instance() == pService1);
	assert (pRef->name() == "Service1");

	pRef = reg.findByName("Service2");
	assert (pRef.isNull());

	std::vector<ServiceRef::Ptr> svcs;
	std::size_t n = reg.find("name == \"Service1\"", svcs);
	assert (n == 1);
	assert (svcs.size() == 1);
	assert (svcs[0]->instance() == pService1);

	assert (!reg.find("").empty());

	Service::Ptr pService2 = new TestServiceFactory;

	Properties props;
	props.set("foo", "bar");

	_events.clear();
	pRef = reg.registerService("Service2", pService2, props);

	assert (_events.size() == 1);
	assert (_events[0].service()->name() == "Service2");
	assert (_events[0].what() == ServiceEvent::EV_SERVICE_REGISTERED);

	assert (pRef->name() == "Service2");
	Service::Ptr pService21 = pRef->instance();
	assert (pService21 != pService2);

	Service::Ptr pService22 = pRef->instance();
	assert (pService22 != pService21);

	TestService::Ptr pTestService = pRef->castedInstance<TestService>();
	assert (pTestService.get() != 0);

	try
	{
		OtherTestService::Ptr pOtherTestService = pRef->castedInstance<OtherTestService>();
		fail("bad cast - must throw");
	}
	catch (Poco::BadCastException&)
	{
	}

	n = reg.find("foo == \"bar\"", svcs);
	assert (n == 1);
	assert (svcs.size() == 1);
	assert (svcs[0]->name() == "Service2");

	pRef->properties().set("foo", "BAR");
	n = reg.find("foo == \"bar\"", svcs);
	assert (n == 0);
	assert (svcs.size() == 0);

	n = reg.find("name =~ \"Service?\"", svcs);
	assert (n == 2);
	assert (svcs.size() == 2);
	assert (svcs[0]->name() == "Service1");
	assert (svcs[1]->name() == "Service2");

	pRef = reg.findByName("Service1");
	assert (pRef->name() == "Service1");

	pRef = reg.findByName("Service2");
	assert (pRef->name() == "Service2");

	try
	{
		Service::Ptr pService11 = new TestService;
		reg.registerService("Service1", pService11, Properties());
		fail("service already registered - must throw");
	}
	catch (Poco::ExistsException&)
	{
	}

	_events.clear();
	reg.unregisterService("Service1");
	assert (_events.size() == 1);
	assert (_events[0].service()->name() == "Service1");
	assert (_events[0].what() == ServiceEvent::EV_SERVICE_UNREGISTERED);

	n = reg.find("name =~ \"Service?\"", svcs);
	assert (n == 1);
	assert (svcs.size() == 1);
	assert (svcs[0]->name() == "Service2");
}


void ServiceRegistryTest::handleEvent(const void* sender, Poco::OSP::ServiceEvent& event)
{
	_events.push_back(event);
}


void ServiceRegistryTest::setUp()
{
}


void ServiceRegistryTest::tearDown()
{
}


CppUnit::Test* ServiceRegistryTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ServiceRegistryTest");

	CppUnit_addTest(pSuite, ServiceRegistryTest, testRegistry);

	return pSuite;
}
