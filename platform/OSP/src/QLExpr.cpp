//
// QLExpr.cpp
//
// Library: OSP
// Package: Util
// Module:  QLExpr
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/QLExpr.h"
#include "Poco/OSP/Properties.h"
#include "Poco/NumberParser.h"
#include "Poco/String.h"
#include <typeinfo>


using Poco::NumberParser;
using Poco::AnyCast;


namespace Poco {
namespace OSP {


//
// QLExpr
//


QLExpr::QLExpr()
{
}


QLExpr::~QLExpr()
{
}


//
// QLAndExpr
//


QLAndExpr::QLAndExpr(QLExpr::Ptr pLeft, QLExpr::Ptr pRight):
	_pLeft(pLeft),
	_pRight(pRight)
{
}


QLAndExpr::~QLAndExpr()
{
}


bool QLAndExpr::evaluate(const Properties& props) const
{
	return _pLeft->evaluate(props) && _pRight->evaluate(props);
}


//
// QLOrExpr
//


QLOrExpr::QLOrExpr(QLExpr::Ptr pLeft, QLExpr::Ptr pRight):
	_pLeft(pLeft),
	_pRight(pRight)
{
}


QLOrExpr::~QLOrExpr()
{
}


bool QLOrExpr::evaluate(const Properties& props) const
{
	return _pLeft->evaluate(props) || _pRight->evaluate(props);
}


//
// QLNotExpr
//


QLNotExpr::QLNotExpr(QLExpr::Ptr pExpr):
	_pExpr(pExpr)
{
}


QLNotExpr::~QLNotExpr()
{
}


bool QLNotExpr::evaluate(const Properties& props) const
{
	return !_pExpr->evaluate(props);
}


//
// QLExistsExpr
//


QLExistsExpr::QLExistsExpr(const std::string& prop):
	_prop(prop)
{
}


QLExistsExpr::~QLExistsExpr()
{
}


bool QLExistsExpr::evaluate(const Properties& props) const
{
	return props.has(_prop);
}


//
// QLRelExpr
//


bool QLRelExpr::evaluate(const Properties& props) const
{
	try
	{
		return evaluateImpl(props);
	}
	catch (Poco::Exception&)
	{
		return false;
	}
}


//
// QLEqExpr
//


QLEqExpr::QLEqExpr(const std::string& prop, const Poco::Any& value):
	_prop(prop),
	_value(value)
{
}


QLEqExpr::~QLEqExpr()
{
}


bool QLEqExpr::evaluateImpl(const Properties& props) const
{
	if (_value.type() == typeid(int))
		return props.getInt(_prop, 0) == AnyCast<int>(_value);
	else if (_value.type() == typeid(double))
		return props.getFloat(_prop, 0) == AnyCast<double>(_value);
	else if (_value.type() == typeid(bool))
		return props.getBool(_prop, false) == AnyCast<bool>(_value);
	else if (_value.type() == typeid(std::string))
		return props.get(_prop, "") == AnyCast<std::string>(_value);
	else
		return false;
}


//
// QLNeExpr
//


QLNeExpr::QLNeExpr(const std::string& prop, const Poco::Any& value):
	_prop(prop),
	_value(value)
{
}


QLNeExpr::~QLNeExpr()
{
}


bool QLNeExpr::evaluateImpl(const Properties& props) const
{
	if (_value.type() == typeid(int))
		return props.getInt(_prop, 0) != AnyCast<int>(_value);
	else if (_value.type() == typeid(double))
		return props.getFloat(_prop, 0) != AnyCast<double>(_value);
	else if (_value.type() == typeid(bool))
		return props.getBool(_prop, false) != AnyCast<bool>(_value);
	else if (_value.type() == typeid(std::string))
		return props.get(_prop, "") != AnyCast<std::string>(_value);
	else
		return false;
}


//
// QLLtExpr
//


QLLtExpr::QLLtExpr(const std::string& prop, const Poco::Any& value):
	_prop(prop),
	_value(value)
{
}


QLLtExpr::~QLLtExpr()
{
}


bool QLLtExpr::evaluateImpl(const Properties& props) const
{
	if (_value.type() == typeid(int))
		return props.getInt(_prop, 0) < AnyCast<int>(_value);
	else if (_value.type() == typeid(double))
		return props.getFloat(_prop, 0) < AnyCast<double>(_value);
	else if (_value.type() == typeid(bool))
		return props.getBool(_prop, false) < AnyCast<bool>(_value);
	else if (_value.type() == typeid(std::string))
		return props.get(_prop, "") < AnyCast<std::string>(_value);
	else
		return false;
}


//
// QLLeExpr
//


QLLeExpr::QLLeExpr(const std::string& prop, const Poco::Any& value):
	_prop(prop),
	_value(value)
{
}


QLLeExpr::~QLLeExpr()
{
}


bool QLLeExpr::evaluateImpl(const Properties& props) const
{
	if (_value.type() == typeid(int))
		return props.getInt(_prop, 0) <= AnyCast<int>(_value);
	else if (_value.type() == typeid(double))
		return props.getFloat(_prop, 0) <= AnyCast<double>(_value);
	else if (_value.type() == typeid(bool))
		return props.getBool(_prop, false) <= AnyCast<bool>(_value);
	else if (_value.type() == typeid(std::string))
		return props.get(_prop, "") <= AnyCast<std::string>(_value);
	else
		return false;
}


//
// QLGtExpr
//


QLGtExpr::QLGtExpr(const std::string& prop, const Poco::Any& value):
	_prop(prop),
	_value(value)
{
}


QLGtExpr::~QLGtExpr()
{
}


bool QLGtExpr::evaluateImpl(const Properties& props) const
{
	if (_value.type() == typeid(int))
		return props.getInt(_prop, 0) > AnyCast<int>(_value);
	else if (_value.type() == typeid(double))
		return props.getFloat(_prop, 0) > AnyCast<double>(_value);
	else if (_value.type() == typeid(bool))
		return props.getBool(_prop, false) > AnyCast<bool>(_value);
	else if (_value.type() == typeid(std::string))
		return props.get(_prop, "") > AnyCast<std::string>(_value);
	else
		return false;
}


//
// QLGeExpr
//


QLGeExpr::QLGeExpr(const std::string& prop, const Poco::Any& value):
	_prop(prop),
	_value(value)
{
}


QLGeExpr::~QLGeExpr()
{
}


bool QLGeExpr::evaluateImpl(const Properties& props) const
{
	if (_value.type() == typeid(int))
		return props.getInt(_prop, 0) >= AnyCast<int>(_value);
	else if (_value.type() == typeid(double))
		return props.getFloat(_prop, 0) >= AnyCast<double>(_value);
	else if (_value.type() == typeid(bool))
		return props.getBool(_prop, false) >= AnyCast<bool>(_value);
	else if (_value.type() == typeid(std::string))
		return props.get(_prop, "") >= AnyCast<std::string>(_value);
	else
		return false;
}


//
// QLMatchExpr
//


QLMatchExpr::QLMatchExpr(const std::string& prop, const std::string& expr):
	_prop(prop),
	_expr(expr)
{
}


QLMatchExpr::~QLMatchExpr()
{
}


bool QLMatchExpr::evaluate(const Properties& props) const
{
	std::string prop(props.get(_prop, ""));
	return match(_expr.begin(), _expr.end(), prop.begin(), prop.end());
}


bool QLMatchExpr::match(std::string::const_iterator itp, const std::string::const_iterator& endp, std::string::const_iterator its, const std::string::const_iterator& ends) const
{
	while (itp != endp)
	{
		if (its == ends)
		{
			while (itp != endp && *itp == '*') ++itp;
			break;
		}
		switch (*itp)
		{
		case '?':
			++itp; ++its;
			break;
		case '*':
			if (++itp != endp)
			{
				while (its != ends && !match(itp, endp, its, ends)) ++its;
				return its != ends;
			}
			return true;
		case '[':
			if (++itp != endp) 
			{
				bool invert = *itp == '!';
				if (invert) ++itp;
				if (itp != endp)
				{
					bool mtch = matchSet(itp, endp, *its++);
					if ((invert && mtch) || (!invert && !mtch)) return false;
					break;
				}
			}
			throw Poco::SyntaxException("bad range syntax in pattern");
		case '\\':
			if (++itp == endp) throw Poco::SyntaxException("backslash must be followed by character in pattern");
			// fallthrough
		default:
			if (*itp != *its) return false;
			++itp; ++its;
		}
	}
	return itp == endp && its == ends;
}


bool QLMatchExpr::matchSet(std::string::const_iterator& itp, const std::string::const_iterator& endp, char c) const
{
	while (itp != endp)
	{
		switch (*itp)
		{
		case ']':
			++itp; 
			return false;
		case '\\':
			if (++itp == endp) throw Poco::SyntaxException("backslash must be followed by character in glob pattern");
		}
		char first = *itp;
		char last  = first;
		if (++itp != endp && *itp == '-')
		{
			if (++itp != endp)
				last = *itp++;
			else
				throw Poco::SyntaxException("bad range syntax in glob pattern");
		}
		if (first <= c && c <= last)
		{
			while (itp != endp)
			{
				switch (*itp)
				{
				case ']':
					++itp;
					return true;
				case '\\':
					if (++itp == endp) break;
				default:
					++itp;
				}
			}
			throw Poco::SyntaxException("range must be terminated by closing bracket in glob pattern");
		}
	}
	return false;
}


//
// QLMatchRegExpr
//


QLMatchRegExpr::QLMatchRegExpr(const std::string& prop, const std::string& expr):
	_prop(prop),
	_expr(expr)
{
}


QLMatchRegExpr::~QLMatchRegExpr()
{
}


bool QLMatchRegExpr::evaluate(const Properties& props) const
{
	std::string prop(props.get(_prop, ""));
	return _expr.match(prop);
}


//
// QLTrueExpr
//


QLTrueExpr::QLTrueExpr()
{
}


bool QLTrueExpr::evaluate(const Properties& props) const
{
	return true;
}


} } // namespace Poco::OSP
