//
// TestCase.cpp
//
// Library: OSP/Unit
// Package: Unit
// Module:  TestCase
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "Poco/OSP/Unit/TestCase.h"
#include "CppUnit/TestResult.h"
#include "Poco/Exception.h"


using CppUnit::TestResult;
using CppUnit::CppUnitException;


namespace Poco {
namespace OSP {
namespace Unit {


Poco::OSP::BundleContext::Ptr TestCase::_pContext;


TestCase::TestCase(const std::string& name): 
	CppUnit::TestCase(name)
{
}

	
TestCase::~TestCase()
{
}


void TestCase::run(TestResult* result)
{
	result->startTest(this);

	setUp();
	try 
	{
		runTest();
	}
	catch (CppUnitException& e) 
	{
		CppUnitException* copy = new CppUnitException(e);
		result->addFailure(this, copy);
	}
	catch (Poco::Exception& e)
	{
		result->addError(this, new CppUnitException(e.displayText()));
	}
	catch (std::exception& e)
	{
		std::string msg(typeid(e).name());
		msg.append(": ");
		msg.append(e.what());
		result->addError(this, new CppUnitException(msg));
	}
#if !defined(_WIN32)
	catch (...)
	{
		CppUnitException *e = new CppUnitException ("unknown exception");
		result->addError (this, e);
	}
#endif
	tearDown();
	result->endTest(this);
}


Poco::OSP::BundleContext::Ptr TestCase::context()
{
	return _pContext;
}


void TestCase::resetContext(Poco::OSP::BundleContext::Ptr pContext)
{
	_pContext = pContext;
}


} } } // namespace Poco::OSP::Unit
