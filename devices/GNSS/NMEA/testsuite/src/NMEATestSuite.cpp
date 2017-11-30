//
// NMEATestSuite.cpp
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "NMEATestSuite.h"
#include "SentenceDecoderTest.h"
#include "RMCProcessorTest.h"
#include "GGAProcessorTest.h"


CppUnit::Test* NMEATestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("NMEATestSuite");

	pSuite->addTest(SentenceDecoderTest::suite());
	pSuite->addTest(RMCProcessorTest::suite());
	pSuite->addTest(GGAProcessorTest::suite());

	return pSuite;
}
