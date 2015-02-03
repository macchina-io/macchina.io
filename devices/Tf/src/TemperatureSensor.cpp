//
// TemperatureSensor.cpp
//
// $Id: //iot/Main/Tf/src/TemperatureSensor.cpp#2 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "TemperatureSensor.h"
#include "MasterConnectionImpl.h"


namespace IoT {
namespace Tf {


TemperatureSensor::TemperatureSensor(MasterConnection::Ptr pMasterConn, const std::string& uid):
	BrickletType("com.iotframework.tf.temperature", "Tinkerforge Temperature Bricklet")
{
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
}

	
TemperatureSensor::~TemperatureSensor()
{
	temperature_destroy(&_temperature);
}


double TemperatureSensor::value() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::Int16 temp;
	int rc = temperature_get_temperature(&_temperature, &temp);
	if (rc == E_OK)
	{
		return temp/100.0;
	}
	else throw Poco::IOException();
}


} } // namespace IoT::Tf
