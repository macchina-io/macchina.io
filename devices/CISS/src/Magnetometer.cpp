//
// Magnetometer.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Magnetometer.h"
#include "Node.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace CISS {


const std::string Magnetometer::NAME("CISS Magnetometer");
const std::string Magnetometer::TYPE("io.macchina.magnetometer");
const std::string Magnetometer::SYMBOLIC_NAME("io.macchina.ciss.magnetometer");


Magnetometer::Magnetometer(Node& node):
	_node(node),
	_samplingInterval(0),
	_enabled(false),
	_ready(false),
	_deviceIdentifier(node.id())
{
	addProperty("displayValue", &Magnetometer::getDisplayValue);
	addProperty("enabled", &Magnetometer::getEnabled, &Magnetometer::setEnabled);
	addProperty("samplingInterval", &Magnetometer::getSamplingInterval, &Magnetometer::setSamplingInterval);
	addProperty("connected", &Magnetometer::getConnected);
	addProperty("deviceIdentifier", &Magnetometer::getDeviceIdentifier);
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
		_node.enableSensor(CISS_SENSOR_ID, enabled);
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


Poco::Any Magnetometer::getSamplingInterval(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _samplingInterval;
}


void Magnetometer::setSamplingInterval(const std::string&, const Poco::Any& value)
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


Poco::Any Magnetometer::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
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


} } // namespace IoT::CISS
