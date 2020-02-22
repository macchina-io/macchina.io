//
// Gyroscope.cpp
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Gyroscope.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace ROS {
namespace Devices {


const std::string Gyroscope::NAME("ROS Gyroscope");
const std::string Gyroscope::TYPE("io.macchina.gyroscope");
const std::string Gyroscope::SYMBOLIC_NAME("io.macchina.ros.gyroscope");


Gyroscope::Gyroscope():
	_enabled(false),
	_ready(false)
{
	addProperty("displayValue", &Gyroscope::getDisplayValue);
	addProperty("enabled", &Gyroscope::getEnabled, &Gyroscope::setEnabled);
	addProperty("connected", &Gyroscope::getConnected);
	addProperty("symbolicName", &Gyroscope::getSymbolicName);
	addProperty("name", &Gyroscope::getName);
	addProperty("type", &Gyroscope::getType);
}


Gyroscope::~Gyroscope()
{
}


bool Gyroscope::isConnected() const
{
	return true;
}


IoT::Devices::Rotation Gyroscope::rotation() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _rotation;
}


void Gyroscope::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_enabled != enabled)
	{
		_enabled = enabled;
	}
}


Poco::Any Gyroscope::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void Gyroscope::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any Gyroscope::getConnected(const std::string&) const
{
	return isConnected();
}


Poco::Any Gyroscope::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready && _enabled)
		return Poco::format("x=%.2f y=%.2f z=%.2f", _rotation.x, _rotation.y, _rotation.z);
	else
		return std::string("n/a");
}


Poco::Any Gyroscope::getName(const std::string&) const
{
	return NAME;
}


Poco::Any Gyroscope::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any Gyroscope::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


void Gyroscope::update(const IoT::Devices::Rotation& rotation)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (_enabled)
	{
		if (!_ready || rotation.x != _rotation.x || rotation.y != _rotation.y || rotation.z != _rotation.z)
		{
			_ready = true;
			_rotation = rotation;
			lock.unlock();

			rotationChanged(this, rotation);
		}
	}
}


} } } // namespace IoT::ROS::Devices
