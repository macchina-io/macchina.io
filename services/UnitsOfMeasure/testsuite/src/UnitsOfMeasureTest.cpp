//
// UnitsOfMeasureTest.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "UnitsOfMeasureTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "IoT/UnitsOfMeasure/UCUMEssenceParser.h"
#include "Poco/Path.h"
#include "Poco/FileStream.h"
#include "Poco/Exception.h"


using namespace IoT::UnitsOfMeasure;


UnitsOfMeasureTest::UnitsOfMeasureTest(const std::string& name):
	CppUnit::TestCase(name)
{
}


UnitsOfMeasureTest::~UnitsOfMeasureTest()
{
}


void UnitsOfMeasureTest::testFindPrefix()
{
	Prefix::Ptr pPrefix = _pUoM->findPrefix("Y");
	assert (pPrefix);
	assert (pPrefix->name == "yotta");
	assert (pPrefix->code == "Y");
	assert (pPrefix->icode == "YA");
	assert (pPrefix->print == "Y");
	assert (pPrefix->value == 1e24);

	pPrefix = _pUoM->findPrefix("#");
	assert (!pPrefix);
}


void UnitsOfMeasureTest::testFindBaseUnit()
{
	Unit::Ptr pUnit = _pUoM->findUnit("m");
	assert (pUnit);
	assert (pUnit->name == "meter");
	assert (pUnit->code == "m");
	assert (pUnit->icode == "M");
	assert (pUnit->print == "m");
	assert (pUnit->property == "length");
	assert (pUnit->dim == "L");

	pUnit = _pUoM->findUnit("$");
	assert (!pUnit);
}


void UnitsOfMeasureTest::testFindUnit()
{
	Unit::Ptr pUnit = _pUoM->findUnit("N");
	assert (pUnit);
	assert (pUnit->name == "newton");
	assert (pUnit->code == "N");
	assert (pUnit->icode == "N");
	assert (pUnit->print == "N");
	assert (pUnit->property == "force");
	assert (pUnit->dim == "");
	assert (pUnit->metric);
	assert (pUnit->unit == "kg.m/s2");
	assert (pUnit->iunit == "KG.M/S2");
	assert (pUnit->group == "si");
	assert (pUnit->value == 1);
}


void UnitsOfMeasureTest::testResolve()
{
	PrefixedUnit pu = _pUoM->resolve("cm");
	assert (pu.prefix->name == "centi");
	assert (pu.unit->name == "meter");

	pu = _pUoM->resolve("KiBy");
	assert (pu.prefix->name == "kibi");
	assert (pu.unit->name == "byte");

	try
	{
		pu = _pUoM->resolve("kfoo");
		fail("bad code - must throw");
	}
	catch (Poco::NotFoundException&)
	{
	}
}


void UnitsOfMeasureTest::testFormat()
{
	std::string format = _pUoM->format("cm");
	assert (format == "cm");

	format = _pUoM->format("[c]");
	assert (format == "<i>c</i>");

	format = _pUoM->format("xyz");
	assert (format == "xyz");
}


void UnitsOfMeasureTest::setUp()
{
	_pUoM = new UnitsOfMeasureServiceImpl;
	UCUMEssenceParser parser(*_pUoM);
	Poco::Path p(Poco::Path::current());
	while (p.depth() > 0 && p.directory(p.depth() - 1) != "UnitsOfMeasure") p.popDirectory();
	if (p.depth() > 0)
	{
		p.pushDirectory("bundle");
		p.setFileName("ucum-essence.xml");
		Poco::FileInputStream istr(p.toString());
		parser.parse(istr);
	}
	else throw Poco::FileNotFoundException("ucum-essence.xml");
}


void UnitsOfMeasureTest::tearDown()
{
	_pUoM.reset();
}


CppUnit::Test* UnitsOfMeasureTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("UnitsOfMeasureTest");

	CppUnit_addTest(pSuite, UnitsOfMeasureTest, testFindPrefix);
	CppUnit_addTest(pSuite, UnitsOfMeasureTest, testFindBaseUnit);
	CppUnit_addTest(pSuite, UnitsOfMeasureTest, testFindUnit);
	CppUnit_addTest(pSuite, UnitsOfMeasureTest, testResolve);
	CppUnit_addTest(pSuite, UnitsOfMeasureTest, testFormat);

	return pSuite;
}
