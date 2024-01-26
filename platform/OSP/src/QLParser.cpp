//
// QLParser.cpp
//
// Library: OSP
// Package: Util
// Module:  QLParser
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/QLParser.h"
#include "Poco/OSP/QLTokens.h"
#include "Poco/Exception.h"


using Poco::Token;
using Poco::Any;
using Poco::SyntaxException;


namespace Poco {
namespace OSP {


QLParser::QLParser(const std::string& expr):
	_istr(expr),
	_tokenizer(_istr)
{
	_tokenizer.addToken(new OperatorToken);
	_tokenizer.addToken(new IdentifierToken);
	_tokenizer.addToken(new StringLiteralToken);
	_tokenizer.addToken(new NumberLiteralToken);
	_tokenizer.addToken(new RegExpToken);
	_tokenizer.addToken(new WhitespaceToken);
}


QLParser::~QLParser()
{
}


QLExpr::Ptr QLParser::parse()
{
	QLExpr::Ptr pExpr;
	const Token* pNext = parseExpr(_tokenizer.next(), pExpr);
	if (pNext->is(Token::EOF_TOKEN))
	{
		if (pExpr)
			return pExpr;
		else
			return new QLTrueExpr;
	}
	else throw SyntaxException("Extra tokens after expression", pNext->asString());
}


const Token* QLParser::parseExpr(const Token* next, QLExpr::Ptr& pExpr)
{
	next = parseAndExpr(next, pExpr);
	while (next->is(Token::OPERATOR_TOKEN) && next->asInteger() == OperatorToken::OP_OR)
	{
		next = _tokenizer.next();
		QLExpr::Ptr pRight;
		next = parseAndExpr(next, pRight);
		pExpr = new QLOrExpr(pExpr, pRight);
	}
	return next;
}


const Token* QLParser::parseAndExpr(const Token* next, QLExpr::Ptr& pExpr)
{
	next = parseRelExpr(next, pExpr);
	while (next->is(Token::OPERATOR_TOKEN) && next->asInteger() == OperatorToken::OP_AND)
	{
		next = _tokenizer.next();
		QLExpr::Ptr pRight;
		next = parseRelExpr(next, pRight);
		pExpr = new QLAndExpr(pExpr, pRight);
	}
	return next;
}


const Token* QLParser::parseRelExpr(const Token* next, QLExpr::Ptr& pExpr)
{
	bool neg = false;
	if (next->is(Token::OPERATOR_TOKEN) && next->asInteger() == OperatorToken::OP_NOT)
	{
		neg = true;
		next = _tokenizer.next();
	}
	if (next->is(Token::OPERATOR_TOKEN) && next->asInteger() == OperatorToken::OP_OPENPARENT)
	{
		next = _tokenizer.next();
		next = parseExpr(next, pExpr);
		if (next->is(Token::OPERATOR_TOKEN) && next->asInteger() == OperatorToken::OP_CLOSPARENT)
			next = _tokenizer.next();
		else
			throw SyntaxException("Expected: ')'");
	}
	else if (next->is(Token::IDENTIFIER_TOKEN))
	{
		std::string prop = next->asString();
		next = _tokenizer.next();
		int op(-1);
		if (isRelOp(next))
		{
			op = next->asInteger();
			next = _tokenizer.next();
			switch (op)
			{
			case OperatorToken::OP_EQ:
				pExpr = new QLEqExpr(prop, token2value(next));
				break;
			case OperatorToken::OP_NE:
				pExpr = new QLNeExpr(prop, token2value(next));
				break;
			case OperatorToken::OP_LT:
				pExpr = new QLLtExpr(prop, token2value(next));
				break;
			case OperatorToken::OP_LE:
				pExpr = new QLLeExpr(prop, token2value(next));
				break;
			case OperatorToken::OP_GT:
				pExpr = new QLGtExpr(prop, token2value(next));
				break;
			case OperatorToken::OP_GE:
				pExpr = new QLGeExpr(prop, token2value(next));
				break;
			case OperatorToken::OP_MATCH:
				if (next->is(Token::STRING_LITERAL_TOKEN))
					pExpr = new QLMatchExpr(prop, next->asString());
				else if (next->is(Token::USER_TOKEN))
					pExpr = new QLMatchRegExpr(prop, next->asString());
				else
					throw SyntaxException("Misplaced token", next->tokenString());
				break;
			default:
				throw SyntaxException("Misplaced token", next->tokenString());
			}
			next = _tokenizer.next();
		}
		else
		{
			pExpr = new QLExistsExpr(prop);
		}
	}
	if (neg)
	{
		pExpr = new QLNotExpr(pExpr);
	}
	return next;
}


bool QLParser::isRelOp(const Poco::Token* token)
{
	if (token->is(Token::OPERATOR_TOKEN))
	{
		switch (token->asInteger())
		{
		case OperatorToken::OP_EQ:
		case OperatorToken::OP_NE:
		case OperatorToken::OP_LT:
		case OperatorToken::OP_LE:
		case OperatorToken::OP_GT:
		case OperatorToken::OP_GE:
		case OperatorToken::OP_MATCH:
			return true;
		}
	}
	return false;
}


Any QLParser::token2value(const Poco::Token* token)
{
	if (token->is(Token::STRING_LITERAL_TOKEN))
		return Any(token->asString());
	else if (token->is(Token::INTEGER_LITERAL_TOKEN))
		return Any(token->asInteger());
	else if (token->is(Token::FLOAT_LITERAL_TOKEN))
		return Any(token->asFloat());
	else if (token->is(Token::IDENTIFIER_TOKEN))
	{
		std::string value = token->asString();
		if (value == "true")
			return Any(true);
		else if (value == "false")
			return Any(false);
		else
			throw SyntaxException("Misplaced identifier", value);
	}
	throw SyntaxException("Misplaced token", token->tokenString());
}


} } // namespace Poco::OSP
