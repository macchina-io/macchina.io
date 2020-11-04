//
// AmbientLightSensor.cpp
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "AmbientLightSensor.h"
#include "MasterConnectionImpl.h"
#include "Poco/NumberFormatter.h"


namespace IoT {
namespace Tf {


AmbientLightSensor::AmbientLightSensor(MasterConnection::Ptr pMasterConn, const std::string& uid):
	BrickletType("io.macchina.tf.ambientlight", "Tinkerforge Ambient Light Bricklet", "io.macchina.sensor", "illuminance", IoT::Devices::Sensor::PHYSICAL_UNIT_LUX),
	_eventPolicy(this->valueChanged, 0.0, 0.0)
{
	addProperty("displayValue", &AmbientLightSensor::getDisplayValue);
	addProperty("valueChangedPeriod", &AmbientLightSensor::getValueChangedPeriod, &AmbientLightSensor::setValueChangedPeriod);
	addProperty("valueChangedDelta", &AmbientLightSensor::getValueChangedDelta, &AmbientLightSensor::setValueChangedDelta);

	IPConnection *ipcon = pMasterConn.cast<MasterConnectionImpl>()->ipcon();
	ambient_light_create(&_ambientLight, uid.c_str(), ipcon);

	char deviceUID[8];
	char masterUID[8];
	char position;
	Poco::UInt8 hardwareVersion[3];
	Poco::UInt8 firmwareVersion[3];
	Poco::UInt16 deviceType;
	if (ambient_light_get_identity(&_ambientLight, deviceUID, masterUID, &position, hardwareVersion, firmwareVersion, &deviceType) == E_OK)
	{
		setIdentity(deviceUID, masterUID, position, hardwareVersion, firmwareVersion, deviceType);
	}
	
	ambient_light_register_callback(&_ambientLight, AMBIENT_LIGHT_CALLBACK_ILLUMINANCE, reinterpret_cast<void*>(onIlluminanceChanged), this);
	ambient_light_set_illuminance_callback_period(&_ambientLight, 1000);
}

	
AmbientLightSensor::~AmbientLightSensor()
{
	ambient_light_destroy(&_ambientLight);
}


double AmbientLightSensor::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt16 illuminance;
	int rc = ambient_light_get_illuminance(&_ambientLight, &illuminance);
	if (rc == E_OK)
	{
		return illuminance/10.0;
	}
	else throw Poco::IOException();
}


bool AmbientLightSensor::ready() const
{
	return true;
}


Poco::Any AmbientLightSensor::getValueChangedPeriod(const std::string&) const
{
	Poco::UInt32 uperiod;
	ambient_light_get_illuminance_callback_period(&_ambientLight, &uperiod);
	return Poco::Any(static_cast<int>(uperiod));
}


void AmbientLightSensor::setValueChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::UInt32 period = static_cast<Poco::UInt32>(Poco::AnyCast<int>(value));
	ambient_light_set_illuminance_callback_period(&_ambientLight, period);
}


Poco::Any AmbientLightSensor::getValueChangedDelta(const std::string&) const
{
	return Poco::Any(_eventPolicy.getMinimumDelta()/1000.0);
}


void AmbientLightSensor::setValueChangedDelta(const std::string&, const Poco::Any& value)
{
	double delta = Poco::AnyCast<double>(value);
	_eventPolicy.setMinimumDelta(delta);
}


Poco::Any AmbientLightSensor::getDisplayValue(const std::string&) const
{
	return Poco::NumberFormatter::format(value(), 0, 1);
}


void AmbientLightSensor::onIlluminanceChanged(Poco::UInt16 illuminance, void* userData)
{
	try
	{
		AmbientLightSensor* pThis = reinterpret_cast<AmbientLightSensor*>(userData);
		pThis->_eventPolicy.valueChanged(illuminance/10.0);
	}
	catch (...)
	{
	}
}


} } // namespace IoT::Tf
