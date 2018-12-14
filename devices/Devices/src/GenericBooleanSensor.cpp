//
// GenericBooleanSensor.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/GenericBooleanSensor.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


namespace IoT {
namespace Devices {


const std::string GenericBooleanSensor::TYPE("io.macchina.boolean");


GenericBooleanSensor::GenericBooleanSensor(const std::string& name, const std::string& symbolicName):
	_name(name),
	_symbolicName(symbolicName),
	_enabled(false),
	_state(false)
{
	addProperty("displayValue", &GenericBooleanSensor::getDisplayValue);
	addProperty("enabled", &GenericBooleanSensor::getEnabled, &GenericBooleanSensor::setEnabled);
	addProperty("symbolicName", &GenericBooleanSensor::getSymbolicName);
	addProperty("name", &GenericBooleanSensor::getName);
	addProperty("type", &GenericBooleanSensor::getType);
}


GenericBooleanSensor::~GenericBooleanSensor()
{
}


bool GenericBooleanSensor::state() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _state;
}


void GenericBooleanSensor::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_enabled = enabled;
}


Poco::Any GenericBooleanSensor::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void GenericBooleanSensor::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any GenericBooleanSensor::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_enabled)
		return std::string(_state ? "true" : "false");
	else
		return std::string("n/a");
}


Poco::Any GenericBooleanSensor::getName(const std::string&) const
{
	return _name;
}


Poco::Any GenericBooleanSensor::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any GenericBooleanSensor::getSymbolicName(const std::string&) const
{
	return _symbolicName;
}


void GenericBooleanSensor::update(bool state)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (_enabled)
	{
		if ( _state != state)
		{
			_state = state;
			lock.unlock();

			stateChanged(this, _state);
		}
	}
}


} } // namespace IoT::Devices
