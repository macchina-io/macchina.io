//
// QLTokens.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/QLTokens.h#1 $
//
// Library: OSP
// Package: Util
// Module:  QLTokens
//
// Definition of the QLTokens class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_QLTokens_INCLUDED
#define OSP_QLTokens_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/Token.h"
#include <map>


namespace Poco {
namespace OSP {


class OSP_API QLToken: public Poco::Token
	/// The base class for all query language tokens.
{
public:
	QLToken();
	~QLToken();
	
protected:
	void syntaxError(const std::string& expected, const std::string& actual);
};


class OSP_API OperatorToken: public QLToken
{
public:
	enum Tokens
	{
		OP_OPENPARENT = 1,  // (
		OP_CLOSPARENT,      // )
		OP_LT,              // <
		OP_LE,              // <=
		OP_GT,              // >
		OP_GE,              // >=
		OP_EQ,              // ==
		OP_MATCH,           // =~
		OP_NOT,             // !
		OP_NE,              // !=
		OP_AND,             // &&
		OP_OR               // ||
	};
	
	OperatorToken();
	~OperatorToken();
	Poco::Token::Class tokenClass() const;
	bool start(char c, std::istream& istr);
	void finish(std::istream& istr);
	int asInteger() const;
	
private:
	typedef std::map<std::string, int> OpMap;
	
	OpMap _opMap;
};


class OSP_API IdentifierToken: public QLToken
{
public:
	IdentifierToken();
	~IdentifierToken();
	Poco::Token::Class tokenClass() const;
	bool start(char c, std::istream& istr);
	void finish(std::istream& istr);
};


class OSP_API StringLiteralToken: public QLToken
{
public:
	StringLiteralToken();
	~StringLiteralToken();
	Poco::Token::Class tokenClass() const;
	bool start(char c, std::istream& istr);
	void finish(std::istream& istr);
	std::string asString() const;
};


class OSP_API RegExpToken: public QLToken
{
public:
	RegExpToken();
	~RegExpToken();
	Poco::Token::Class tokenClass() const;
	bool start(char c, std::istream& istr);
	void finish(std::istream& istr);
	std::string asString() const;
};


class OSP_API NumberLiteralToken: public QLToken
{
public:
	NumberLiteralToken();
	~NumberLiteralToken();
	Poco::Token::Class tokenClass() const;
	bool start(char c, std::istream& istr);
	void finish(std::istream& istr);
	
private:
	bool _isFloat;
};


} } // namespace Poco::OSP


#endif // OSP_QLTokens_INCLUDED
