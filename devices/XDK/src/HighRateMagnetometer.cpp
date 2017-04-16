//
// HighRateMagnetometer.cpp
//
// $Id$
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "HighRateMagnetometer.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace BtLE {
namespace XDK {


const std::string HighRateMagnetometer::NAME("XDK Magnetometer");
const std::string HighRateMagnetometer::SYMBOLIC_NAME("io.macchina.btle.xdk.magnetometer");


HighRateMagnetometer::HighRateMagnetometer(Peripheral::Ptr pPeripheral):
	_pPeripheral(pPeripheral),
	_enabled(false),
	_ready(false),
	_deviceIdentifier(pPeripheral->address()),
	_symbolicName(SYMBOLIC_NAME),
	_name(NAME)
{
	addProperty("displayValue", &HighRateMagnetometer::getDisplayValue);
	addProperty("enabled", &HighRateMagnetometer::getEnabled, &HighRateMagnetometer::setEnabled);
	addProperty("connected", &HighRateMagnetometer::getConnected);
	addProperty("deviceIdentifier", &HighRateMagnetometer::getDeviceIdentifier);
	addProperty("symbolicName", &HighRateMagnetometer::getSymbolicName);
	addProperty("name", &HighRateMagnetometer::getName);
	
	_pPeripheral->connected += Poco::delegate(this, &HighRateMagnetometer::onConnected);
	_pPeripheral->disconnected += Poco::delegate(this, &HighRateMagnetometer::onDisconnected);

	init();
}

	
HighRateMagnetometer::~HighRateMagnetometer()
{
	_pPeripheral->connected -= Poco::delegate(this, &HighRateMagnetometer::onConnected);
	_pPeripheral->disconnected -= Poco::delegate(this, &HighRateMagnetometer::onDisconnected);

	_pPeripheral = 0;
}


bool HighRateMagnetometer::isConnected() const
{
	return _pPeripheral->isConnected();
}


IoT::Devices::MagneticFieldStrength HighRateMagnetometer::fieldStrength() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _fieldStrength;
}


void HighRateMagnetometer::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_enabled = enabled;
}


Poco::Any HighRateMagnetometer::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void HighRateMagnetometer::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any HighRateMagnetometer::getConnected(const std::string&) const
{
	return isConnected();
}


Poco::Any HighRateMagnetometer::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready && _enabled)
		return Poco::format("x=%.2f y=%.2f z=%.2f, r=%.2f", _fieldStrength.x, _fieldStrength.y, _fieldStrength.z, _fieldStrength.r);
	else
		return std::string("n/a");
}


Poco::Any HighRateMagnetometer::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any HighRateMagnetometer::getName(const std::string&) const
{
	return _name;
}


Poco::Any HighRateMagnetometer::getSymbolicName(const std::string&) const
{
	return _symbolicName;
}


void HighRateMagnetometer::update(const IoT::Devices::MagneticFieldStrength& fieldStrength)
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


void HighRateMagnetometer::init()
{
	enable(true);
}


void HighRateMagnetometer::onConnected()
{
}


void HighRateMagnetometer::onDisconnected()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_ready = false;
}


} } } // namespace IoT::BtLE::XDK

