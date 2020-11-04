//
// Accelerometer.cpp
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Accelerometer.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace ROS {
namespace Devices {


const std::string Accelerometer::NAME("ROS Accelerometer");
const std::string Accelerometer::TYPE("io.macchina.accelerometer");
const std::string Accelerometer::SYMBOLIC_NAME("io.macchina.ros.accelerometer");


Accelerometer::Accelerometer():
	_enabled(false),
	_ready(false)
{
	addProperty("displayValue", &Accelerometer::getDisplayValue);
	addProperty("enabled", &Accelerometer::getEnabled, &Accelerometer::setEnabled);
	addProperty("connected", &Accelerometer::getConnected);
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


} } } // namespace IoT::ROS::Devices
