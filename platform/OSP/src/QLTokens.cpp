//
// QLTokens.cpp
//
// Library: OSP
// Package: Util
// Module:  QLTokens
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/QLTokens.h"
#include "Poco/Exception.h"
#include <cctype>


using Poco::Token;


namespace Poco {
namespace OSP {


//
// QLToken
//


QLToken::QLToken()
{
}


QLToken::~QLToken()
{
}


void QLToken::syntaxError(const std::string& expected, const std::string& actual)
{
	std::string msg("expected: ");
	msg.append(expected);
	msg.append(", got: ");
	msg.append(actual);
	throw Poco::SyntaxException(msg);
}


//
// OperatorToken
//


OperatorToken::OperatorToken()
{
	int i = 1;
	_opMap["("]  = i++;
	_opMap[")"]  = i++;
	_opMap["<"]  = i++;
	_opMap["<="] = i++;
	_opMap[">"]  = i++;
	_opMap[">="] = i++;
	_opMap["=="] = i++;
	_opMap["=~"] = i++;
	_opMap["!"]  = i++;
	_opMap["!="] = i++;
	_opMap["&&"] = i++;
	_opMap["||"] = i++;
}


OperatorToken::~OperatorToken()
{
}


Token::Class OperatorToken::tokenClass() const
{
	return Token::OPERATOR_TOKEN;
}


bool OperatorToken::start(char c, std::istream& istr)
{
	_value = c;
	switch (_value[0])
	{
	case '(':
	case ')':
	case '<':
	case '>':
	case '=':
	case '!':
	case '&':
	case '|':
		return true;
	default:
		return false;
	}
}


void OperatorToken::finish(std::istream& istr)
{
	int next = (char) istr.peek();
	switch (_value[0])
	{
	case '(':
	case ')':
		break;
	case '<':
		if (next == '=') _value += (char) istr.get();
		break;
	case '>':
		if (next == '=') _value += (char) istr.get();
		break;
	case '&':
		if (next == '&')
			_value += (char) istr.get();
		else
			syntaxError("&", std::string(1, next));
		break;
	case '|':
		if (next == '|')
			_value += (char) istr.get();
		else
			syntaxError("|", std::string(1, next));
		break;
	case '=':
		if (next == '~' || next == '=') _value += (char) istr.get();
		break;
	case '!':
		if (next == '=') _value += (char) istr.get();
		break;
	default:
		poco_bugcheck();
	}
}


int OperatorToken::asInteger() const
{
	OpMap::const_iterator it = _opMap.find(_value);
	if (it != _opMap.end())
		return it->second;
	else
		return 0;
}


//
// IdentifierToken
//


IdentifierToken::IdentifierToken()
{
}


IdentifierToken::~IdentifierToken()
{
}


Token::Class IdentifierToken::tokenClass() const
{
	return Token::IDENTIFIER_TOKEN;
}


bool IdentifierToken::start(char c, std::istream& istr)
{
	_value = c;
	return (c >= 'A' && c <= 'Z') ||
	       (c >= 'a' && c <= 'z') ||
	       c == '_';
}


void IdentifierToken::finish(std::istream& istr)
{
	int next = (char) istr.peek();
	while ((next >= 'A' && next <= 'Z') ||
		   (next >= 'a' && next <= 'z') ||
		   (next >= '0' && next <= '9') ||
		    next == '_' || next == '.') 
	{
		_value += (char) istr.get();
		next = istr.peek();
	}
}


//
// StringLiteralToken
//


StringLiteralToken::StringLiteralToken()
{
}


StringLiteralToken::~StringLiteralToken()
{
}


Token::Class StringLiteralToken::tokenClass() const
{
	return Token::STRING_LITERAL_TOKEN;
}


bool StringLiteralToken::start(char c, std::istream& istr)
{
	_value = c;
	return c == '"';
}


void StringLiteralToken::finish(std::istream& istr)
{
	int next = istr.peek();	
	while (next != -1 && next != '"' && next != '\n' && next != '\r')
	{
		if (next == '\\') _value += (char) istr.get();
		_value += (char) istr.get();
		next = istr.peek();
	}
	if (next == '"')
	{
		next = istr.get();
		_value += (char) next;
	}
	else throw SyntaxException("Unterminated string literal");
}


std::string StringLiteralToken::asString() const
{
	std::string result;
	std::string::const_iterator it  = _value.begin();
	std::string::const_iterator end = _value.end();
	if (it != end)
	{
		if (*it == '"') ++it;
		while (it != end && *it != '"')
		{
			if (*it == '\\') ++it;
			if (it != end) result += *it++;
		}
	}
	return result;
}


//
// RegExpToken
//


RegExpToken::RegExpToken()
{
}


RegExpToken::~RegExpToken()
{
}


Token::Class RegExpToken::tokenClass() const
{
	return Token::USER_TOKEN;
}


bool RegExpToken::start(char c, std::istream& istr)
{
	_value = c;
	return c == '/' || c == '#';
}


void RegExpToken::finish(std::istream& istr)
{
	int next = istr.peek();	
	while (next != -1 && next != _value[0] && next != '\n' && next != '\r')
	{
		_value += (char) istr.get();
		next = istr.peek();
	}
	if (next == _value[0])
	{
		next = istr.get();
		_value += (char) next;
	}
	else throw SyntaxException("Unterminated regular expression");
}


std::string RegExpToken::asString() const
{
	std::string result;
	std::string::const_iterator it  = _value.begin();
	std::string::const_iterator end = _value.end();
	if (it != end)
	{
		if (*it == _value[0]) ++it;
		while (it != end && *it != _value[0]) result += *it++;
	}
	return result;
}


//
// NumberLiteralToken
//


NumberLiteralToken::NumberLiteralToken():
	_isFloat(false)
{
}


NumberLiteralToken::~NumberLiteralToken()
{
}


Token::Class NumberLiteralToken::tokenClass() const
{
	return _isFloat ? Token::FLOAT_LITERAL_TOKEN : Token::INTEGER_LITERAL_TOKEN;
}


bool NumberLiteralToken::start(char c, std::istream& istr)
{
	_value = c;
	int next = istr.peek();
	return (c >= '0' && c <= '9') ||
	       (c == '.' && next >= '0' && next <= '9');
}


void NumberLiteralToken::finish(std::istream& istr)
{
	int next = istr.peek();
	_isFloat = false;
	if (_value[0] != '.') // starts with digit
	{
		if (next == 'x')
		{
			_value += (char) istr.get();
			next = istr.peek();
			while (std::isxdigit(next)) { _value += (char) istr.get(); next = istr.peek(); }
			return;
		}
		while (next >= '0' && next <= '9')
		{
			_value += (char) istr.get();
			next = istr.peek();
		}
		if (next == '.')
		{
			next = istr.get();
			next = istr.peek();
			if (next != '.')
			{
				_isFloat = true;
				_value += '.';
			}
			else // double period
			{
				istr.unget();
			}
		}
	}
	else
	{
		_isFloat = true;
		_value += istr.get();
		next = istr.peek();
	}
	while (next >= '0' && next <= '9')
	{
		_value += (char) istr.get();
		next = istr.peek();
	}
	if (next == 'e' || next == 'E')
	{
		_isFloat = true;
		_value += (char) istr.get();
		next = istr.peek();
		if (next == '+' || next == '-')
		{
			_value += (char) istr.get();
			next = istr.peek();
		}
		if (next >= '0' && next <= '9')
		{
			while (next >= '0' && next <= '9')
			{
				_value += (char) istr.get();
				next = istr.peek();
			}
		}
		else
		{
			std::string s(1, (char) next);
			syntaxError("digit", s);
		}
	}
}


} } // namespace Poco::OSP
