//
// TemperatureSensor.h
//
// $Id: //iot/Main/Tf/src/TemperatureSensor.h#2 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Tf_TemperatureSensor_INCLUDED
#define IoT_Tf_TemperatureSensor_INCLUDED


#include "IoT/Tf/Tf.h"
#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "IoT/Tf/MasterConnection.h"
#include "BrickletImpl.h"
extern "C"
{
#include "bricklet_temperature.h"
}

namespace IoT {
namespace Tf {


class IoTTf_API TemperatureSensor: public BrickletImpl<IoT::Devices::Sensor, TemperatureSensor>
{
public:
	enum
	{
		DEVICE_IDENTIFIER = TEMPERATURE_DEVICE_IDENTIFIER
	};
	
	TemperatureSensor(MasterConnection::Ptr pMasterConn, const std::string& uid);
		/// Creates a TemperatureSensorImpl.
		
	~TemperatureSensor();
		/// Destroys the TemperatureSensorImpl.
	
	// Sensor
	double value() const;

protected:
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);

	static void onTemperatureChanged(Poco::Int16 temperature, void* userData);
	
private:
	mutable Temperature _temperature;
	IoT::Devices::MinimumDeltaModerationPolicy<double> _eventPolicy;
};


} } // namespace IoT::Tf


#endif // IoT_Tf_TemperatureSensor_INCLUDED
