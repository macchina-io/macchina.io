//
// ScalarDatapointImpl.cpp
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  ScalarDatapointImpl
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/ScalarDatapointImpl.h"
#include "IoT/Datapoints/Utility.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


using namespace std::string_literals;


namespace IoT {
namespace Datapoints {


const std::string ScalarDatapointImpl::SYMBOLIC_NAME("io.macchina.datapoint.scalar.default");
const std::string ScalarDatapointImpl::TYPE("io.macchina.datapoint.scalar");


ScalarDatapointImpl::ScalarDatapointImpl(const std::string& id, const Params& params, Poco::Util::Timer& timer):
	_id(id),
	_name(params.name),
	_physicalQuantity(params.physicalQuantity),
	_physicalUnit(params.physicalUnit),
	_access(params.access),
	_value(params.initialValue.value(0.0)),
	_valid(params.initialValue.isSpecified()),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<double>(valueChanged)),
	_timer(timer)
{
	addProperty("displayValue"s, &ScalarDatapointImpl::getDisplayValue);
	addProperty("valueChangedPeriod"s, &ScalarDatapointImpl::getValueChangedPeriod, &ScalarDatapointImpl::setValueChangedPeriod);
	addProperty("valueChangedDelta"s, &ScalarDatapointImpl::getValueChangedDelta, &ScalarDatapointImpl::setValueChangedDelta);
	addProperty("deviceIdentifier"s, &ScalarDatapointImpl::getDeviceIdentifier);
	addProperty("symbolicName"s, &ScalarDatapointImpl::getSymbolicName);
	addProperty("name"s, &ScalarDatapointImpl::getName);
	addProperty("type"s, &ScalarDatapointImpl::getType);
	addProperty("physicalQuantity"s, &ScalarDatapointImpl::getPhysicalQuantity);
	addProperty("physicalUnit"s, &ScalarDatapointImpl::getPhysicalUnit);
	addProperty("updated"s, &ScalarDatapointImpl::getUpdated);
	addProperty("access"s, &ScalarDatapointImpl::getAccess);
}


ScalarDatapointImpl::~ScalarDatapointImpl()
{
}


double ScalarDatapointImpl::value() const
{
	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		return _value;
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


Poco::Optional<double> ScalarDatapointImpl::validValue() const
{
	ScopedLock lock(*this);

	if (_access & ACCESS_READ)
	{
		if (_valid)
			return _value;
		else
			return Poco::Optional<double>();
	}
	else throw Poco::InvalidAccessException("not readable"s);
}


void ScalarDatapointImpl::update(double value)
{
	ScopedLock lock(*this);

	if (_access & ACCESS_WRITE)
	{
		unsafeUpdate(value);
	}
	else throw Poco::InvalidAccessException("not writable"s);
}


void ScalarDatapointImpl::forceUpdate(double value)
{
	ScopedLock lock(*this);

	unsafeUpdate(value);
}


void ScalarDatapointImpl::invalidate()
{
	ScopedLock lock(*this);

	makeInvalid(_valid);
}


bool ScalarDatapointImpl::valid() const
{
	ScopedLock lock(*this);

	return _valid;
}


Poco::Any ScalarDatapointImpl::getValueChangedPeriod(const std::string&) const
{
	return _valueChangedPeriod;
}


void ScalarDatapointImpl::setValueChangedPeriod(const std::string&, const Poco::Any& value)
{
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


Poco::Any ScalarDatapointImpl::getValueChangedDelta(const std::string&) const
{
	return _valueChangedDelta;
}


void ScalarDatapointImpl::setValueChangedDelta(const std::string&, const Poco::Any& value)
{
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


Poco::Any ScalarDatapointImpl::getDisplayValue(const std::string&) const
{
	if (_access & ACCESS_READ)
	{
		if (_valid)
		{
			return Poco::NumberFormatter::format(_value, 0, 1);
		}
		else return "-"s;
	}
	else throw Poco::InvalidAccessException("not readable"s); 
}


Poco::Any ScalarDatapointImpl::getDeviceIdentifier(const std::string&) const
{
	return _id;
}


Poco::Any ScalarDatapointImpl::getName(const std::string&) const
{
	return _name;
}


Poco::Any ScalarDatapointImpl::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any ScalarDatapointImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any ScalarDatapointImpl::getPhysicalQuantity(const std::string&) const
{
	return _physicalQuantity;
}


Poco::Any ScalarDatapointImpl::getPhysicalUnit(const std::string&) const
{
	return _physicalUnit;
}


Poco::Any ScalarDatapointImpl::getUpdated(const std::string&) const
{
	return _updated;
}


Poco::Any ScalarDatapointImpl::getAccess(const std::string&) const
{
	return Utility::accessString(_access);
}


void ScalarDatapointImpl::unsafeUpdate(double value)
{
	_updated.update();
	bool changed = _value != value;
	_value = value;
	makeValid(_valid, _value);
	valueUpdated(_value);
	if (changed) _pEventPolicy->valueChanged(value);
}


} } // namespace IoT::Datapoints
