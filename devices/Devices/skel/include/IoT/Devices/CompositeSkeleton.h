//
// CompositeSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  CompositeSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_CompositeSkeleton_INCLUDED
#define IoT_Devices_CompositeSkeleton_INCLUDED


#include "IoT/Devices/CompositeRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class CompositeSkeleton: public Poco::RemotingNG::Skeleton
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
	CompositeSkeleton();
		/// Creates a CompositeSkeleton.

	virtual ~CompositeSkeleton();
		/// Destroys a CompositeSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& CompositeSkeleton::remoting__typeId() const
{
	return IComposite::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_CompositeSkeleton_INCLUDED

