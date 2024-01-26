//
// QLExpr.h
//
// Library: OSP
// Package: Util
// Module:  QLExpr
//
// Definition of the QLExpr class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_QLExpr_INCLUDED
#define OSP_QLExpr_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Any.h"
#include "Poco/RegularExpression.h"


namespace Poco {
namespace OSP {


class Properties;


class OSP_API QLExpr: public Poco::RefCountedObject
	/// The base class for all Query Language expressions.
{
public:
	using Ptr = Poco::AutoPtr<QLExpr>;
	using ConstPtr = const Ptr;

	virtual bool evaluate(const Properties& props) const = 0;
		/// Evaluates the expression on the given properties.

protected:
	QLExpr();
	virtual ~QLExpr();
};


class OSP_API QLAndExpr: public QLExpr
{
public:
	QLAndExpr(QLExpr::Ptr pLeft, QLExpr::Ptr pRight);
	~QLAndExpr();

	bool evaluate(const Properties& props) const;

private:
	QLExpr::Ptr _pLeft;
	QLExpr::Ptr _pRight;
};


class OSP_API QLOrExpr: public QLExpr
{
public:
	QLOrExpr(QLExpr::Ptr pLeft, QLExpr::Ptr pRight);
	~QLOrExpr();

	bool evaluate(const Properties& props) const;

private:
	QLExpr::Ptr _pLeft;
	QLExpr::Ptr _pRight;
};


class OSP_API QLNotExpr: public QLExpr
{
public:
	QLNotExpr(QLExpr::Ptr pExpr);
	~QLNotExpr();

	bool evaluate(const Properties& props) const;

private:
	QLExpr::Ptr _pExpr;
};


class OSP_API QLExistsExpr: public QLExpr
{
public:
	QLExistsExpr(const std::string& prop);
	~QLExistsExpr();

	bool evaluate(const Properties& props) const;

private:
	std::string _prop;
};


class OSP_API QLRelExpr: public QLExpr
{
public:
	bool evaluate(const Properties& props) const;

protected:
	virtual bool evaluateImpl(const Properties& props) const = 0;

private:
	std::string _prop;
	Poco::Any   _value;
};


class OSP_API QLEqExpr: public QLRelExpr
{
public:
	QLEqExpr(const std::string& prop, const Poco::Any& value);
	~QLEqExpr();

protected:
	bool evaluateImpl(const Properties& props) const;

private:
	std::string _prop;
	Poco::Any   _value;
};


class OSP_API QLNeExpr: public QLRelExpr
{
public:
	QLNeExpr(const std::string& prop, const Poco::Any& value);
	~QLNeExpr();

protected:
	bool evaluateImpl(const Properties& props) const;

private:
	std::string _prop;
	Poco::Any   _value;
};


class OSP_API QLLtExpr: public QLRelExpr
{
public:
	QLLtExpr(const std::string& prop, const Poco::Any& value);
	~QLLtExpr();

protected:
	bool evaluateImpl(const Properties& props) const;

private:
	std::string _prop;
	Poco::Any   _value;
};


class OSP_API QLLeExpr: public QLRelExpr
{
public:
	QLLeExpr(const std::string& prop, const Poco::Any& value);
	~QLLeExpr();

protected:
	bool evaluateImpl(const Properties& props) const;

private:
	std::string _prop;
	Poco::Any   _value;
};


class OSP_API QLGtExpr: public QLRelExpr
{
public:
	QLGtExpr(const std::string& prop, const Poco::Any& value);
	~QLGtExpr();

protected:
	bool evaluateImpl(const Properties& props) const;

private:
	std::string _prop;
	Poco::Any   _value;
};


class OSP_API QLGeExpr: public QLRelExpr
{
public:
	QLGeExpr(const std::string& prop, const Poco::Any& value);
	~QLGeExpr();

protected:
	bool evaluateImpl(const Properties& props) const;

private:
	std::string _prop;
	Poco::Any   _value;
};


class OSP_API QLMatchExpr: public QLExpr
{
public:
	QLMatchExpr(const std::string& prop, const std::string& expr);
	~QLMatchExpr();

	bool evaluate(const Properties& props) const;

protected:
	bool match(std::string::const_iterator itp, const std::string::const_iterator& endp, std::string::const_iterator its, const std::string::const_iterator& ends) const;
	bool matchSet(std::string::const_iterator& itp, const std::string::const_iterator& endp, char c) const;

private:
	std::string _prop;
	std::string _expr;
};


class OSP_API QLMatchRegExpr: public QLExpr
{
public:
	QLMatchRegExpr(const std::string& prop, const std::string& expr);
	~QLMatchRegExpr();

	bool evaluate(const Properties& props) const;

private:
	std::string _prop;
	Poco::RegularExpression _expr;
};


class OSP_API QLTrueExpr: public QLExpr
{
public:
	QLTrueExpr();

	bool evaluate(const Properties& props) const;
};


} } // namespace Poco::OSP


#endif // OSP_QLExpr_INCLUDED
