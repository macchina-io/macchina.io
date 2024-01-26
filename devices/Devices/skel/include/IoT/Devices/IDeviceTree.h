//
// IDeviceTree.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IDeviceTree
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_IDeviceTree_INCLUDED
#define IoT_Devices_IDeviceTree_INCLUDED


#include "IoT/Devices/DeviceTree.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"


namespace IoT {
namespace Devices {


class IDeviceTree: public Poco::OSP::Service
	/// This class manages a hierarchical structure
	/// of devices, consisting of Composite and 
	/// leaf Device objects.
{
public:
	using Ptr = Poco::AutoPtr<IDeviceTree>;

	IDeviceTree();
		/// Creates a IDeviceTree.

	virtual ~IDeviceTree();
		/// Destroys the IDeviceTree.

	virtual IoT::Devices::DeviceNode deviceById(const std::string& id) const = 0;
		/// Returns the DeviceNode of the device with the given device identifier. 
		///
		/// Throws a Poco::NotFoundException if no DeviceNode is available for the given device identifier.

	virtual IoT::Devices::DeviceNode deviceByPath(const std::string& path) const = 0;
		/// Returns the DeviceNode of the device with the given path.
		/// The path name is composed of the instance names of all parent composite devices,
		/// as well as the device's instance name, separated by "/".
		///
		/// To obtain the root device, which is always a Composite, specify "/" or "" as pathName.
		///
		/// Throws a Poco::NotFoundException if no DeviceNode is available for the given pathName.

	virtual Poco::Optional < IoT::Devices::DeviceNode > findDeviceById(const std::string& id) const = 0;
		/// Returns the DeviceNode of the device with the given device identifier, if it exists.

	virtual Poco::Optional < IoT::Devices::DeviceNode > findDeviceByPath(const std::string& path) const = 0;
		/// Returns the DeviceNode of the device with the given path, if it exists.
		/// The path name is composed of the instance names of all parent composite devices,
		/// as well as the device's instance name, separated by "/".
		///
		/// To obtain the root device, which is always a Composite, specify "/" or "" as pathName.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IDeviceTree_INCLUDED

