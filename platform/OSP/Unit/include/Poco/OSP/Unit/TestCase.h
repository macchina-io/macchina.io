//
// TestCase.h
//
// Library: OSP/Unit
// Package: Unit
// Module:  TestCase
//
// Definition of the TestCase class.
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Unit_TestCase_INCLUDED
#define OSP_Unit_TestCase_INCLUDED


#include "Poco/OSP/Unit/Unit.h"
#include "Poco/OSP/BundleContext.h"
#include "CppUnit/TestCase.h"


namespace CppUnit {

class TestResult;

}


namespace Poco {
namespace OSP {
namespace Unit {


class OSPUnit_API TestCase: public CppUnit::TestCase
	/// The TestCase class. This is a stand-in test case class whose purpose is 
	/// to force capture of POCO exceptions through override of run virtual function.
{
public:	
	TestCase(const std::string& name);
		/// Creates a TestCase.
		
	~TestCase();
		/// Destroys the TestCase.

	virtual void run(CppUnit::TestResult* result);
		/// Performs the test run.
		/// In addition to doing all the work that the parent class' run()
		/// does this function also captures POCO exceptions.
		
	static Poco::OSP::BundleContext::Ptr context();
		/// Returns the bundle context of the test bundle.
		
	static void resetContext(Poco::OSP::BundleContext::Ptr pContext);
		/// Sets the bundle context for all tests to the given one.

private:
	static Poco::OSP::BundleContext::Ptr _pContext;
};


} } } // namespace Poco::OSP::Unit


#endif // OSP_Unit_TestCase_INCLUDED
