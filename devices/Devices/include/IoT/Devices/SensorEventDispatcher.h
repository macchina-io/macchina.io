//
// SensorEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SensorEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SensorEventDispatcher_INCLUDED
#define IoT_Devices_SensorEventDispatcher_INCLUDED


#include "IoT/Devices/SensorRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class SensorEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The base class for analog sensors, such as
	/// temperature or ambient light sensors.
	///
	/// In addition to the methods defined in this interface,
	/// a Sensor implementation should expose the following
	/// properties:
	///   - physicalQuantity (string): The physical quantity that is
	///     being measured by the sensor, e.g. "temperature".
	///   - physicalUnit (string): The physical unit the measured value
	///     is being represented in (e.g. "°C"), UTF-8 encoded.
	///     See the PHYSICAL_UNIT_* strings for predefined values.
	///   - displayValue (string, optional): The current value of the sensor,
	///     formatted as string for display purposes.
{
public:
	SensorEventDispatcher(SensorRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a SensorEventDispatcher.

	virtual ~SensorEventDispatcher();
		/// Destroys the SensorEventDispatcher.

	void event__valueChanged(const void* pSender, const double& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__valueChangedImpl(const std::string& subscriberURI, const double& data);

	static const std::string DEFAULT_NS;
	SensorRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SensorEventDispatcher::remoting__typeId() const
{
	return ISensor::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SensorEventDispatcher_INCLUDED

