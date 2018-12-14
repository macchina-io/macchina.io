//
// GenericCounter.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/GenericCounter.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


namespace IoT {
namespace Devices {


const std::string GenericCounter::TYPE("io.macchina.counter");


GenericCounter::GenericCounter(const std::string& name, const std::string& symbolicName, Poco::Util::Timer& timer):
	_name(name),
	_symbolicName(symbolicName),
	_timer(timer),
	_enabled(false),
	_value(0),
	_valueChangedDelta(0.0),
	_valueChangedPeriod(0),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<Poco::Int32>(countChanged))
{
	addProperty("displayValue", &GenericCounter::getDisplayValue);
	addProperty("enabled", &GenericCounter::getEnabled, &GenericCounter::setEnabled);
	addProperty("valueChangedDelta", &GenericCounter::getValueChangedDelta, &GenericCounter::setValueChangedDelta);
	addProperty("valueChangedPeriod", &GenericCounter::getValueChangedPeriod, &GenericCounter::setValueChangedPeriod);
	addProperty("symbolicName", &GenericCounter::getSymbolicName);
	addProperty("name", &GenericCounter::getName);
	addProperty("type", &GenericCounter::getType);
}


GenericCounter::~GenericCounter()
{
}


Poco::Int32 GenericCounter::count() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _value;
}


Poco::Int32 GenericCounter::reset()
{
	throw Poco::NotImplementedException("Cannot reset a CAN Counter");
}


void GenericCounter::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_enabled = enabled;
}


Poco::Any GenericCounter::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void GenericCounter::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any GenericCounter::getValueChangedDelta(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedDelta;
}


void GenericCounter::setValueChangedDelta(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	double delta = Poco::AnyCast<double>(value);
	if (delta != _valueChangedDelta)
	{
		if (delta == 0)
		{
			_pEventPolicy = new IoT::Devices::NoModerationPolicy<Poco::Int32>(countChanged);
		}
		else
		{
			_pEventPolicy = new IoT::Devices::MinimumDeltaModerationPolicy<Poco::Int32>(countChanged, _value, delta);
		}
		_valueChangedDelta = delta;
	}
}


Poco::Any GenericCounter::getValueChangedPeriod(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedPeriod;
}


void GenericCounter::setValueChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	int period = Poco::AnyCast<int>(value);
	if (period != _valueChangedPeriod)
	{
		if (period == 0)
		{
			_pEventPolicy = new IoT::Devices::NoModerationPolicy<Poco::Int32>(countChanged);
		}
		else
		{
			_pEventPolicy = new IoT::Devices::MaximumRateModerationPolicy<Poco::Int32>(countChanged, _value, period, _timer);
		}
		_valueChangedPeriod = period;
	}
}


Poco::Any GenericCounter::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_enabled)
		return Poco::NumberFormatter::format(_value);
	else
		return std::string("n/a");
}


Poco::Any GenericCounter::getName(const std::string&) const
{
	return _name;
}


Poco::Any GenericCounter::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any GenericCounter::getSymbolicName(const std::string&) const
{
	return _symbolicName;
}


void GenericCounter::update(Poco::Int32 value)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (_enabled)
	{
		if ( _value != value)
		{
			_value = value;
			lock.unlock();

			_pEventPolicy->valueChanged(value);
		}
	}
}


} } // namespace IoT::Devices
