//
// Sensor.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Sensor.h"
#include "Node.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


namespace IoT {
namespace CISS {


const std::string Sensor::NAME("CISS Sensor");
const std::string Sensor::TYPE("io.macchina.sensor");
const std::string Sensor::SYMBOLIC_NAME("io.macchina.ciss");


Sensor::Sensor(Node& node, Poco::UInt8 id, Poco::UInt8 streamId, const std::string& physicalQuantity, const std::string& physicalUnit):
	_node(node),
	_sensorId(id),
	_streamId(streamId),
	_ready(false),
	_enabled(false),
	_value(0),
	_valueChangedDelta(0.0),
	_samplingInterval(0),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<double>(valueChanged)),
	_deviceIdentifier(node.id()),
	_physicalQuantity(physicalQuantity),
	_physicalUnit(physicalUnit)
{
	addProperty("displayValue", &Sensor::getDisplayValue);
	addProperty("enabled", &Sensor::getEnabled, &Sensor::setEnabled);
	addProperty("valueChangedDelta", &Sensor::getValueChangedDelta, &Sensor::setValueChangedDelta);
	addProperty("samplingInterval", &Sensor::getSamplingInterval, &Sensor::setSamplingInterval);
	addProperty("connected", &Sensor::getConnected);
	addProperty("deviceIdentifier", &Sensor::getDeviceIdentifier);
	addProperty("symbolicName", &Sensor::getSymbolicName);
	addProperty("name", &Sensor::getName);
	addProperty("type", &Sensor::getType);
	addProperty("physicalQuantity", &Sensor::getPhysicalQuantity);
	addProperty("physicalUnit", &Sensor::getPhysicalUnit);

	_pEventPolicy = new IoT::Devices::NoModerationPolicy<double>(valueChanged);
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
	if (interval < 0 || interval > 65535) throw Poco::InvalidArgumentException("samplingInterval");

	if (interval != _samplingInterval)
	{
		_node.setEnvironmentalSamplingInterval(_sensorId, static_cast<Poco::UInt16>(interval));
		_samplingInterval = interval;
	}
}


Poco::Any Sensor::getDisplayValue(const std::string&) const
{
	if (_ready && _enabled)
		return Poco::NumberFormatter::format(value(), 0, 1);
	else
		return std::string("n/a");
}


Poco::Any Sensor::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
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


} } // namespace IoT::CISS
