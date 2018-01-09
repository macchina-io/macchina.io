//
// Gyroscope.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Gyroscope.h"
#include "Node.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace CISS {


const std::string Gyroscope::NAME("CISS Gyroscope");
const std::string Gyroscope::TYPE("io.macchina.gyroscope");
const std::string Gyroscope::SYMBOLIC_NAME("io.macchina.ciss.gyroscope");


Gyroscope::Gyroscope(Node& node):
	_node(node),
	_samplingInterval(0),
	_enabled(false),
	_ready(false),
	_deviceIdentifier(node.id())
{
	addProperty("displayValue", &Gyroscope::getDisplayValue);
	addProperty("enabled", &Gyroscope::getEnabled, &Gyroscope::setEnabled);
	addProperty("samplingInterval", &Gyroscope::getSamplingInterval, &Gyroscope::setSamplingInterval);
	addProperty("connected", &Gyroscope::getConnected);
	addProperty("deviceIdentifier", &Gyroscope::getDeviceIdentifier);
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
		_node.enableSensor(CISS_SENSOR_ID, enabled);
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


Poco::Any Gyroscope::getSamplingInterval(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _samplingInterval;
}


void Gyroscope::setSamplingInterval(const std::string&, const Poco::Any& value)
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


Poco::Any Gyroscope::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
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


} } // namespace IoT::CISS
