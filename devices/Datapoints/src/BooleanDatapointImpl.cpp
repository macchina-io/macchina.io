//
// BooleanDatapointImpl.cpp
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  BooleanDatapointImpl
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/BooleanDatapointImpl.h"
#include "IoT/Datapoints/Utility.h"
#include "Poco/Exception.h"


using namespace std::string_literals;


namespace IoT {
namespace Datapoints {


const std::string BooleanDatapointImpl::SYMBOLIC_NAME("io.macchina.datapoint.boolean.default");
const std::string BooleanDatapointImpl::TYPE("io.macchina.datapoint.boolean");


BooleanDatapointImpl::BooleanDatapointImpl(const std::string& id, const Params& params):
	_id(id),
	_name(params.name),
	_access(params.access),
	_value(params.initialValue.value(false)),
	_valid(params.initialValue.isSpecified())
{
	addProperty("displayValue"s, &BooleanDatapointImpl::getDisplayValue);
	addProperty("deviceIdentifier"s, &BooleanDatapointImpl::getDeviceIdentifier);
	addProperty("symbolicName"s, &BooleanDatapointImpl::getSymbolicName);
	addProperty("name"s, &BooleanDatapointImpl::getName);
	addProperty("type"s, &BooleanDatapointImpl::getType);
	addProperty("updated"s, &BooleanDatapointImpl::getUpdated);
	addProperty("access"s, &BooleanDatapointImpl::getAccess);
}


BooleanDatapointImpl::~BooleanDatapointImpl()
{
}


bool BooleanDatapointImpl::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_READ)
	{
		return _value;
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


Poco::Optional<bool> BooleanDatapointImpl::validValue() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_READ)
	{
		if (_valid)
			return _value;
		else
			return Poco::Optional<bool>();
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


bool BooleanDatapointImpl::update(bool value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_WRITE)
	{
		return unsafeUpdate(value);
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


bool BooleanDatapointImpl::invert()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_WRITE)
	{
		return unsafeUpdate(!_value);
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


bool BooleanDatapointImpl::forceUpdate(bool value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return unsafeUpdate(value);
}


void BooleanDatapointImpl::invalidate()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	makeInvalid(_valid);
}


bool BooleanDatapointImpl::valid() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valid;
}


Poco::Any BooleanDatapointImpl::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_READ)
	{
		if (_valid)
			return _value ? "1"s : "0"s;
		else
			return "-"s;
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


Poco::Any BooleanDatapointImpl::getDeviceIdentifier(const std::string&) const
{
	return _id;
}


Poco::Any BooleanDatapointImpl::getName(const std::string&) const
{
	return _name;
}


Poco::Any BooleanDatapointImpl::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any BooleanDatapointImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any BooleanDatapointImpl::getUpdated(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _updated;
}


Poco::Any BooleanDatapointImpl::getAccess(const std::string&) const
{
	return Utility::accessString(_access);
}


bool BooleanDatapointImpl::unsafeUpdate(bool value)
{
	bool previous = _value;
	_updated.update();
	_value = value;
	makeValid(_valid, value);
	valueUpdated(value);
	if (previous != value) valueChanged(value);
	return previous;
}


} } // namespace IoT::Datapoints
