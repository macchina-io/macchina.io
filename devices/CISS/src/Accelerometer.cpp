//
// Accelerometer.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Accelerometer.h"
#include "Node.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace CISS {


const std::string Accelerometer::NAME("CISS Accelerometer");
const std::string Accelerometer::TYPE("io.macchina.accelerometer");
const std::string Accelerometer::SYMBOLIC_NAME("io.macchina.ciss.accelerometer");


Accelerometer::Accelerometer(Node& node):
	_node(node),
	_range(16),
	_samplingInterval(0),
	_enabled(false),
	_ready(false),
	_deviceIdentifier(node.id())
{
	addProperty("displayValue", &Accelerometer::getDisplayValue);
	addProperty("enabled", &Accelerometer::getEnabled, &Accelerometer::setEnabled);
	addProperty("range", &Accelerometer::getRange, &Accelerometer::setRange);
	addProperty("samplingInterval", &Accelerometer::getSamplingInterval, &Accelerometer::setSamplingInterval);
	addProperty("connected", &Accelerometer::getConnected);
	addProperty("deviceIdentifier", &Accelerometer::getDeviceIdentifier);
	addProperty("symbolicName", &Accelerometer::getSymbolicName);
	addProperty("name", &Accelerometer::getName);
	addProperty("type", &Accelerometer::getType);
}


Accelerometer::~Accelerometer()
{
}


bool Accelerometer::isConnected() const
{
	return true;
}


IoT::Devices::Acceleration Accelerometer::acceleration() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _acceleration;
}


void Accelerometer::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_enabled != enabled)
	{
		_node.enableSensor(CISS_SENSOR_ID, enabled);
		_enabled = enabled;
	}
}


Poco::Any Accelerometer::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void Accelerometer::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any Accelerometer::getRange(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _range;
}


void Accelerometer::setRange(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	int range = Poco::AnyCast<int>(value);
	if (range < 4 || range > 16) throw Poco::InvalidArgumentException("range");

	if (range != _range)
	{
		_node.setAccelerometerRange(static_cast<Poco::UInt8>(_range));
		_range = range;
	}
}


Poco::Any Accelerometer::getSamplingInterval(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _samplingInterval;
}


void Accelerometer::setSamplingInterval(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	int interval = Poco::AnyCast<int>(value);
	if (interval < 0) throw Poco::InvalidArgumentException("samplingInterval");

	if (interval != _samplingInterval)
	{
		_node.setSamplingInterval(CISS_SENSOR_ID, static_cast<Poco::UInt32>(1000*interval));
		_samplingInterval = interval;
	}
}


Poco::Any Accelerometer::getConnected(const std::string&) const
{
	return isConnected();
}


Poco::Any Accelerometer::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready && _enabled)
		return Poco::format("x=%.2f y=%.2f z=%.2f", _acceleration.x, _acceleration.y, _acceleration.z);
	else
		return std::string("n/a");
}


Poco::Any Accelerometer::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any Accelerometer::getName(const std::string&) const
{
	return NAME;
}


Poco::Any Accelerometer::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any Accelerometer::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


void Accelerometer::update(const IoT::Devices::Acceleration& acceleration)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (_enabled)
	{
		if (!_ready || acceleration.x != _acceleration.x || acceleration.y != _acceleration.y || acceleration.z != _acceleration.z)
		{
			_ready = true;
			_acceleration = acceleration;
			lock.unlock();

			accelerationChanged(this, acceleration);
		}
	}
}


} } // namespace IoT::CISS
