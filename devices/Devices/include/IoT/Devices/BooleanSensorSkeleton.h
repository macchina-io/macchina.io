//
// BooleanSensorSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  BooleanSensorSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_BooleanSensorSkeleton_INCLUDED
#define IoT_Devices_BooleanSensorSkeleton_INCLUDED


#include "IoT/Devices/BooleanSensorRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class BooleanSensorSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for two-state sensors measuring
	/// on/off or open/closed state.
	///
	/// In addition to the methods defined in this interface,
	/// a BooleanSensor implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the trigger,
	///     formatted as string for display purposes.
{
public:
	BooleanSensorSkeleton();
		/// Creates a BooleanSensorSkeleton.

	virtual ~BooleanSensorSkeleton();
		/// Destroys a BooleanSensorSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& BooleanSensorSkeleton::remoting__typeId() const
{
	return IBooleanSensor::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_BooleanSensorSkeleton_INCLUDED

