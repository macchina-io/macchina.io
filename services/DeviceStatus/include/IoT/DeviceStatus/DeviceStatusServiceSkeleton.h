//
// DeviceStatusServiceSkeleton.h
//
// Library: IoT/DeviceStatus
// Package: Generated
// Module:  DeviceStatusServiceSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_DeviceStatus_DeviceStatusServiceSkeleton_INCLUDED
#define IoT_DeviceStatus_DeviceStatusServiceSkeleton_INCLUDED


#include "IoT/DeviceStatus/DeviceStatusServiceRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace DeviceStatus {


class DeviceStatusServiceSkeleton: public Poco::RemotingNG::Skeleton
	/// The DeviceStatusService keeps track of the current operational
	/// status of a device.
{
public:
	DeviceStatusServiceSkeleton();
		/// Creates a DeviceStatusServiceSkeleton.

	virtual ~DeviceStatusServiceSkeleton();
		/// Destroys a DeviceStatusServiceSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& DeviceStatusServiceSkeleton::remoting__typeId() const
{
	return IDeviceStatusService::remoting__typeId();
}


} // namespace DeviceStatus
} // namespace IoT


#endif // IoT_DeviceStatus_DeviceStatusServiceSkeleton_INCLUDED

