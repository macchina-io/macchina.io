//
// Sensor.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/CAN/Sensor.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


namespace IoT {
namespace CAN {


const std::string Sensor::NAME("CAN Sensor");
const std::string Sensor::TYPE("io.macchina.sensor");
const std::string Sensor::SYMBOLIC_NAME("io.macchina.can.sensor");


Sensor::Sensor(Poco::Util::Timer& timer, const std::string& signal, const std::string& physicalQuantity, const std::string& physicalUnit):
	_timer(timer),
	_ready(false),
	_enabled(false),
	_value(0),
	_valueChangedDelta(0.0),
	_valueChangedPeriod(0),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<double>(valueChanged)),
	_signal(signal),
	_physicalQuantity(physicalQuantity),
	_physicalUnit(physicalUnit)
{
	addProperty("displayValue", &Sensor::getDisplayValue);
	addProperty("enabled", &Sensor::getEnabled, &Sensor::setEnabled);
	addProperty("valueChangedDelta", &Sensor::getValueChangedDelta, &Sensor::setValueChangedDelta);
	addProperty("valueChangedPeriod", &Sensor::getValueChangedPeriod, &Sensor::setValueChangedPeriod);
	addProperty("signalI", &Sensor::getSignal);
	addProperty("symbolicName", &Sensor::getSymbolicName);
	addProperty("name", &Sensor::getName);
	addProperty("type", &Sensor::getType);
	addProperty("physicalQuantity", &Sensor::getPhysicalQuantity);
	addProperty("physicalUnit", &Sensor::getPhysicalUnit);
}


Sensor::~Sensor()
{
}


double Sensor::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _value;
}


bool Sensor::ready() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _ready;
}


void Sensor::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_enabled = enabled;
}


Poco::Any Sensor::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void Sensor::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any Sensor::getValueChangedDelta(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedDelta;
}


void Sensor::setValueChangedDelta(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	double delta = Poco::AnyCast<double>(value);
	if (delta != _valueChangedDelta)
	{
		if (delta == 0)
		{
			_pEventPolicy = new IoT::Devices::NoModerationPolicy<double>(valueChanged);
		}
		else
		{
			_pEventPolicy = new IoT::Devices::MinimumDeltaModerationPolicy<double>(valueChanged, _value, delta);
		}
		_valueChangedDelta = delta;
	}
}


Poco::Any Sensor::getValueChangedPeriod(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedPeriod;
}


void Sensor::setValueChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	int period = Poco::AnyCast<int>(value);
	if (period != _valueChangedPeriod)
	{
		if (period == 0)
		{
			_pEventPolicy = new IoT::Devices::NoModerationPolicy<double>(valueChanged);
		}
		else
		{
			_pEventPolicy = new IoT::Devices::MaximumRateModerationPolicy<double>(valueChanged, _value, period, _timer);
		}
		_valueChangedPeriod = period;
	}
}


Poco::Any Sensor::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready && _enabled)
		return Poco::NumberFormatter::format(_value, 0, 1);
	else
		return std::string("n/a");
}


Poco::Any Sensor::getSignal(const std::string&) const
{
	return _signal;
}


Poco::Any Sensor::getName(const std::string&) const
{
	return NAME;
}


Poco::Any Sensor::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any Sensor::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any Sensor::getPhysicalQuantity(const std::string&) const
{
	return _physicalQuantity;
}


Poco::Any Sensor::getPhysicalUnit(const std::string&) const
{
	return _physicalUnit;
}


void Sensor::update(double value)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (_enabled)
	{
		if (!_ready || _value != value)
		{
			_ready = true;
			_value = value;
			lock.unlock();

			_pEventPolicy->valueChanged(value);
		}
	}
}


} } // namespace IoT::CAN
