//
// HumiditySensor.h
//
// $Id: //iot/Main/Tf/src/HumiditySensor.h#2 $
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Tf_HumiditySensor_INCLUDED
#define IoT_Tf_HumiditySensor_INCLUDED


#include "IoT/Tf/Tf.h"
#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "IoT/Tf/MasterConnection.h"
#include "BrickletImpl.h"
#include "bricklet_humidity.h"


namespace IoT {
namespace Tf {


class IoTTf_API HumiditySensor: public BrickletImpl<IoT::Devices::Sensor, HumiditySensor>
{
public:
	enum
	{
		DEVICE_IDENTIFIER = HUMIDITY_DEVICE_IDENTIFIER
	};
	
	HumiditySensor(MasterConnection::Ptr pMasterConn, const std::string& uid);
		/// Creates a HumiditySensorImpl.
		
	~HumiditySensor();
		/// Destroys the HumiditySensorImpl.
	
	// Sensor
	double value() const;
	bool ready() const;

protected:
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;

	static void onHumidityChanged(Poco::UInt16 humidity, void* userData);

private:
	mutable Humidity _humidity;
	IoT::Devices::MinimumDeltaModerationPolicy<double> _eventPolicy;
};


} } // namespace IoT::Tf


#endif // IoT_Tf_HumiditySensor_INCLUDED
