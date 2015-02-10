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

