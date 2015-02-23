//
// HumiditySensor.cpp
//
// $Id: //iot/Main/Tf/src/HumiditySensor.cpp#2 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "HumiditySensor.h"
#include "MasterConnectionImpl.h"
#include "Poco/NumberFormatter.h"


namespace IoT {
namespace Tf {


HumiditySensor::HumiditySensor(MasterConnection::Ptr pMasterConn, const std::string& uid):
	BrickletType("io.macchina.tf.humidity", "Tinkerforge Humidity Bricklet", "humidity", "%RH"),
	_eventPolicy(this->valueChanged, 0.0, 0.0)
{
	addProperty("displayValue", &HumiditySensor::getDisplayValue);
	addProperty("valueChangedPeriod", &HumiditySensor::getValueChangedPeriod, &HumiditySensor::setValueChangedPeriod);
	addProperty("valueChangedDelta", &HumiditySensor::getValueChangedDelta, &HumiditySensor::setValueChangedDelta);

	IPConnection *ipcon = pMasterConn.cast<MasterConnectionImpl>()->ipcon();
	humidity_create(&_humidity, uid.c_str(), ipcon);
	
	char deviceUID[8];
	char masterUID[8];
	char position;
	Poco::UInt8 hardwareVersion[3];
	Poco::UInt8 firmwareVersion[3];
	Poco::UInt16 deviceType;
	if (humidity_get_identity(&_humidity, deviceUID, masterUID, &position, hardwareVersion, firmwareVersion, &deviceType) == E_OK)
	{
		setIdentity(deviceUID, masterUID, position, hardwareVersion, firmwareVersion, deviceType);
	}
	
	humidity_register_callback(&_humidity, HUMIDITY_CALLBACK_HUMIDITY, reinterpret_cast<void*>(onHumidityChanged), this);
	humidity_set_humidity_callback_period(&_humidity, 1000);
}

	
HumiditySensor::~HumiditySensor()
{
	humidity_destroy(&_humidity);
}


double HumiditySensor::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt16 humidity;
	int rc = humidity_get_humidity(&_humidity, &humidity);
	if (rc == E_OK)
	{
		return humidity/10.0;
	}
	else throw Poco::IOException();
}


Poco::Any HumiditySensor::getValueChangedPeriod(const std::string&) const
{
	Poco::UInt32 uperiod;
	humidity_get_humidity_callback_period(&_humidity, &uperiod);
	return Poco::Any(static_cast<int>(uperiod));
}


void HumiditySensor::setValueChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::UInt32 period = static_cast<Poco::UInt32>(Poco::AnyCast<int>(value));
	humidity_set_humidity_callback_period(&_humidity, period);
}


Poco::Any HumiditySensor::getValueChangedDelta(const std::string&) const
{
	return Poco::Any(_eventPolicy.getMinimumDelta()/1000.0);
}


void HumiditySensor::setValueChangedDelta(const std::string&, const Poco::Any& value)
{
	double delta = Poco::AnyCast<double>(value);
	_eventPolicy.setMinimumDelta(delta);
}


Poco::Any HumiditySensor::getDisplayValue(const std::string&) const
{
	return Poco::NumberFormatter::format(value(), 0, 1);
}


void HumiditySensor::onHumidityChanged(Poco::UInt16 humidity, void* userData)
{
	try
	{
		HumiditySensor* pThis = reinterpret_cast<HumiditySensor*>(userData);
		pThis->_eventPolicy.valueChanged(humidity/10.0);
	}
	catch (...)
	{
	}
}


} } // namespace IoT::Tf
