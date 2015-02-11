//
// AirPressureSensor.h
//
// $Id: //iot/Main/Tf/src/AirPressureSensor.h#2 $
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Tf_AirPressureSensor_INCLUDED
#define IoT_Tf_AirPressureSensor_INCLUDED


#include "IoT/Tf/Tf.h"
#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Tf/MasterConnection.h"
#include "BrickletImpl.h"
extern "C"
{
#include "bricklet_barometer.h"
}

namespace IoT {
namespace Tf {


class IoTTf_API AirPressureSensor: public BrickletImpl<IoT::Devices::Sensor, AirPressureSensor>
{
public:
	enum
	{
		DEVICE_IDENTIFIER = BAROMETER_DEVICE_IDENTIFIER
	};
	
	AirPressureSensor(MasterConnection::Ptr pMasterConn, const std::string& uid);
		/// Creates a AirPressureSensorImpl.
		
	~AirPressureSensor();
		/// Destroys the AirPressureSensorImpl.
	
	// Sensor
	double value() const;

protected:
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);

	static void onAirPressureChanged(Poco::Int32 airPressure, void* userData);
	
private:
	mutable Barometer _barometer;
};


} } // namespace IoT::Tf


#endif // IoT_Tf_AirPressureSensor_INCLUDED
