//
// VersionRange.cpp
//
// Library: OSP
// Package: Util
// Module:  VersionRange
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/VersionRange.h"
#include <algorithm>


namespace Poco {
namespace OSP {


VersionRange::VersionRange():
	_includeLower(false),
	_includeUpper(false)
{
}


VersionRange::VersionRange(const Version& ver):
	_lower(ver),
	_upper(ver),
	_includeLower(true),
	_includeUpper(true)
{
}


VersionRange::VersionRange(const Version& lower, bool includeLower, const Version& upper, bool includeUpper):
	_lower(lower),
	_upper(upper),
	_includeLower(includeLower),
	_includeUpper(includeUpper)
{
	poco_assert (lower <= upper);
}


VersionRange::VersionRange(const VersionRange& range):
	_lower(range._lower),
	_upper(range._upper),
	_includeLower(range._includeLower),
	_includeUpper(range._includeUpper)
{
}


VersionRange::~VersionRange()
{
}


VersionRange& VersionRange::operator = (const VersionRange& range)
{
	VersionRange tmp(range);
	swap(tmp);
	return *this;
}


VersionRange& VersionRange::operator = (const Version& ver)
{
	VersionRange tmp(ver);
	swap(tmp);
	return *this;
}


void VersionRange::swap(VersionRange& range)
{
	using std::swap;
	swap(_lower, range._lower);
	swap(_upper, range._upper);
	swap(_includeLower, range._includeLower);
	swap(_includeUpper, range._includeUpper);
}


bool VersionRange::isInRange(const Version& version) const
{
	return ((_includeLower && version == _lower) || version > _lower)
	    && ((_includeUpper && version == _upper) || version < _upper);
}


bool VersionRange::isEmpty() const
{
	return _lower == _upper && !_includeLower;
}


std::string VersionRange::toString() const
{
	std::string result;
	result += _includeLower ? '[' : '(';
	if (!isEmpty())
	{
		result += _lower.toString();
		result += ',';
		result += _upper.toString();
	}
	result += _includeUpper ? ']' : ')';
	return result;
}


} } // namespace Poco::OSP
