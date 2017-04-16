//
// HighRateGyroscope.cpp
//
// $Id$
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "HighRateGyroscope.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace BtLE {
namespace XDK {


const std::string HighRateGyroscope::NAME("XDK Gyroscope");
const std::string HighRateGyroscope::SYMBOLIC_NAME("io.macchina.btle.xdk.gyroscope");


HighRateGyroscope::HighRateGyroscope(Peripheral::Ptr pPeripheral):
	_pPeripheral(pPeripheral),
	_enabled(false),
	_ready(false),
	_deviceIdentifier(pPeripheral->address()),
	_symbolicName(SYMBOLIC_NAME),
	_name(NAME)
{
	addProperty("displayValue", &HighRateGyroscope::getDisplayValue);
	addProperty("enabled", &HighRateGyroscope::getEnabled, &HighRateGyroscope::setEnabled);
	addProperty("connected", &HighRateGyroscope::getConnected);
	addProperty("deviceIdentifier", &HighRateGyroscope::getDeviceIdentifier);
	addProperty("symbolicName", &HighRateGyroscope::getSymbolicName);
	addProperty("name", &HighRateGyroscope::getName);
	
	_pPeripheral->connected += Poco::delegate(this, &HighRateGyroscope::onConnected);
	_pPeripheral->disconnected += Poco::delegate(this, &HighRateGyroscope::onDisconnected);

	init();
}

	
HighRateGyroscope::~HighRateGyroscope()
{
	_pPeripheral->connected -= Poco::delegate(this, &HighRateGyroscope::onConnected);
	_pPeripheral->disconnected -= Poco::delegate(this, &HighRateGyroscope::onDisconnected);

	_pPeripheral = 0;
}


bool HighRateGyroscope::isConnected() const
{
	return _pPeripheral->isConnected();
}


IoT::Devices::Rotation HighRateGyroscope::rotation() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _rotation;
}


void HighRateGyroscope::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_enabled = enabled;
}


Poco::Any HighRateGyroscope::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void HighRateGyroscope::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any HighRateGyroscope::getConnected(const std::string&) const
{
	return isConnected();
}


Poco::Any HighRateGyroscope::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready && _enabled)
		return Poco::format("x=%.2f y=%.2f z=%.2f", _rotation.x, _rotation.y, _rotation.z);
	else
		return std::string("n/a");
}


Poco::Any HighRateGyroscope::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any HighRateGyroscope::getName(const std::string&) const
{
	return _name;
}


Poco::Any HighRateGyroscope::getSymbolicName(const std::string&) const
{
	return _symbolicName;
}


void HighRateGyroscope::update(const IoT::Devices::Rotation& rotation)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!_ready || rotation.x != _rotation.x || rotation.y != _rotation.y || rotation.z != _rotation.z)
	{
		_ready = true;
		_rotation = rotation;
		rotationChanged(this, _rotation);
	}
}


void HighRateGyroscope::init()
{
	enable(true);
}


void HighRateGyroscope::onConnected()
{
	if (_enabled)
	{
		enable(true);
	}
}


void HighRateGyroscope::onDisconnected()
{
	enable(false);
}


} } } // namespace IoT::BtLE::XDK

