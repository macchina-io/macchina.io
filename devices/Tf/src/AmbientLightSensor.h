//
// AmbientLightSensor.h
//
// $Id: //iot/Main/Tf/src/AmbientLightSensor.h#2 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Tf_AmbientLightSensor_INCLUDED
#define IoT_Tf_AmbientLightSensor_INCLUDED


#include "IoT/Tf/Tf.h"
#include "IoT/Devices/Sensor.h"
#include "IoT/Tf/MasterConnection.h"
#include "BrickletImpl.h"
extern "C"
{
#include "bricklet_ambient_light.h"
}

namespace IoT {
namespace Tf {


class IoTTf_API AmbientLightSensor: public BrickletImpl<IoT::Devices::Sensor, AmbientLightSensor>
{
public:
	enum
	{
		DEVICE_IDENTIFIER = AMBIENT_LIGHT_DEVICE_IDENTIFIER
	};
	
	AmbientLightSensor(MasterConnection::Ptr pMasterConn, const std::string& uid);
		/// Creates a AmbientLightSensorImpl.
		
	~AmbientLightSensor();
		/// Destroys the AmbientLightSensorImpl.
	
	// Sensor
	double value() const;

protected:
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);

	static void onIlluminanceChanged(Poco::UInt16 temperature, void* userData);

private:
	mutable AmbientLight _ambientLight;
};


} } // namespace IoT::Tf


#endif // IoT_Tf_AmbientLightSensor_INCLUDED
