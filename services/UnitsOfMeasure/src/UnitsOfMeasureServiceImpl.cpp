//
// UnitsOfMeasureServiceImpl.cpp
//
// Library: IoT/UnitsOfMeasure
// Package: UnitsOfMeasure
// Module:  UnitsOfMeasureServiceImpl
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/UnitsOfMeasure/UnitsOfMeasureServiceImpl.h"


namespace IoT {
namespace UnitsOfMeasure {


UnitsOfMeasureServiceImpl::UnitsOfMeasureServiceImpl()
{
}


UnitsOfMeasureServiceImpl::~UnitsOfMeasureServiceImpl()
{
}


void UnitsOfMeasureServiceImpl::addPrefix(const Prefix& prefix)
{
	_prefixes[prefix.code] = new Prefix(prefix);
}


void UnitsOfMeasureServiceImpl::addUnit(const Unit& unit)
{
	_units[unit.code] = new Unit(unit);
}


Prefix::Ptr UnitsOfMeasureServiceImpl::findPrefix(const std::string& code) const
{
	PrefixMap::const_iterator it = _prefixes.find(code);
	if (it != _prefixes.end())
		return it->second;
	else
		return Prefix::Ptr();
}


Unit::Ptr UnitsOfMeasureServiceImpl::findUnit(const std::string& code) const
{
	UnitMap::const_iterator it = _units.find(code);
	if (it != _units.end())
		return it->second;
	else
		return Unit::Ptr();
}


PrefixedUnit UnitsOfMeasureServiceImpl::resolve(const std::string& code) const
{
	PrefixedUnit result;
	UnitMap::const_iterator itUnit = _units.find(code);
	if (itUnit != _units.end())
	{
		result.unit = itUnit->second;
		return result;
	}
	else if (code.length() > 1)
	{
		std::string::size_type prefixLen = 1;
		while (prefixLen <= 2)
		{
			std::string prefix(code, 0, prefixLen);
			std::string unit(code, prefixLen);
			PrefixMap::const_iterator itPrefix = _prefixes.find(prefix);
			itUnit = _units.find(unit);
			if (itPrefix != _prefixes.end() && itUnit != _units.end())
			{
				result.prefix = itPrefix->second;
				result.unit = itUnit->second;
				return result;
			}
			prefixLen++;
		}
	}
	throw Poco::NotFoundException(code);
}


std::string UnitsOfMeasureServiceImpl::format(const std::string& code) const
{
	try
	{
		std::string result;
		PrefixedUnit pu = resolve(code);
		if (pu.prefix) result += pu.prefix->print;
		result += pu.unit->print;
		return result;
	}
	catch (Poco::NotFoundException&)
	{
		return code;
	}
}


} } // namespace IoT::UnitsOfMeasure
