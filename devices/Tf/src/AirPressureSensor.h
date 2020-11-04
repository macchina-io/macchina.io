//
// AirPressureSensor.h
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Tf_AirPressureSensor_INCLUDED
#define IoT_Tf_AirPressureSensor_INCLUDED


#include "IoT/Tf/Tf.h"
#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "IoT/Tf/MasterConnection.h"
#include "BrickletImpl.h"
#include "bricklet_barometer.h"


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
	bool ready() const;

protected:
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;

	static void onAirPressureChanged(Poco::Int32 airPressure, void* userData);
	
private:
	mutable Barometer _barometer;
	IoT::Devices::MinimumDeltaModerationPolicy<double> _eventPolicy;
};


} } // namespace IoT::Tf


#endif // IoT_Tf_AirPressureSensor_INCLUDED
