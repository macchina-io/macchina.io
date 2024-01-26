//
// VectorDatapointSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  VectorDatapointSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_VectorDatapointSkeleton_INCLUDED
#define IoT_Devices_VectorDatapointSkeleton_INCLUDED


#include "IoT/Devices/VectorDatapointRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class VectorDatapointSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for datapoints holding a vector value.
	///
	/// In addition to the methods defined in this interface,
	/// a VectorDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	VectorDatapointSkeleton();
		/// Creates a VectorDatapointSkeleton.

	virtual ~VectorDatapointSkeleton();
		/// Destroys a VectorDatapointSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& VectorDatapointSkeleton::remoting__typeId() const
{
	return IVectorDatapoint::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_VectorDatapointSkeleton_INCLUDED

