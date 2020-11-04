//
// Magnetometer.cpp
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Magnetometer.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace ROS {
namespace Devices {


const std::string Magnetometer::NAME("ROS Magnetometer");
const std::string Magnetometer::TYPE("io.macchina.magnetometer");
const std::string Magnetometer::SYMBOLIC_NAME("io.macchina.ros.magnetometer");


Magnetometer::Magnetometer():
	_enabled(false),
	_ready(false)
{
	addProperty("displayValue", &Magnetometer::getDisplayValue);
	addProperty("enabled", &Magnetometer::getEnabled, &Magnetometer::setEnabled);
	addProperty("connected", &Magnetometer::getConnected);
	addProperty("symbolicName", &Magnetometer::getSymbolicName);
	addProperty("name", &Magnetometer::getName);
	addProperty("type", &Magnetometer::getType);
}


Magnetometer::~Magnetometer()
{
}


bool Magnetometer::isConnected() const
{
	return true;
}


IoT::Devices::MagneticFieldStrength Magnetometer::fieldStrength() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _fieldStrength;
}


void Magnetometer::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_enabled != enabled)
	{
		_enabled = enabled;
	}
}


Poco::Any Magnetometer::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void Magnetometer::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any Magnetometer::getConnected(const std::string&) const
{
	return isConnected();
}


Poco::Any Magnetometer::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready && _enabled)
		return Poco::format("x=%.3f y=%.3f z=%.3f", _fieldStrength.x, _fieldStrength.y, _fieldStrength.z);
	else
		return std::string("n/a");
}


Poco::Any Magnetometer::getName(const std::string&) const
{
	return NAME;
}


Poco::Any Magnetometer::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any Magnetometer::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


void Magnetometer::update(const IoT::Devices::MagneticFieldStrength& fieldStrength)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (_enabled)
	{
		if (!_ready || fieldStrength.x != _fieldStrength.x || fieldStrength.y != _fieldStrength.y || fieldStrength.z != _fieldStrength.z || fieldStrength.r != _fieldStrength.r)
		{
			_ready = true;
			_fieldStrength = fieldStrength;
			lock.unlock();
			fieldStrengthChanged(this, fieldStrength);
		}
	}
}


} } } // namespace IoT::ROS::Devices
