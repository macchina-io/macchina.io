//
// DeviceStatusServiceRemoteObject.h
//
// Library: IoT/DeviceStatus
// Package: Generated
// Module:  DeviceStatusServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_DeviceStatus_DeviceStatusServiceRemoteObject_INCLUDED
#define IoT_DeviceStatus_DeviceStatusServiceRemoteObject_INCLUDED


#include "IoT/DeviceStatus/IDeviceStatusService.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace DeviceStatus {


class DeviceStatusServiceRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::DeviceStatus::IDeviceStatusService
	/// The DeviceStatusService keeps track of the current operational
	/// status of a device.
{
public:
	typedef Poco::AutoPtr<DeviceStatusServiceRemoteObject> Ptr;

	DeviceStatusServiceRemoteObject();
		/// Creates a DeviceStatusServiceRemoteObject.

	virtual ~DeviceStatusServiceRemoteObject();
		/// Destroys the DeviceStatusServiceRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& DeviceStatusServiceRemoteObject::remoting__typeId() const
{
	return IDeviceStatusService::remoting__typeId();
}


} // namespace DeviceStatus
} // namespace IoT


#endif // IoT_DeviceStatus_DeviceStatusServiceRemoteObject_INCLUDED

