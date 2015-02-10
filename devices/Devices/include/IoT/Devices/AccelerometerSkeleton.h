//
// AccelerometerSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  AccelerometerSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_AccelerometerSkeleton_INCLUDED
#define IoT_Devices_AccelerometerSkeleton_INCLUDED


#include "IoT/Devices/AccelerometerRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class AccelerometerSkeleton: public Poco::RemotingNG::Skeleton
	/// The interface for three-axis Accelerometers.
{
public:
	AccelerometerSkeleton();
		/// Creates a AccelerometerSkeleton.

	virtual ~AccelerometerSkeleton();
		/// Destroys a AccelerometerSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& AccelerometerSkeleton::remoting__typeId() const
{
	return IAccelerometer::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_AccelerometerSkeleton_INCLUDED

