//
// IComposite.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IComposite
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_IComposite_INCLUDED
#define IoT_Devices_IComposite_INCLUDED


#include "IoT/Devices/Composite.h"
#include "IoT/Devices/IDevice.h"


namespace IoT {
namespace Devices {


class IComposite: public IoT::Devices::IDevice
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
	using Ptr = Poco::AutoPtr<IComposite>;

	IComposite();
		/// Creates a IComposite.

	virtual ~IComposite();
		/// Destroys the IComposite.

	virtual Poco::Optional < std::string > fragmentByName(const std::string& nodeName) const = 0;
		/// Returns the device identifier of the direct sub device 
		/// with the given node name (property "io.macchina.nodeName"), 
		/// or an empty optional if no such device node exists.
		///
		/// Note: if multiple child nodes with the same node name exist,
		/// which of these nodes is returned is undefined.

	virtual std::vector < std::string > fragments() const = 0;
		/// Returns a vector containing the device identifiers
		/// of all direct sub devices owned by this device.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IComposite_INCLUDED

