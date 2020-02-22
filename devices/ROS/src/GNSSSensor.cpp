//
// GNSSSensor.cpp
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "GNSSSensor.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace ROS {
namespace Devices {


const std::string GNSSSensor::NAME("ROS GNSS Sensor");
const std::string GNSSSensor::TYPE("io.macchina.gnss");
const std::string GNSSSensor::SYMBOLIC_NAME("io.macchina.ros.gnss");


GNSSSensor::GNSSSensor():
	_enabled(false),
	_ready(false),
	_altitude(0.0)
{
	addProperty("displayValue", &GNSSSensor::getDisplayValue);
	addProperty("enabled", &GNSSSensor::getEnabled, &GNSSSensor::setEnabled);
	addProperty("connected", &GNSSSensor::getConnected);
	addProperty("symbolicName", &GNSSSensor::getSymbolicName);
	addProperty("name", &GNSSSensor::getName);
	addProperty("type", &GNSSSensor::getType);
}


GNSSSensor::~GNSSSensor()
{
}


bool GNSSSensor::isConnected() const
{
	return true;
}


bool GNSSSensor::positionAvailable() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _ready;
}


IoT::Devices::LatLon GNSSSensor::position() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _position.position;
}


double GNSSSensor::course() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _position.course;
}


double GNSSSensor::speed() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _position.speed;
}


double GNSSSensor::magneticVariation() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _position.magneticVariation;
}


double GNSSSensor::altitude() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _altitude;
}


double GNSSSensor::hdop() const
{
	return -9999;
}


void GNSSSensor::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_enabled != enabled)
	{
		_enabled = enabled;
	}
}


Poco::Any GNSSSensor::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void GNSSSensor::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any GNSSSensor::getConnected(const std::string&) const
{
	return isConnected();
}


Poco::Any GNSSSensor::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (positionAvailable())
	{
		IoT::Devices::LatLon latLon = position();
		std::string value = Poco::format("%02.6f,%03.6f", latLon.latitude, latLon.longitude);
		double knots = speed();
		if (knots >= 0) Poco::format(value, " %.2f kn", knots);
		double degrees = course();
		if (degrees >= 0) Poco::format(value, " %.1f°", degrees);
		return value;
	}
	else return std::string("n/a");
}


Poco::Any GNSSSensor::getName(const std::string&) const
{
	return NAME;
}


Poco::Any GNSSSensor::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any GNSSSensor::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


void GNSSSensor::update(const IoT::Devices::PositionUpdate& position, double altitude)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (_enabled)
	{
		if (!_ready || position.position.latitude != _position.position.latitude || position.position.longitude != _position.position.longitude || _altitude != altitude)
		{
			_ready = true;
			_position = position;
			_altitude = altitude;
			lock.unlock();

			positionUpdate(this, _position);
		}
	}
}


} } } // namespace IoT::ROS::Devices
