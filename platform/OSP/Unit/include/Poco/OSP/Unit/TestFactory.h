//
// TestFactory.h
//
// Library: OSP/Unit
// Package: Unit
// Module:  TestFactory
//
// Definition of the TestFactory class.
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
//
//


#ifndef OSP_Unit_TestFactory_INCLUDED
#define OSP_Unit_TestFactory_INCLUDED


#include "Poco/OSP/Unit/Unit.h"
#include "Poco/SharedPtr.h"
#include "Poco/Mutex.h"
#include <vector>
#include <map>


namespace CppUnit {

class Test;

}


namespace Poco {
namespace OSP {
namespace Unit {


class TestCase;


class OSPUnit_API TestFactory
	/// A TestFactory is a singleton class that registers tests.
	/// Multiple tests keyed under the same name can be registered
	/// and later retrieved. Key is typically the bundle name.
{
public:
	using Ptr = Poco::SharedPtr<CppUnit::Test>;
	using TestVec = std::vector<Ptr>;

	TestFactory();
		/// Creates the TestFactory.

	~TestFactory();
		/// Destroys the TestFactory.

	static TestFactory& instance();
		/// Returns the static instance of the singleton.

	void add(const std::string& bundle, CppUnit::Test* pTest);
		/// Registers a test under the given bundle name with the factory.
		/// Takes ownership of parameter pTest.

	void remove(const std::string& bundle);
		/// Removes all tests for given bundle from the factory.

	TestVec get(const std::string& bundle);
		/// Retrieves a vector of tests for the given bundle.

private:
	using TestMap = std::multimap<std::string, Ptr>;

	TestFactory(const TestFactory&);
	TestFactory& operator = (const TestFactory&);

	TestMap         _tests;
	Poco::FastMutex _mutex;
};


} } } // namespace Poco::OSP::Unit


#endif // OSP_Unit_TestFactory_INCLUDED
