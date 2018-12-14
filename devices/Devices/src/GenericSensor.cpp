//
// GenericSensor.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/GenericSensor.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


namespace IoT {
namespace Devices {


const std::string GenericSensor::TYPE("io.macchina.sensor");


GenericSensor::GenericSensor(const std::string& name, const std::string& symbolicName, const std::string& physicalQuantity, const std::string& physicalUnit, Poco::Util::Timer& timer):
	_name(name),
	_symbolicName(symbolicName),
	_physicalQuantity(physicalQuantity),
	_physicalUnit(physicalUnit),
	_timer(timer),
	_ready(false),
	_enabled(false),
	_value(0),
	_valueChangedDelta(0.0),
	_valueChangedPeriod(0),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<double>(valueChanged))
{
	addProperty("displayValue", &GenericSensor::getDisplayValue);
	addProperty("enabled", &GenericSensor::getEnabled, &GenericSensor::setEnabled);
	addProperty("valueChangedDelta", &GenericSensor::getValueChangedDelta, &GenericSensor::setValueChangedDelta);
	addProperty("valueChangedPeriod", &GenericSensor::getValueChangedPeriod, &GenericSensor::setValueChangedPeriod);
	addProperty("symbolicName", &GenericSensor::getSymbolicName);
	addProperty("name", &GenericSensor::getName);
	addProperty("type", &GenericSensor::getType);
	addProperty("physicalQuantity", &GenericSensor::getPhysicalQuantity);
	addProperty("physicalUnit", &GenericSensor::getPhysicalUnit);
}


GenericSensor::~GenericSensor()
{
}


double GenericSensor::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _value;
}


bool GenericSensor::ready() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _ready;
}


void GenericSensor::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_enabled = enabled;
}


Poco::Any GenericSensor::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void GenericSensor::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any GenericSensor::getValueChangedDelta(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedDelta;
}


void GenericSensor::setValueChangedDelta(const std::string&, const Poco::Any& value)
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


Poco::Any GenericSensor::getValueChangedPeriod(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedPeriod;
}


void GenericSensor::setValueChangedPeriod(const std::string&, const Poco::Any& value)
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


Poco::Any GenericSensor::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready && _enabled)
		return Poco::NumberFormatter::format(_value, 0, 1);
	else
		return std::string("n/a");
}


Poco::Any GenericSensor::getName(const std::string&) const
{
	return _name;
}


Poco::Any GenericSensor::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any GenericSensor::getSymbolicName(const std::string&) const
{
	return _symbolicName;
}


Poco::Any GenericSensor::getPhysicalQuantity(const std::string&) const
{
	return _physicalQuantity;
}


Poco::Any GenericSensor::getPhysicalUnit(const std::string&) const
{
	return _physicalUnit;
}


void GenericSensor::update(double value)
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


} } // namespace IoT::Devices
