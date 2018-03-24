//
// BooleanSensor.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/CAN/BooleanSensor.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Exception.h"


namespace IoT {
namespace CAN {


const std::string BooleanSensor::NAME("CAN BooleanSensor");
const std::string BooleanSensor::TYPE("io.macchina.boolean");
const std::string BooleanSensor::SYMBOLIC_NAME("io.macchina.can.boolean");


BooleanSensor::BooleanSensor(const std::string& signal):
	_enabled(false),
	_state(false),
	_signal(signal)
{
	addProperty("displayValue", &BooleanSensor::getDisplayValue);
	addProperty("enabled", &BooleanSensor::getEnabled, &BooleanSensor::setEnabled);
	addProperty("signal", &BooleanSensor::getSignal);
	addProperty("symbolicName", &BooleanSensor::getSymbolicName);
	addProperty("name", &BooleanSensor::getName);
	addProperty("type", &BooleanSensor::getType);
}


BooleanSensor::~BooleanSensor()
{
}


bool BooleanSensor::state() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _state;
}


void BooleanSensor::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_enabled = enabled;
}


Poco::Any BooleanSensor::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void BooleanSensor::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any BooleanSensor::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_enabled)
		return std::string(_state ? "true" : "false");
	else
		return std::string("n/a");
}


Poco::Any BooleanSensor::getSignal(const std::string&) const
{
	return _signal;
}


Poco::Any BooleanSensor::getName(const std::string&) const
{
	return NAME;
}


Poco::Any BooleanSensor::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any BooleanSensor::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


void BooleanSensor::update(bool state)
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


} } // namespace IoT::CAN
