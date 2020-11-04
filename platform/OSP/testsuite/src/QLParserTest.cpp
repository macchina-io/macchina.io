//
// QLParserTest.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "QLParserTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/OSP/Properties.h"
#include "Poco/OSP/QLExpr.h"
#include "Poco/OSP/QLParser.h"


using Poco::OSP::Properties;
using Poco::OSP::QLExpr;
using Poco::OSP::QLParser;


namespace
{
	QLExpr::Ptr parse(const std::string& expr)
	{
		QLParser parser(expr);
		return parser.parse();
	}
}


QLParserTest::QLParserTest(const std::string& name): CppUnit::TestCase(name)
{
}


QLParserTest::~QLParserTest()
{
}


void QLParserTest::testParser()
{
	Properties props;
	props.set("s", "foo");
	props.set("n", "42");
	props.set("x", "0.5");
	props.set("t", "true");
	props.set("f", "false");

	QLExpr::Ptr pExpr = parse("s");
	assert (pExpr->evaluate(props));

	pExpr = parse("z");
	assert (!pExpr->evaluate(props));

	pExpr = parse("!z");
	assert (pExpr->evaluate(props));
		
	pExpr = parse("s == \"foo\"");
	assert (pExpr->evaluate(props));

	pExpr = parse("s == \"bar\"");
	assert (!pExpr->evaluate(props));
	
	pExpr = parse("s != \"bar\"");
	assert (pExpr->evaluate(props));

	pExpr = parse("s != \"foo\"");
	assert (!pExpr->evaluate(props));
	
	pExpr = parse("s < \"ggg\"");
	assert (pExpr->evaluate(props));

	pExpr = parse("s <= \"ggg\"");
	assert (pExpr->evaluate(props));

	pExpr = parse("s < \"aaa\"");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s <= \"aaa\"");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s < \"foo\"");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s <= \"foo\"");
	assert (pExpr->evaluate(props));

	pExpr = parse("s > \"eee\"");
	assert (pExpr->evaluate(props));

	pExpr = parse("s >= \"eee\"");
	assert (pExpr->evaluate(props));

	pExpr = parse("s > \"ggg\"");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s >= \"ggg\"");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s > \"foo\"");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s >= \"foo\"");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("n == 42");
	assert (pExpr->evaluate(props));

	pExpr = parse("n != 24");
	assert (pExpr->evaluate(props));

	pExpr = parse("n != 42");
	assert (!pExpr->evaluate(props));

	pExpr = parse("n == 24");
	assert (!pExpr->evaluate(props));
	
	pExpr = parse("n < 100");
	assert (pExpr->evaluate(props));

	pExpr = parse("n > 10");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("t == true");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("f == false");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("x == 0.5");
	assert (pExpr->evaluate(props));

	pExpr = parse("x != 1.5");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("s == \"foo\" && n == 42");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("s == \"foo\" && n == 24");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s == \"bar\" && n == 42");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s == \"foo\" && n == 42 && t == true");
	assert (pExpr->evaluate(props));

	pExpr = parse("s && n && t");
	assert (pExpr->evaluate(props));

	pExpr = parse("s == \"foo\" || n == 42");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("s == \"foo\" || n == 24");
	assert (pExpr->evaluate(props));

	pExpr = parse("s == \"bar\" || n == 42");
	assert (pExpr->evaluate(props));

	pExpr = parse("s == \"bar\" || n == 24");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s == \"bar\" || n == 24 || t == true");
	assert (pExpr->evaluate(props));

	pExpr = parse("s || n || t");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("s == \"bar\" && n == 42 || t == true");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("s == \"foo\" && n == 24 || t == true");
	assert (pExpr->evaluate(props));

	pExpr = parse("s == \"bar\" || n == 24 && t == true");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s == \"bar\" || n == 42 && t == true");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("!s == \"bar\"");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("s == \"foo\" && (n == 24 || t)");
	assert (pExpr->evaluate(props));

	pExpr = parse("s == \"foo\" && (n == 42 && (t || z))");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("s =~ \"f*\"");
	assert (pExpr->evaluate(props));

	pExpr = parse("s =~ \"f*z\"");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s =~ \"f??\"");
	assert (pExpr->evaluate(props));
	
	pExpr = parse("s =~ \"f?z\"");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s =~ \"foo\"");
	assert (pExpr->evaluate(props));

	pExpr = parse("s =~ \"bar\"");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s =~ /foo/");
	assert (pExpr->evaluate(props));

	pExpr = parse("s =~ /.*/");
	assert (pExpr->evaluate(props));

	pExpr = parse("s =~ /f../");
	assert (pExpr->evaluate(props));

	pExpr = parse("s =~ /oo/");
	assert (!pExpr->evaluate(props));

	pExpr = parse("s =~ /.oo/");
	assert (pExpr->evaluate(props));
}


void QLParserTest::setUp()
{
}


void QLParserTest::tearDown()
{
}


CppUnit::Test* QLParserTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("QLParserTest");

	CppUnit_addTest(pSuite, QLParserTest, testParser);

	return pSuite;
}
