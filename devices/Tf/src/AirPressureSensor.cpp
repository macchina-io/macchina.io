//
// AirPressureSensor.cpp
//
// $Id: //iot/Main/Tf/src/AirPressureSensor.cpp#2 $
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "AirPressureSensor.h"
#include "MasterConnectionImpl.h"
#include "Poco/NumberFormatter.h"


namespace IoT {
namespace Tf {


AirPressureSensor::AirPressureSensor(MasterConnection::Ptr pMasterConn, const std::string& uid):
	BrickletType("io.macchina.tf.barometer", "Tinkerforge Barometer Bricklet", "io.macchina.sensor", "AirPressure", IoT::Devices::Sensor::PHYSICAL_UNIT_MBAR),
	_eventPolicy(this->valueChanged, 0.0, 0.0)
{
	addProperty("displayValue", &AirPressureSensor::getDisplayValue);
	addProperty("valueChangedPeriod", &AirPressureSensor::getValueChangedPeriod, &AirPressureSensor::setValueChangedPeriod);
	addProperty("valueChangedDelta", &AirPressureSensor::getValueChangedDelta, &AirPressureSensor::setValueChangedDelta);

	IPConnection *ipcon = pMasterConn.cast<MasterConnectionImpl>()->ipcon();
	barometer_create(&_barometer, uid.c_str(), ipcon);
	
	char deviceUID[8];
	char masterUID[8];
	char position;
	Poco::UInt8 hardwareVersion[3];
	Poco::UInt8 firmwareVersion[3];
	Poco::UInt16 deviceType;
	if (barometer_get_identity(&_barometer, deviceUID, masterUID, &position, hardwareVersion, firmwareVersion, &deviceType) == E_OK)
	{
		setIdentity(deviceUID, masterUID, position, hardwareVersion, firmwareVersion, deviceType);
	}
	
	barometer_register_callback(&_barometer, BAROMETER_CALLBACK_AIR_PRESSURE, reinterpret_cast<void*>(onAirPressureChanged), this);
	barometer_set_air_pressure_callback_period(&_barometer, 1000);
}

	
AirPressureSensor::~AirPressureSensor()
{
	barometer_destroy(&_barometer);
}


double AirPressureSensor::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::Int32 airPressure;
	int rc = barometer_get_air_pressure(&_barometer, &airPressure);
	if (rc == E_OK)
	{
		return airPressure/1000.0;
	}
	else throw Poco::IOException();
}


bool AirPressureSensor::ready() const
{
	return true;
}


Poco::Any AirPressureSensor::getValueChangedPeriod(const std::string&) const
{
	Poco::UInt32 uperiod;
	barometer_get_air_pressure_callback_period(&_barometer, &uperiod);
	return Poco::Any(static_cast<int>(uperiod));
}


void AirPressureSensor::setValueChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::UInt32 period = static_cast<Poco::UInt32>(Poco::AnyCast<int>(value));
	barometer_set_air_pressure_callback_period(&_barometer, period);
}


Poco::Any AirPressureSensor::getValueChangedDelta(const std::string&) const
{
	return Poco::Any(_eventPolicy.getMinimumDelta()/1000.0);
}


void AirPressureSensor::setValueChangedDelta(const std::string&, const Poco::Any& value)
{
	double delta = Poco::AnyCast<double>(value);
	_eventPolicy.setMinimumDelta(delta);
}


Poco::Any AirPressureSensor::getDisplayValue(const std::string&) const
{
	return Poco::NumberFormatter::format(value(), 0, 2);
}


void AirPressureSensor::onAirPressureChanged(Poco::Int32 airPressure, void* userData)
{
	try
	{
		AirPressureSensor* pThis = reinterpret_cast<AirPressureSensor*>(userData);
		pThis->_eventPolicy.valueChanged(airPressure/1000.0);
	}
	catch (...)
	{
	}
}


} } // namespace IoT::Tf
