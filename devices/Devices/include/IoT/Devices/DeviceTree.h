//
// DeviceTree.h
//
// Library: IoT/Devices
// Package: Devices
// Module:  DeviceTree
//
// Definition of the DeviceTree interface.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_DeviceTree_INCLUDED
#define IoT_Devices_DeviceTree_INCLUDED


#include "IoT/Devices/Devices.h"
#include "Poco/Optional.h"
#include <vector>


namespace IoT {
namespace Devices {


//@ serialize
struct DeviceNode
{
	std::string id;
		/// Device identifier (registered service name), e.g. "io.macchina.simulation.sensor#1"
	
	std::string name;
		/// Local node name, e.g. "Temperature"

	std::string type;
		/// Node device type, e.g. "io.macchina.sensor"

	std::string composite;
		/// Registered service name of parent Composite device, 
		/// which is always a Composite.

	Poco::Optional<std::vector<std::string>> fragments;
		/// Device identifiers (registered service names) of all 
		/// direct child fragment devices, only set if the device is a Composite.
};


//@ remote
class IoTDevices_API DeviceTree
	/// This class manages a hierarchical structure
	/// of devices, consisting of Composite and 
	/// leaf Device objects.
{
public:
	DeviceTree();
		/// Creates the DeviceTree.

	virtual ~DeviceTree();
		/// Destroys the DeviceTree.

	virtual DeviceNode deviceByPath(const std::string& path) const = 0;
		/// Returns the DeviceNode of the device with the given path.
		/// The path name is composed of the instance names of all parent composite devices,
		/// as well as the device's instance name, separated by "/".
		///
		/// To obtain the root device, which is always a Composite, specify "/" or "" as pathName.
		///
		/// Throws a Poco::NotFoundException if no DeviceNode is available for the given pathName.

	virtual Poco::Optional<DeviceNode> findDeviceByPath(const std::string& path) const = 0;
		/// Returns the DeviceNode of the device with the given path, if it exists.
		/// The path name is composed of the instance names of all parent composite devices,
		/// as well as the device's instance name, separated by "/".
		///
		/// To obtain the root device, which is always a Composite, specify "/" or "" as pathName.

	virtual DeviceNode deviceById(const std::string& id) const = 0;
		/// Returns the DeviceNode of the device with the given device identifier. 
		///
		/// Throws a Poco::NotFoundException if no DeviceNode is available for the given device identifier.

	virtual Poco::Optional<DeviceNode> findDeviceById(const std::string& id) const = 0;
		/// Returns the DeviceNode of the device with the given device identifier, if it exists.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_DeviceTree_INCLUDED
