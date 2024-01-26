//
// CounterDatapointImpl.cpp
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  CounterDatapointImpl
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/CounterDatapointImpl.h"
#include "IoT/Datapoints/Utility.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


using namespace std::string_literals;


namespace IoT {
namespace Datapoints {


const std::string CounterDatapointImpl::SYMBOLIC_NAME("io.macchina.datapoint.counter.default");
const std::string CounterDatapointImpl::TYPE("io.macchina.datapoint.counter");


CounterDatapointImpl::CounterDatapointImpl(const std::string& id, const Params& params):
	_id(id),
	_name(params.name),
	_access(params.access),
	_value(params.initialValue.value(0)),
	_valid(params.initialValue.isSpecified())
{
	addProperty("displayValue"s, &CounterDatapointImpl::getDisplayValue);
	addProperty("deviceIdentifier"s, &CounterDatapointImpl::getDeviceIdentifier);
	addProperty("symbolicName"s, &CounterDatapointImpl::getSymbolicName);
	addProperty("name"s, &CounterDatapointImpl::getName);
	addProperty("type"s, &CounterDatapointImpl::getType);
	addProperty("updated"s, &CounterDatapointImpl::getUpdated);
	addProperty("access"s, &CounterDatapointImpl::getAccess);
}


CounterDatapointImpl::~CounterDatapointImpl()
{
}


CounterDatapointImpl::CounterType CounterDatapointImpl::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_READ)
	{
		return _value;
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


Poco::Optional<CounterDatapointImpl::CounterType> CounterDatapointImpl::validValue() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_READ)
	{
		if (_valid)
			return _value;
		else
			return Poco::Optional<CounterDatapointImpl::CounterType>();
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


CounterDatapointImpl::CounterType CounterDatapointImpl::increment(CounterType delta)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_WRITE)
	{
		return unsafeIncrement(delta);
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


CounterDatapointImpl::CounterType CounterDatapointImpl::forceIncrement(CounterType delta)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return unsafeIncrement(delta);
}


CounterDatapointImpl::CounterType CounterDatapointImpl::reset(CounterType value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_WRITE)
	{
		return unsafeReset(value);
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


CounterDatapointImpl::CounterType CounterDatapointImpl::forceReset(CounterType value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return unsafeReset(value);
}


void CounterDatapointImpl::invalidate()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	makeInvalid(_valid);
}


bool CounterDatapointImpl::valid() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valid;
}


Poco::Any CounterDatapointImpl::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_READ)
	{
		if (_valid)
			return Poco::NumberFormatter::format(_value);
		else
			return "-"s;
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


Poco::Any CounterDatapointImpl::getDeviceIdentifier(const std::string&) const
{
	return _id;
}


Poco::Any CounterDatapointImpl::getName(const std::string&) const
{
	return _name;
}


Poco::Any CounterDatapointImpl::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any CounterDatapointImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any CounterDatapointImpl::getUpdated(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _updated;
}


Poco::Any CounterDatapointImpl::getAccess(const std::string&) const
{
	return Utility::accessString(_access);
}


CounterDatapointImpl::CounterType CounterDatapointImpl::unsafeIncrement(CounterType delta)
{
	_updated.update();
	makeValid(_valid, _value);
	bool changed = delta > 0;
	_value += delta;
	makeValid(_valid, _value);
	if (changed) valueChanged(_value);
	return _value;
}


CounterDatapointImpl::CounterType CounterDatapointImpl::unsafeReset(CounterType value)
{
	CounterDatapointImpl::CounterType lastValue = _value;
	_updated.update();
	_value = value;
	makeValid(_valid, _value);
	if (lastValue != value) valueChanged(_value);
	return lastValue;
}


} } // namespace IoT::Datapoints
