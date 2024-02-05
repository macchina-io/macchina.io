//
// StringDatapointImpl.cpp
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  StringDatapointImpl
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/StringDatapointImpl.h"
#include "IoT/Datapoints/Utility.h"
#include "Poco/Exception.h"


using namespace std::string_literals;


namespace IoT {
namespace Datapoints {


const std::string StringDatapointImpl::SYMBOLIC_NAME("io.macchina.datapoint.string.default");
const std::string StringDatapointImpl::TYPE("io.macchina.datapoint.string");


StringDatapointImpl::StringDatapointImpl(const std::string& id, const Params& params):
	_id(id),
	_name(params.name),
	_access(params.access),
	_value(params.initialValue.value(""s)),
	_valid(params.initialValue.isSpecified())
{
	addProperty("displayValue"s, &StringDatapointImpl::getDisplayValue);
	addProperty("deviceIdentifier"s, &StringDatapointImpl::getDeviceIdentifier);
	addProperty("symbolicName"s, &StringDatapointImpl::getSymbolicName);
	addProperty("name"s, &StringDatapointImpl::getName);
	addProperty("type"s, &StringDatapointImpl::getType);
	addProperty("updated"s, &StringDatapointImpl::getUpdated);
	addProperty("access"s, &StringDatapointImpl::getAccess);
}


StringDatapointImpl::~StringDatapointImpl()
{
}


std::string StringDatapointImpl::value() const
{
	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		return _value;
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


Poco::Optional<std::string> StringDatapointImpl::validValue() const
{
	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		if (_valid)
			return _value;
		else
			return Poco::Optional<std::string>();
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


void StringDatapointImpl::update(const std::string& value)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		unsafeUpdate(value);
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


void StringDatapointImpl::forceUpdate(const std::string& value)
{
	ScopedLock lock(*this);

	unsafeUpdate(value);
}


void StringDatapointImpl::invalidate()
{
	ScopedLock lock(*this);

	makeInvalid(_valid);
}


bool StringDatapointImpl::valid() const
{
	ScopedLock lock(*this);

	return _valid;
}


Poco::Any StringDatapointImpl::getDisplayValue(const std::string&) const
{
	if (_access & ACCESS_READ)
	{
		if (_valid)
			return _value;
		else
			return "-"s;
	}
	else throw Poco::InvalidAccessException("not readable"s); 
}


Poco::Any StringDatapointImpl::getDeviceIdentifier(const std::string&) const
{
	return _id;
}


Poco::Any StringDatapointImpl::getName(const std::string&) const
{
	return _name;
}


Poco::Any StringDatapointImpl::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any StringDatapointImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any StringDatapointImpl::getUpdated(const std::string&) const
{
	return _updated;
}


Poco::Any StringDatapointImpl::getAccess(const std::string&) const
{
	return Utility::accessString(_access);
}


void StringDatapointImpl::unsafeUpdate(const std::string& value)
{
	_updated.update();
	bool changed = _value != value;
	_value = value;
	makeValid(_valid, value);
	valueUpdated(_value);
	if (changed) valueChanged(_value);
}


} } // namespace IoT::Datapoints
