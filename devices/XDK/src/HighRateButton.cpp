//
// HighRateButton.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "HighRateButton.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace XDK {


const std::string HighRateButton::NAME("XDK Button");
const std::string HighRateButton::TYPE("io.macchina.trigger");
const std::string HighRateButton::SYMBOLIC_NAME("io.macchina.xdk.button");


HighRateButton::HighRateButton(BtLE::Peripheral::Ptr pPeripheral):
	_pPeripheral(pPeripheral),
	_enabled(false),
	_ready(false),
	_deviceIdentifier(pPeripheral->address())
{
	addProperty("displayValue", &HighRateButton::getDisplayValue);
	addProperty("enabled", &HighRateButton::getEnabled, &HighRateButton::setEnabled);
	addProperty("connected", &HighRateButton::getConnected);
	addProperty("deviceIdentifier", &HighRateButton::getDeviceIdentifier);
	addProperty("symbolicName", &HighRateButton::getSymbolicName);
	addProperty("name", &HighRateButton::getName);
	addProperty("type", &HighRateButton::getType);

	_pPeripheral->connected += Poco::delegate(this, &HighRateButton::onConnected);
	_pPeripheral->disconnected += Poco::delegate(this, &HighRateButton::onDisconnected);

	init();
}


HighRateButton::~HighRateButton()
{
	_pPeripheral->connected -= Poco::delegate(this, &HighRateButton::onConnected);
	_pPeripheral->disconnected -= Poco::delegate(this, &HighRateButton::onDisconnected);

	_pPeripheral = 0;
}


bool HighRateButton::isConnected() const
{
	return _pPeripheral->isConnected();
}


bool HighRateButton::state() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _state;
}


void HighRateButton::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_enabled = enabled;
}


Poco::Any HighRateButton::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void HighRateButton::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any HighRateButton::getConnected(const std::string&) const
{
	return isConnected();
}


Poco::Any HighRateButton::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready && _enabled)
		return std::string(_state ? "pressed" : "not pressed");
	else
		return std::string("n/a");
}


Poco::Any HighRateButton::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any HighRateButton::getName(const std::string&) const
{
	return NAME;
}


Poco::Any HighRateButton::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any HighRateButton::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


void HighRateButton::update(bool state)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (!_ready || state != _state)
	{
		_ready = true;
		_state = state;
		lock.unlock();

		stateChanged(this, state);
	}
}


void HighRateButton::init()
{
	enable(true);
}


void HighRateButton::onConnected()
{
}


void HighRateButton::onDisconnected()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_ready = false;
}


} } // namespace IoT::XDK
