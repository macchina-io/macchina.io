//
// BundleStreamFactoryTest.h
//
// Definition of the BundleStreamFactoryTest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef BundleStreamFactoryTest_INCLUDED
#define BundleStreamFactoryTest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "CppUnit/TestCase.h"


class BundleStreamFactoryTest: public CppUnit::TestCase
{
public:
	BundleStreamFactoryTest(const std::string& name);
	~BundleStreamFactoryTest();

	void testStreamFactory();
	void testB();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

protected:
	std::string findBundle(const std::string& name);

private:
};


#endif // BundleStreamFactoryTest_INCLUDED
