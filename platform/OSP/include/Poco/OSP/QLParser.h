//
// QLParser.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/QLParser.h#1 $
//
// Library: OSP
// Package: Util
// Module:  QLParser
//
// Definition of the QLParser class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_QLParser_INCLUDED
#define OSP_QLParser_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/QLExpr.h"
#include "Poco/StreamTokenizer.h"
#include <sstream>


namespace Poco {
namespace OSP {


class OSP_API QLParser
	/// QLParser implements a parser for property
	/// query expressions, such as used by
	/// the ServiceRegistry.
{
public:
	QLParser(const std::string& expr);
		/// Creates the QLParser for parsing the given
		/// expression.

	~QLParser();
		/// Destroys the QLParser.
		
	QLExpr::Ptr parse();
		/// Parses the expression.
		///
		/// Throws a SyntaxExpression if the expression
		/// is not valid.
		///
		/// The language syntax is as follows:
		///     expr          ::= andExpr ["||" andExpr]
		///     andExpr       ::= relExpr ["&&" relExpr]
		///     relExpr       ::= ["!"] (id [relOp value | "=~" matchExpr]) | subExpr
		///     subExpr       ::= "(" expr ")"
		///     relOp         ::= "==" | "!=" | "<" | "<=" | ">" | ">="
		///     value         ::= numLiteral | boolLiteral | stringLiteral
		///     numLiteral    ::= [sign] digit*"."digit*["E"["+" | "-"]digit*]
		///     boolLiteral   ::= "true" | "false"
		///     stringLiteral ::= """ char* """
		///     matchExpr     ::= stringLiteral | regExpr
		///     regExpr       ::= delim char+ delim /* valid Perl regular expression,
		///                                            enclosed in delim */
		///     delim         ::= "/" | "#"	

protected:
	const Poco::Token* parseExpr(const Poco::Token* next, QLExpr::Ptr& pExpr);
	const Poco::Token* parseAndExpr(const Poco::Token* next, QLExpr::Ptr& pExpr);
	const Poco::Token* parseRelExpr(const Poco::Token* next, QLExpr::Ptr& pExpr);
	bool isRelOp(const Poco::Token* token);
	Poco::Any token2value(const Poco::Token* token);

private:
	QLParser();
	QLParser(const QLParser&);
	QLParser& operator = (const QLParser&);
	
	std::istringstream    _istr;
	Poco::StreamTokenizer _tokenizer;
};


} } // namespace Poco::OSP


#endif // OSP_QLParser_INCLUDED
