//
// TemperatureSensor.cpp
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "TemperatureSensor.h"
#include "MasterConnectionImpl.h"
#include "Poco/NumberFormatter.h"


using namespace std::string_literals;


namespace IoT {
namespace Tf {


TemperatureSensor::TemperatureSensor(MasterConnection::Ptr pMasterConn, const std::string& uid):
	BrickletType("io.macchina.tf.temperature"s, "Tinkerforge Temperature Bricklet"s, "io.macchina.sensor"s, "temperature"s, IoT::Devices::Sensor::PHYSICAL_UNIT_DEGREES_CELSIUS),
	_eventPolicy(this->valueChanged, 0.0, 0.0)
{
	addProperty("displayValue"s, &TemperatureSensor::getDisplayValue);
	addProperty("valueChangedPeriod"s, &TemperatureSensor::getValueChangedPeriod, &TemperatureSensor::setValueChangedPeriod);
	addProperty("valueChangedDelta"s, &TemperatureSensor::getValueChangedDelta, &TemperatureSensor::setValueChangedDelta);

	IPConnection *ipcon = pMasterConn.cast<MasterConnectionImpl>()->ipcon();
	temperature_create(&_temperature, uid.c_str(), ipcon);
	
	char deviceUID[8];
	char masterUID[8];
	char position;
	Poco::UInt8 hardwareVersion[3];
	Poco::UInt8 firmwareVersion[3];
	Poco::UInt16 deviceType;
	if (temperature_get_identity(&_temperature, deviceUID, masterUID, &position, hardwareVersion, firmwareVersion, &deviceType) == E_OK)
	{
		setIdentity(deviceUID, masterUID, position, hardwareVersion, firmwareVersion, deviceType);
	}
	
	temperature_register_callback(&_temperature, TEMPERATURE_CALLBACK_TEMPERATURE, reinterpret_cast<void*>(onTemperatureChanged), this);
	temperature_set_temperature_callback_period(&_temperature, 1000);
}

	
TemperatureSensor::~TemperatureSensor()
{
	temperature_destroy(&_temperature);
}


double TemperatureSensor::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::Int16 temp;
	int rc = temperature_get_temperature(&_temperature, &temp);
	if (rc == E_OK)
	{
		return temp/100.0;
	}
	else throw Poco::IOException();
}


bool TemperatureSensor::ready() const
{
	return true;
}


Poco::Any TemperatureSensor::getValueChangedPeriod(const std::string&) const
{
	Poco::UInt32 uperiod;
	temperature_get_temperature_callback_period(&_temperature, &uperiod);
	return Poco::Any(static_cast<int>(uperiod));
}


void TemperatureSensor::setValueChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::UInt32 period = static_cast<Poco::UInt32>(Poco::AnyCast<int>(value));
	temperature_set_temperature_callback_period(&_temperature, period);
}


Poco::Any TemperatureSensor::getValueChangedDelta(const std::string&) const
{
	return Poco::Any(_eventPolicy.getMinimumDelta()/1000.0);
}


void TemperatureSensor::setValueChangedDelta(const std::string&, const Poco::Any& value)
{
	double delta = Poco::AnyCast<double>(value);
	_eventPolicy.setMinimumDelta(delta);
}


Poco::Any TemperatureSensor::getDisplayValue(const std::string&) const
{
	return Poco::NumberFormatter::format(value(), 0, 1);
}


void TemperatureSensor::onTemperatureChanged(Poco::Int16 temperature, void* userData)
{
	try
	{
		TemperatureSensor* pThis = reinterpret_cast<TemperatureSensor*>(userData);
		pThis->_eventPolicy.valueChanged(temperature/100.0);
	}
	catch (...)
	{
	}
}


} } // namespace IoT::Tf
