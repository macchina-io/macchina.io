//
// Composite.h
//
// Library: IoT/Devices
// Package: Devices
// Module:  Composite
//
// Definition of the Composite interface.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_Composite_INCLUDED
#define IoT_Devices_Composite_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/Optional.h"
#include <vector>


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API Composite: public Device
	/// A composite device consists of one or
	/// more sub devices or device fragments.
	///
	/// Composites are used to build hierarchies
	/// of devices, also known as device trees.
	/// This is intended to represent the hierarchical
	/// structure of a more complex device.
	///
	/// For example, for an electric vehicle, the
	/// (simplified) device tree may look like:
	///
	///     / (root)
	///      Battery/
 	///       Voltage
 	///       Temperature
 	///       ChargeLevel
	///      Motor/
	///        Switch
	///        PowerUsage
	///        RPM
 	///        Temperature
    ///        ...    
    ///      ...
	///
	/// The DeviceTree class can be used to conveniently
	/// find a device in the tree.
{
public:
	Composite();
		/// Creates the Composite.

	virtual ~Composite();
		/// Destroys the Composite.

	virtual std::vector<std::string> fragments() const = 0;
		/// Returns a vector containing the device identifiers
		/// of all direct sub devices owned by this device.

	virtual Poco::Optional<std::string> fragmentByName(const std::string& nodeName) const = 0;
		/// Returns the device identifier of the direct sub device 
		/// with the given node name (property "io.macchina.nodeName"), 
		/// or an empty optional if no such device node exists.
		///
		/// Note: if multiple child nodes with the same node name exist,
		/// which of these nodes is returned is undefined.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Composite_INCLUDED
