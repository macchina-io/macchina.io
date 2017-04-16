//
// HighRateButton.cpp
//
// $Id$
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "HighRateButton.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace IoT {
namespace BtLE {
namespace XDK {


const std::string HighRateButton::NAME("XDK Button");
const std::string HighRateButton::SYMBOLIC_NAME("io.macchina.btle.xdk.button");


HighRateButton::HighRateButton(Peripheral::Ptr pPeripheral):
	_pPeripheral(pPeripheral),
	_enabled(false),
	_ready(false),
	_deviceIdentifier(pPeripheral->address()),
	_symbolicName(SYMBOLIC_NAME),
	_name(NAME)
{
	addProperty("displayValue", &HighRateButton::getDisplayValue);
	addProperty("enabled", &HighRateButton::getEnabled, &HighRateButton::setEnabled);
	addProperty("connected", &HighRateButton::getConnected);
	addProperty("deviceIdentifier", &HighRateButton::getDeviceIdentifier);
	addProperty("symbolicName", &HighRateButton::getSymbolicName);
	addProperty("name", &HighRateButton::getName);
	
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
	return _name;
}


Poco::Any HighRateButton::getSymbolicName(const std::string&) const
{
	return _symbolicName;
}


void HighRateButton::update(bool state)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!_ready || state != _state)
	{
		_ready = true;
		_state = state;
		stateChanged(this, _state);
	}
}


void HighRateButton::init()
{
	enable(true);
}


void HighRateButton::onConnected()
{
	if (_enabled)
	{
		enable(true);
	}
}


void HighRateButton::onDisconnected()
{
	enable(false);
}


} } } // namespace IoT::BtLE::XDK

