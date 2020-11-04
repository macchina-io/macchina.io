//
// Counter.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/CAN/Counter.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


namespace IoT {
namespace CAN {


const std::string Counter::NAME("CAN Counter");
const std::string Counter::TYPE("io.macchina.counter");
const std::string Counter::SYMBOLIC_NAME("io.macchina.can.counter");


Counter::Counter(Poco::Util::Timer& timer, const std::string& signal):
	_timer(timer),
	_enabled(false),
	_value(0),
	_valueChangedDelta(0.0),
	_valueChangedPeriod(0),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<Poco::Int32>(countChanged)),
	_signal(signal)
{
	addProperty("displayValue", &Counter::getDisplayValue);
	addProperty("enabled", &Counter::getEnabled, &Counter::setEnabled);
	addProperty("valueChangedDelta", &Counter::getValueChangedDelta, &Counter::setValueChangedDelta);
	addProperty("valueChangedPeriod", &Counter::getValueChangedPeriod, &Counter::setValueChangedPeriod);
	addProperty("signal", &Counter::getSignal);
	addProperty("symbolicName", &Counter::getSymbolicName);
	addProperty("name", &Counter::getName);
	addProperty("type", &Counter::getType);
}


Counter::~Counter()
{
}


Poco::Int32 Counter::count() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _value;
}


Poco::Int32 Counter::reset()
{
	throw Poco::NotImplementedException("Cannot reset a CAN Counter");
}


void Counter::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_enabled = enabled;
}


Poco::Any Counter::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void Counter::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any Counter::getValueChangedDelta(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedDelta;
}


void Counter::setValueChangedDelta(const std::string&, const Poco::Any& value)
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


Poco::Any Counter::getValueChangedPeriod(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedPeriod;
}


void Counter::setValueChangedPeriod(const std::string&, const Poco::Any& value)
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


Poco::Any Counter::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_enabled)
		return Poco::NumberFormatter::format(_value);
	else
		return std::string("n/a");
}


Poco::Any Counter::getSignal(const std::string&) const
{
	return _signal;
}


Poco::Any Counter::getName(const std::string&) const
{
	return NAME;
}


Poco::Any Counter::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any Counter::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


void Counter::update(Poco::Int32 value)
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


} } // namespace IoT::CAN
