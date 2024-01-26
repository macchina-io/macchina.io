//
// MovingAverageDatapointImpl.cpp
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  MovingAverageDatapointImpl
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/MovingAverageDatapointImpl.h"
#include "IoT/Datapoints/Utility.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


using namespace std::string_literals;


namespace IoT {
namespace Datapoints {


const std::string MovingAverageDatapointImpl::SYMBOLIC_NAME("io.macchina.datapoint.scalar.moving-average");
const std::string MovingAverageDatapointImpl::TYPE("io.macchina.datapoint.scalar");


MovingAverageDatapointImpl::MovingAverageDatapointImpl(const std::string& id, const Params& params, Poco::Util::Timer& timer):
	_id(id),
	_name(params.name),
	_physicalQuantity(params.physicalQuantity),
	_physicalUnit(params.physicalUnit),
	_access(params.access),
	_samples(params.windowSize),
	_sampleCount(0),
	_value(0.0),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<double>(valueChanged)),
	_timer(timer)
{
	addProperty("displayValue"s, &MovingAverageDatapointImpl::getDisplayValue);
	addProperty("valueChangedPeriod"s, &MovingAverageDatapointImpl::getValueChangedPeriod, &MovingAverageDatapointImpl::setValueChangedPeriod);
	addProperty("valueChangedDelta"s, &MovingAverageDatapointImpl::getValueChangedDelta, &MovingAverageDatapointImpl::setValueChangedDelta);
	addProperty("deviceIdentifier"s, &MovingAverageDatapointImpl::getDeviceIdentifier);
	addProperty("symbolicName"s, &MovingAverageDatapointImpl::getSymbolicName);
	addProperty("name"s, &MovingAverageDatapointImpl::getName);
	addProperty("type"s, &MovingAverageDatapointImpl::getType);
	addProperty("physicalQuantity"s, &MovingAverageDatapointImpl::getPhysicalQuantity);
	addProperty("physicalUnit"s, &MovingAverageDatapointImpl::getPhysicalUnit);
	addProperty("updated"s, &MovingAverageDatapointImpl::getUpdated);
	addProperty("access"s, &MovingAverageDatapointImpl::getAccess);
}


MovingAverageDatapointImpl::~MovingAverageDatapointImpl()
{
}


double MovingAverageDatapointImpl::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_READ)
	{
		return _value;
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


Poco::Optional<double> MovingAverageDatapointImpl::validValue() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_READ)
	{
		if (_sampleCount > 0)
			return _value;
		else
			return Poco::Optional<double>();
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


void MovingAverageDatapointImpl::update(double value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_WRITE)
	{
		unsafeUpdate(value);
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


void MovingAverageDatapointImpl::forceUpdate(double value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	unsafeUpdate(value);
}


void MovingAverageDatapointImpl::invalidate()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_sampleCount != 0)
	{
		_sampleCount = 0;
		invalidated();
	}
}


bool MovingAverageDatapointImpl::valid() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _sampleCount > 0;
}


Poco::Any MovingAverageDatapointImpl::getValueChangedPeriod(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedPeriod;
}


void MovingAverageDatapointImpl::setValueChangedPeriod(const std::string&, const Poco::Any& value)
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


Poco::Any MovingAverageDatapointImpl::getValueChangedDelta(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedDelta;
}


void MovingAverageDatapointImpl::setValueChangedDelta(const std::string&, const Poco::Any& value)
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


Poco::Any MovingAverageDatapointImpl::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_access & ACCESS_READ)
	{
		if (_sampleCount > 0)
		{
			return Poco::NumberFormatter::format(_value, 0, 1);
		}
		else
		{
			return "-"s;
		}
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


Poco::Any MovingAverageDatapointImpl::getDeviceIdentifier(const std::string&) const
{
	return _id;
}


Poco::Any MovingAverageDatapointImpl::getName(const std::string&) const
{
	return _name;
}


Poco::Any MovingAverageDatapointImpl::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any MovingAverageDatapointImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any MovingAverageDatapointImpl::getPhysicalQuantity(const std::string&) const
{
	return _physicalQuantity;
}


Poco::Any MovingAverageDatapointImpl::getPhysicalUnit(const std::string&) const
{
	return _physicalUnit;
}


Poco::Any MovingAverageDatapointImpl::getUpdated(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _updated;
}


Poco::Any MovingAverageDatapointImpl::getAccess(const std::string&) const
{
	return Utility::accessString(_access);
}


void MovingAverageDatapointImpl::unsafeUpdate(double value)
{
	_updated.update();
	std::size_t windowSize = _samples.size();
	_samples[_sampleCount % windowSize] = value;
	_sampleCount++;
	std::size_t n = std::min(windowSize, _sampleCount);
	double newValue = 0.0;
	for (std::size_t i = 0; i < n; i++)
	{
		newValue += _samples[i];
	}
	newValue /= n;
	bool changed = _value != newValue;
	_value = newValue;
	if (_sampleCount == 1)
	{
		validated(_value);
	}
	valueUpdated(_value);
	if (changed) _pEventPolicy->valueChanged(_value);
}


} } // namespace IoT::Datapoints
