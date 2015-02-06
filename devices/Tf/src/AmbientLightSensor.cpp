//
// AmbientLightSensor.cpp
//
// $Id: //iot/Main/Tf/src/AmbientLightSensor.cpp#2 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "AmbientLightSensor.h"
#include "MasterConnectionImpl.h"


namespace IoT {
namespace Tf {


AmbientLightSensor::AmbientLightSensor(MasterConnection::Ptr pMasterConn, const std::string& uid):
	BrickletType("io.macchina.tf.ambientlight", "Tinkerforge Ambient Light Bricklet")
{
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
}

	
AmbientLightSensor::~AmbientLightSensor()
{
	ambient_light_destroy(&_ambientLight);
}


double AmbientLightSensor::value() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::UInt16 illuminance;
	int rc = ambient_light_get_illuminance(&_ambientLight, &illuminance);
	if (rc == E_OK)
	{
		return illuminance/10.0;
	}
	else throw Poco::IOException();
}


} } // namespace IoT::Tf
