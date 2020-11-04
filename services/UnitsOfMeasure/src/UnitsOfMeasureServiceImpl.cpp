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
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/UnitsOfMeasure/UnitsOfMeasureServiceImpl.h"
#include "Poco/Exception.h"
#include "Poco/Format.h"


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
	PrefixedUnit result = tryResolve(code);
	if (result.unit)
		return result;
	else
		throw Poco::NotFoundException(code);
}


std::string UnitsOfMeasureServiceImpl::format(const std::string& code) const
{
	try
	{
		std::string result;
		PrefixedUnit pu = tryResolve(code);
		if (pu.unit)
		{
			if (pu.prefix) result += pu.prefix->print;
			result += pu.unit->print;
		}
		else
		{
			std::string::size_type pos = code.find('/');
			if (pos != std::string::npos)
			{
				std::string upper(code, 0, pos);
				std::string lower(code, pos + 1);
				result = format(upper) + "/" + format(lower);
			}
			else
			{
				if (code.size() > 1 && (code[code.size() - 1] == '2' || code[code.size() - 1 ] == '3'))
				{
					result = format(code.substr(0, code.size() - 1));
					result += code[code.size() - 1] == '2' ? "²" : "³";
				}
				else result = code;
			}
		}
		return result;
	}
	catch (Poco::NotFoundException&)
	{
		return code;
	}
}


CanonicalValue UnitsOfMeasureServiceImpl::canonicalize(double value, const std::string& prefixedCode) const
{
	CanonicalValue result;
	PrefixedUnit pu = resolve(prefixedCode);
	if (pu.prefix)
	{
		result.value = value*pu.prefix->value;
		result.code  = pu.unit->code;
	}
	else
	{
		result.value = value;
		result.code  = pu.unit->code;
	}
	return result;
}


double UnitsOfMeasureServiceImpl::convert(double value, const std::string& fromPrefixedCode, const std::string& toPrefixedCode) const
{
	try
	{
		PrefixedUnit target = resolve(toPrefixedCode);
		CanonicalValue base = convertToBase(value, fromPrefixedCode);
		double converted = convertFromBase(base.value, target.unit->code, base.code);
		if (target.prefix)
			return converted/target.prefix->value;
		else
			return converted;
	}
	catch (Poco::InvalidArgumentException&)
	{
		throw Poco::InvalidArgumentException(Poco::format("No conversion possible from %s to %s", fromPrefixedCode, toPrefixedCode));
	}
}


CanonicalValue UnitsOfMeasureServiceImpl::convertToBase(double value, const std::string& code) const
{
	CanonicalValue result;
	if (code == "Cel")
	{
		result.value = value + 273.15;
		result.code = "K";
	}
	else if (code == "[degF]")
	{
		result.value = (value + 459.67)*5.0/9.0;
		result.code = "K";
	}
	else
	{
		result = canonicalize(value, code);
		Unit::Ptr pUnit = findUnit(result.code);
		if (pUnit)
		{
			Unit::Ptr pBase = findUnit(pUnit->unit);
			while (pBase)
			{
				result = canonicalize(result.value*pUnit->value, pUnit->unit);
				pUnit = findUnit(result.code);
				if (pUnit)
					pBase = findUnit(pBase->unit);
				else
					pBase.reset();
			}
		}
		else throw Poco::NotFoundException(code);
	}
	return result;
}


double UnitsOfMeasureServiceImpl::convertFromBase(double value, const std::string& code, const std::string& base) const
{
	if (code == base)
	{
		return value;
	}
	else if (code == "Cel" && base == "K")
	{
		return value - 273.15;
	}
	else if (code == "[degF]" && base == "K")
	{
		return value*9.0/5.0  - 459.67;
	}
	else
	{
		Unit::Ptr pUnit = findUnit(code);
		if (pUnit)
		{
			PrefixedUnit basePrefixed = tryResolve(pUnit->unit);
			while (basePrefixed.unit)
			{
				CanonicalValue can = reverseCanonicalize(value/pUnit->value, pUnit->unit);
				value = can.value;
				pUnit = findUnit(can.code);
				basePrefixed = tryResolve(pUnit->unit);
			}
			if (pUnit->code == base)
				return value;
			else
				throw Poco::InvalidArgumentException();
		}
		else throw Poco::NotFoundException(code);
	}
}


PrefixedUnit UnitsOfMeasureServiceImpl::tryResolve(const std::string& code) const
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
	return result;
}


CanonicalValue UnitsOfMeasureServiceImpl::reverseCanonicalize(double value, const std::string& prefixedCode) const
{
	CanonicalValue result;
	PrefixedUnit pu = resolve(prefixedCode);
	if (pu.prefix)
	{
		result.value = value/pu.prefix->value;
		result.code  = pu.unit->code;
	}
	else
	{
		result.value = value;
		result.code  = pu.unit->code;
	}
	return result;
}



} } // namespace IoT::UnitsOfMeasure
