//
// EnumDatapointImpl.cpp
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  EnumDatapointImpl
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/EnumDatapointImpl.h"
#include "IoT/Datapoints/Utility.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"
#include "Poco/Format.h"


using namespace std::string_literals;


namespace IoT {
namespace Datapoints {


const std::string EnumDatapointImpl::SYMBOLIC_NAME("io.macchina.datapoint.enum.default");
const std::string EnumDatapointImpl::TYPE("io.macchina.datapoint.enum");


EnumDatapointImpl::EnumDatapointImpl(const std::string& id, const Params& params):
	_id(id),
	_name(params.name),
	_access(params.access),
	_definedValues(params.values),
	_value(params.initialValue.value(0)),
	_valid(params.initialValue.isSpecified())
{
	addProperty("displayValue"s, &EnumDatapointImpl::getDisplayValue);
	addProperty("deviceIdentifier"s, &EnumDatapointImpl::getDeviceIdentifier);
	addProperty("symbolicName"s, &EnumDatapointImpl::getSymbolicName);
	addProperty("name"s, &EnumDatapointImpl::getName);
	addProperty("type"s, &EnumDatapointImpl::getType);
	addProperty("updated"s, &EnumDatapointImpl::getUpdated);
	addProperty("access"s, &EnumDatapointImpl::getAccess);
}


EnumDatapointImpl::~EnumDatapointImpl()
{
}


int EnumDatapointImpl::value() const
{
	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		return _value;
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


Poco::Optional<int> EnumDatapointImpl::validValue() const
{
	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		if (_valid)
			return _value;
		else
			return Poco::Optional<int>();
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


std::string EnumDatapointImpl::stringValue() const
{
	return mapValue(value());
}


Poco::Optional<std::string> EnumDatapointImpl::validStringValue() const
{
	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		if (_valid)
			return mapValue(_value);
		else
			return Poco::Optional<std::string>();
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


void EnumDatapointImpl::update(int value)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		checkedUpdate(value);
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


void EnumDatapointImpl::updateString(const std::string& symbolicName)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		forceUpdateString(symbolicName);
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


std::vector<IoT::Devices::EnumValue> EnumDatapointImpl::definedValues() const
{
	return _definedValues;
}


void EnumDatapointImpl::forceUpdate(int value)
{
	ScopedLock lock(*this);

	checkedUpdate(value);
}


void EnumDatapointImpl::checkedUpdate(int value)
{
	for (const auto& v: _definedValues)
	{
		if (v.value == value)
		{
			ScopedLock lock(*this);
			unsafeUpdate(value);
			return;
		}
	}
	throw Poco::InvalidArgumentException(Poco::format("Numeric enum value %d not defined"s, value));
}


void EnumDatapointImpl::forceUpdateString(const std::string& symbolicName)
{
	int value = mapSymbolicName(symbolicName);
	ScopedLock lock(*this);
	unsafeUpdate(value);
}


void EnumDatapointImpl::invalidate()
{
	ScopedLock lock(*this);

	makeInvalid(_valid);
}


bool EnumDatapointImpl::valid() const
{
	ScopedLock lock(*this);

	return _valid;
}


Poco::Any EnumDatapointImpl::getDisplayValue(const std::string&) const
{	
	return stringValue();
}


Poco::Any EnumDatapointImpl::getDeviceIdentifier(const std::string&) const
{
	return _id;
}


Poco::Any EnumDatapointImpl::getName(const std::string&) const
{
	return _name;
}


Poco::Any EnumDatapointImpl::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any EnumDatapointImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any EnumDatapointImpl::getUpdated(const std::string&) const
{
	return _updated;
}


Poco::Any EnumDatapointImpl::getAccess(const std::string&) const
{
	return Utility::accessString(_access);
}


void EnumDatapointImpl::unsafeUpdate(int value)
{
	_updated.update();
	bool changed = _value != value;
	_value = value;
	makeValid(_valid, _value);
	valueUpdated(_value);
	if (changed) valueChanged(_value);
}


int EnumDatapointImpl::mapSymbolicName(const std::string& symbolicName) const
{
	for (const auto& v: _definedValues)
	{
		if (v.symbolicName == symbolicName)
		{
			return v.value;
		}
	}
	throw Poco::InvalidArgumentException(Poco::format("Symbolic name '%s' not defined"s, symbolicName));
}


const std::string& EnumDatapointImpl::mapValue(int value) const
{
	for (const auto& v: _definedValues)
	{
		if (v.value == value)
		{
			return v.symbolicName;
		}
	}
	throw Poco::InvalidArgumentException(Poco::format("Numeric enum value %d not defined"s, value));
}


} } // namespace IoT::Datapoints
