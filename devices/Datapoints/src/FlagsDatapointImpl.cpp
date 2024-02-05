//
// FlagsDatapointImpl.cpp
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  FlagsDatapointImpl
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/FlagsDatapointImpl.h"
#include "IoT/Datapoints/Utility.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"
#include "Poco/Format.h"
#include "Poco/String.h"


using namespace std::string_literals;


namespace IoT {
namespace Datapoints {


const std::string FlagsDatapointImpl::SYMBOLIC_NAME("io.macchina.datapoint.flags.default");
const std::string FlagsDatapointImpl::TYPE("io.macchina.datapoint.flags");


FlagsDatapointImpl::FlagsDatapointImpl(const std::string& id, const Params& params):
	_id(id),
	_name(params.name),
	_access(params.access),
	_definedFlags(params.values),
	_value(params.initialValue.value(std::vector<bool>())),
	_valid(params.initialValue.isSpecified())
{
	std::size_t size = 0;
	for (const auto& f: _definedFlags)
	{
		if (f.bit >= size) size = f.bit + 1;
	}
	_validMask.resize(size, false);
	_value.resize(size, false);
	for (const auto& f: _definedFlags)
	{
		if (!_validMask[f.bit])
		{
			_validMask[f.bit] = true;
		}
		else throw Poco::InvalidAccessException(Poco::format("Duplicate name defined for bit %hu"s, f.bit));
	}

	addProperty("displayValue"s, &FlagsDatapointImpl::getDisplayValue);
	addProperty("deviceIdentifier"s, &FlagsDatapointImpl::getDeviceIdentifier);
	addProperty("symbolicName"s, &FlagsDatapointImpl::getSymbolicName);
	addProperty("name"s, &FlagsDatapointImpl::getName);
	addProperty("type"s, &FlagsDatapointImpl::getType);
	addProperty("updated"s, &FlagsDatapointImpl::getUpdated);
	addProperty("access"s, &FlagsDatapointImpl::getAccess);
}


FlagsDatapointImpl::~FlagsDatapointImpl()
{
}


FlagsDatapointImpl::FlagsType FlagsDatapointImpl::value() const
{
	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		return _value;
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


Poco::Optional<FlagsDatapointImpl::FlagsType> FlagsDatapointImpl::validValue() const
{
	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		if (_valid)
			return _value;
		else
			return Poco::Optional<FlagsDatapointImpl::FlagsType>();
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


std::vector<std::string> FlagsDatapointImpl::flags() const
{
	std::vector<std::string> result;

	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		return mapFlags(_value);
	}
	else throw Poco::InvalidAccessException("not readable"s);

	return result;
}


Poco::Optional<std::vector<std::string>> FlagsDatapointImpl::validFlags() const
{
	std::vector<std::string> result;

	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		if (_valid)
			return mapFlags(_value);
		else
			return Poco::Optional<std::vector<std::string>>();
	}
	else throw Poco::InvalidAccessException("not readable"s);

	return result;
}


FlagsDatapointImpl::FlagsType FlagsDatapointImpl::reset(FlagsType value)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		value.resize(_validMask.size(), false);
		FlagsType previous = _value;
		unsafeUpdate(value);
		return previous;
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


void FlagsDatapointImpl::resetFlags(const std::vector<std::string>& flags)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		unsafeUpdate(mapSymbolicNames(flags));
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


FlagsDatapointImpl::FlagsType FlagsDatapointImpl::set(FlagsType flags)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		flags.resize(_validMask.size(), false);
		FlagsType previous = _value;
		unsafeSet(flags);
		return previous;
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


void FlagsDatapointImpl::setFlags(const std::vector<std::string>& flags)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		FlagsType previous = _value;
		unsafeSet(mapSymbolicNames(flags));
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


FlagsDatapointImpl::FlagsType FlagsDatapointImpl::unset(FlagsType flags)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		flags.resize(_validMask.size(), false);
		FlagsType previous = _value;
		unsafeUnset(flags);
		return previous;
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


void FlagsDatapointImpl::unsetFlags(const std::vector<std::string>& flags)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		FlagsType previous = _value;
		unsafeUnset(mapSymbolicNames(flags));
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


FlagsDatapointImpl::FlagsType FlagsDatapointImpl::toggle(FlagsType flags)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		flags.resize(_validMask.size(), false);
		FlagsType previous = _value;
		unsafeToggle(flags);
		return previous;
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


void FlagsDatapointImpl::toggleFlags(const std::vector<std::string>& flags)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		FlagsType previous = _value;
		unsafeToggle(mapSymbolicNames(flags));
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


std::vector<IoT::Devices::FlagValue> FlagsDatapointImpl::definedFlags() const
{
	return _definedFlags;
}


void FlagsDatapointImpl::invalidate()
{
	ScopedLock lock(*this);

	makeInvalid(_valid);
}


bool FlagsDatapointImpl::valid() const
{
	ScopedLock lock(*this);

	return _valid;
}


Poco::Any FlagsDatapointImpl::getDisplayValue(const std::string&) const
{
	if (_access & ACCESS_READ)
	{
		if (_valid)
		{
			const std::vector<std::string> f = mapFlags(_value);
			return Poco::cat(", "s, f.begin(), f.end());
		}
		else return "-"s;
	}
	else throw Poco::InvalidAccessException("not readable"s); 
}


Poco::Any FlagsDatapointImpl::getDeviceIdentifier(const std::string&) const
{
	return _id;
}


Poco::Any FlagsDatapointImpl::getName(const std::string&) const
{
	return _name;
}


Poco::Any FlagsDatapointImpl::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any FlagsDatapointImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any FlagsDatapointImpl::getUpdated(const std::string&) const
{
	return _updated;
}


Poco::Any FlagsDatapointImpl::getAccess(const std::string&) const
{
	return Utility::accessString(_access);
}


void FlagsDatapointImpl::unsafeUpdate(const FlagsType& value)
{
	poco_assert_dbg (value.size() == _validMask.size());
	
	_updated.update();
	FlagsType newValue(_validMask.size(), false);
	for (std::size_t b = 0; b < _validMask.size(); b++)
	{
		newValue[b] = _validMask[b] && value[b];
	}
	bool changed = newValue != _value;
	_value = std::move(newValue);
	makeValid(_valid, _value);
	valueUpdated(_value);
	if (changed) valueChanged(_value);
}


void FlagsDatapointImpl::unsafeSet(const FlagsType& value)
{
	poco_assert_dbg (value.size() == _validMask.size());

	_updated.update();
	FlagsType newValue(_value);
	for (std::size_t b = 0; b < _validMask.size(); b++)
	{
		newValue[b] = _validMask[b] && (_value[b] || value[b]);
	}
	bool changed = newValue != _value;
	_value = std::move(newValue);
	makeValid(_valid, _value);
	valueUpdated(_value);
	if (changed) valueChanged(_value);
}


void FlagsDatapointImpl::unsafeUnset(const FlagsType& value)
{
	poco_assert_dbg (value.size() == _validMask.size());

	_updated.update();
	FlagsType newValue(_value);
	for (std::size_t b = 0; b < _validMask.size(); b++)
	{
		newValue[b] = _value[b] && !value[b];
	}
	bool changed = newValue != _value;
	_value = std::move(newValue);
	makeValid(_valid, _value);
	valueUpdated(_value);
	if (changed) valueChanged(_value);
}


void FlagsDatapointImpl::unsafeToggle(const FlagsType& value)
{
	poco_assert_dbg (value.size() == _validMask.size());

	_updated.update();
	FlagsType newValue(_value);
	for (std::size_t b = 0; b < _validMask.size(); b++)
	{
		if (value[b]) newValue[b] = !newValue[b];
	}
	bool changed = newValue != _value;
	_value = std::move(newValue);
	makeValid(_valid, _value);
	valueUpdated(_value);
	if (changed) valueChanged(_value);
}


Poco::UInt16 FlagsDatapointImpl::mapSymbolicName(const std::string& symbolicName) const
{
	for (const auto& v: _definedFlags)
	{
		if (v.symbolicName == symbolicName)
		{
			return v.bit;
		}
	}
	throw Poco::InvalidArgumentException(Poco::format("Symbolic flag name '%s' not defined"s, symbolicName));
}


FlagsDatapointImpl::FlagsType FlagsDatapointImpl::mapSymbolicNames(const std::vector<std::string>& symbolicNames) const
{
	FlagsType flags(_validMask.size(), false);
	for (const auto& name: symbolicNames)
	{
		flags[mapSymbolicName(name)] = true;
	}
	return flags;
}


std::vector<std::string> FlagsDatapointImpl::mapFlags(const FlagsType& value) const
{
	std::vector<std::string> result;
	for (const auto& v: _definedFlags)
	{
		if (value[v.bit])
		{
			result.push_back(v.symbolicName);
		}
	}
	return result;
}


} } // namespace IoT::Datapoints
