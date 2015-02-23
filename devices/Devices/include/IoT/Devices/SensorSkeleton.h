//
// SensorSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SensorSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SensorSkeleton_INCLUDED
#define IoT_Devices_SensorSkeleton_INCLUDED


#include "IoT/Devices/SensorRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class SensorSkeleton: public Poco::RemotingNG::Skeleton
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
	SensorSkeleton();
		/// Creates a SensorSkeleton.

	virtual ~SensorSkeleton();
		/// Destroys a SensorSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SensorSkeleton::remoting__typeId() const
{
	return ISensor::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SensorSkeleton_INCLUDED

