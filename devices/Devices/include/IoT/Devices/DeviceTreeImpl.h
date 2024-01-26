//
// DeviceTreeImpl.h
//
// Library: IoT/Devices
// Package: Devices
// Module:  DeviceTree
//
// Default implementation of the DeviceTree interface.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_DeviceTreeImpl_INCLUDED
#define IoT_Devices_DeviceTreeImpl_INCLUDED


#include "IoT/Devices/DeviceTree.h"
#include "Poco/OSP/ServiceRegistry.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API DeviceTreeImpl: public DeviceTree
	/// Default implementation of the DeviceTree service.
	///
	/// Local device node names will be obtained from the
	/// service property named "io.macchina.nodeName". If
	/// that device property is not defined, the device's
	/// name will be obtained directly from the device
	/// object's "name" property.
{
public:
	explicit DeviceTreeImpl(const Poco::OSP::ServiceRegistry& registry);
		/// Creates the DeviceTreeImpl with the given ServiceRegistry.

	~DeviceTreeImpl();
		/// Destroys the DeviceTreeImpl.

	// DeviceTree
	DeviceNode deviceByPath(const std::string& path) const;
	Poco::Optional<DeviceNode> findDeviceByPath(const std::string& path) const;
	DeviceNode deviceById(const std::string& id) const;
	Poco::Optional<DeviceNode> findDeviceById(const std::string& id) const;

protected:
	Poco::Optional<DeviceNode> rootDevice() const;
	Poco::Optional<DeviceNode> findDevice(const DeviceNode& node, std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end) const;

private:
	const Poco::OSP::ServiceRegistry& _registry;
};


} } // namespace IoT::Devices


#endif // IoT_Devices_DeviceTreeImpl_INCLUDED
