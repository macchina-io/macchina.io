//
// DeviceRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_DeviceRemoteObject_INCLUDED
#define IoT_Devices_DeviceRemoteObject_INCLUDED


#include "IoT/Devices/IDevice.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class DeviceRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::IDevice
	/// The base class for all devices and sensors.
	///
	/// This class defines a generic interface for setting
	/// and querying device properties and features.
	///
	/// Every implementation of Device should expose the
	/// following properties:
	///   - symbolicName (string): A name in reverse DNS notation
	///     that identifies the device type (e.g., "io.macchina.serialport").
	///   - name (string): A human-readable device type (e.g., "Serial Port").
{
public:
	typedef Poco::AutoPtr<DeviceRemoteObject> Ptr;

	DeviceRemoteObject();
		/// Creates a DeviceRemoteObject.

	virtual ~DeviceRemoteObject();
		/// Destroys the DeviceRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& DeviceRemoteObject::remoting__typeId() const
{
	return IDevice::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_DeviceRemoteObject_INCLUDED

