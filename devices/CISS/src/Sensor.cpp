//
// Sensor.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Sensor.h"
#include "Node.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


using namespace std::string_literals;


namespace IoT {
namespace CISS {


const std::string Sensor::TYPE("io.macchina.sensor");
const std::string Sensor::SYMBOLIC_NAME("io.macchina.ciss");


Sensor::Sensor(Node& node, Poco::UInt8 id, Poco::UInt8 streamId, const std::string& physicalQuantity, const std::string& physicalUnit, const std::string& name):
	_node(node),
	_sensorId(id),
	_streamId(streamId),
	_ready(false),
	_enabled(false),
	_value(0),
	_valueChangedDelta(0.0),
	_samplingInterval(0),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<double>(valueChanged)),
	_name(name),
	_deviceIdentifier(node.id()),
	_physicalQuantity(physicalQuantity),
	_physicalUnit(physicalUnit)
{
	addProperty("displayValue"s, &Sensor::getDisplayValue);
	addProperty("enabled"s, &Sensor::getEnabled, &Sensor::setEnabled);
	addProperty("valueChangedDelta"s, &Sensor::getValueChangedDelta, &Sensor::setValueChangedDelta);
	addProperty("samplingInterval"s, &Sensor::getSamplingInterval, &Sensor::setSamplingInterval);
	addProperty("connected"s, &Sensor::getConnected);
	addProperty("deviceIdentifier"s, &Sensor::getDeviceIdentifier);
	addProperty("symbolicName"s, &Sensor::getSymbolicName);
	addProperty("name"s, &Sensor::getName);
	addProperty("type"s, &Sensor::getType);
	addProperty("physicalQuantity"s, &Sensor::getPhysicalQuantity);
	addProperty("physicalUnit"s, &Sensor::getPhysicalUnit);
}


Sensor::~Sensor()
{
}


bool Sensor::isConnected() const
{
	return true;
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

	if (_enabled != enabled)
	{
		_node.enableEnvironmentalSensor(_sensorId, _streamId, enabled);
		_enabled = enabled;
	}
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


Poco::Any Sensor::getConnected(const std::string&) const
{
	return isConnected();
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


Poco::Any Sensor::getSamplingInterval(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _samplingInterval;
}


void Sensor::setSamplingInterval(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	int interval = Poco::AnyCast<int>(value);
	if (interval < 0 || interval > 65535) throw Poco::InvalidArgumentException("samplingInterval"s);

	if (interval != _samplingInterval)
	{
		_node.setEnvironmentalSamplingInterval(_sensorId, static_cast<Poco::UInt16>(interval));
		_samplingInterval = interval;
	}
}


Poco::Any Sensor::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready && _enabled)
		return Poco::NumberFormatter::format(_value, 0, 1);
	else
		return "n/a"s;
}


Poco::Any Sensor::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any Sensor::getName(const std::string&) const
{
	return _name;
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


} } // namespace IoT::CISS
