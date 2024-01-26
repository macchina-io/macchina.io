//
// LogTestResult.h
//
// Library: OSP/Unit
// Package: Unit
// Module:  LogTestResult
//
// Definition of the LogTestResult class.
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Unit_LogTestResult_INCLUDED
#define OSP_Unit_LogTestResult_INCLUDED


#include "CppUnit/TextTestResult.h"
#include "Poco/OSP/Unit/Unit.h"
#include <ostream>


namespace CppUnit {

class TextTestResult;

};


namespace Poco {
namespace OSP {
namespace Unit {


class OSPUnit_API LogTestResult: public CppUnit::TextTestResult
	/// The LogTestResult class. The purpose of this class is to extend the
	/// CppUnit TextTestResult and bypass default output to std::cout.
{
public:	
	LogTestResult(std::ostream& ostr);
		/// Creates a LogTestResult with supplied ostream as destination.
		/// Typically, ostr will be a Poco::LogStream.

	~LogTestResult();
		/// Destroys the LogTestResult.
	
	virtual void startTest(CppUnit::Test* test);
		/// Calls TextTestResult::startTest() and appends std::endl to the stream.
	
	virtual void print(std::ostream& stream);
		/// Calls TextTestResult::print() and appends std::endl to the stream.

	virtual void printErrors(std::ostream& stream);
		/// Calls TextTestResult::printErrors() and appends std::endl to the stream.

	virtual void printFailures(std::ostream& stream);
		/// Calls TextTestResult::printFailures() and appends std::endl to the stream.

	virtual void printHeader(std::ostream& stream);
		/// Calls TextTestResult::printHeader() and appends std::endl to the stream.

private:
	LogTestResult();
	std::ostream& _ostr;
};


} } } // namespace Poco::OSP::Unit


#endif // OSP_Unit_LogTestResult_INCLUDED
