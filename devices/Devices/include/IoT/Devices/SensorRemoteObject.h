//
// SensorRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SensorRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SensorRemoteObject_INCLUDED
#define IoT_Devices_SensorRemoteObject_INCLUDED


#include "IoT/Devices/ISensor.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class SensorRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::ISensor
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
	typedef Poco::AutoPtr<SensorRemoteObject> Ptr;

	SensorRemoteObject();
		/// Creates a SensorRemoteObject.

	virtual ~SensorRemoteObject();
		/// Destroys the SensorRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& SensorRemoteObject::remoting__typeId() const
{
	return ISensor::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SensorRemoteObject_INCLUDED

