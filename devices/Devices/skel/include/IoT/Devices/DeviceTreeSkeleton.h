//
// DeviceTreeSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceTreeSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_DeviceTreeSkeleton_INCLUDED
#define IoT_Devices_DeviceTreeSkeleton_INCLUDED


#include "IoT/Devices/DeviceTreeRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class DeviceTreeSkeleton: public Poco::RemotingNG::Skeleton
	/// This class manages a hierarchical structure
	/// of devices, consisting of Composite and 
	/// leaf Device objects.
{
public:
	DeviceTreeSkeleton();
		/// Creates a DeviceTreeSkeleton.

	virtual ~DeviceTreeSkeleton();
		/// Destroys a DeviceTreeSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& DeviceTreeSkeleton::remoting__typeId() const
{
	return IDeviceTree::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_DeviceTreeSkeleton_INCLUDED

