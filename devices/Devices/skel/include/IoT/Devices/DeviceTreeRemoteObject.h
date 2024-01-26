//
// DeviceTreeRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceTreeRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_DeviceTreeRemoteObject_INCLUDED
#define IoT_Devices_DeviceTreeRemoteObject_INCLUDED


#include "IoT/Devices/IDeviceTree.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class DeviceTreeRemoteObject: public IoT::Devices::IDeviceTree, public Poco::RemotingNG::RemoteObject
	/// This class manages a hierarchical structure
	/// of devices, consisting of Composite and 
	/// leaf Device objects.
{
public:
	using Ptr = Poco::AutoPtr<DeviceTreeRemoteObject>;

	DeviceTreeRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::DeviceTree> pServiceObject);
		/// Creates a DeviceTreeRemoteObject.

	virtual ~DeviceTreeRemoteObject();
		/// Destroys the DeviceTreeRemoteObject.

	IoT::Devices::DeviceNode deviceById(const std::string& id) const;
		/// Returns the DeviceNode of the device with the given device identifier. 
		///
		/// Throws a Poco::NotFoundException if no DeviceNode is available for the given device identifier.

	IoT::Devices::DeviceNode deviceByPath(const std::string& path) const;
		/// Returns the DeviceNode of the device with the given path.
		/// The path name is composed of the instance names of all parent composite devices,
		/// as well as the device's instance name, separated by "/".
		///
		/// To obtain the root device, which is always a Composite, specify "/" or "" as pathName.
		///
		/// Throws a Poco::NotFoundException if no DeviceNode is available for the given pathName.

	Poco::Optional < IoT::Devices::DeviceNode > findDeviceById(const std::string& id) const;
		/// Returns the DeviceNode of the device with the given device identifier, if it exists.

	Poco::Optional < IoT::Devices::DeviceNode > findDeviceByPath(const std::string& path) const;
		/// Returns the DeviceNode of the device with the given path, if it exists.
		/// The path name is composed of the instance names of all parent composite devices,
		/// as well as the device's instance name, separated by "/".
		///
		/// To obtain the root device, which is always a Composite, specify "/" or "" as pathName.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	Poco::SharedPtr<IoT::Devices::DeviceTree> _pServiceObject;
};


inline IoT::Devices::DeviceNode DeviceTreeRemoteObject::deviceById(const std::string& id) const
{
	return _pServiceObject->deviceById(id);
}


inline IoT::Devices::DeviceNode DeviceTreeRemoteObject::deviceByPath(const std::string& path) const
{
	return _pServiceObject->deviceByPath(path);
}


inline Poco::Optional < IoT::Devices::DeviceNode > DeviceTreeRemoteObject::findDeviceById(const std::string& id) const
{
	return _pServiceObject->findDeviceById(id);
}


inline Poco::Optional < IoT::Devices::DeviceNode > DeviceTreeRemoteObject::findDeviceByPath(const std::string& path) const
{
	return _pServiceObject->findDeviceByPath(path);
}


inline const Poco::RemotingNG::Identifiable::TypeId& DeviceTreeRemoteObject::remoting__typeId() const
{
	return IDeviceTree::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_DeviceTreeRemoteObject_INCLUDED

