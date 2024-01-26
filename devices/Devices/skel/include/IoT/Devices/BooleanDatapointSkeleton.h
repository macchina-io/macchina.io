//
// BooleanDatapointSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  BooleanDatapointSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_BooleanDatapointSkeleton_INCLUDED
#define IoT_Devices_BooleanDatapointSkeleton_INCLUDED


#include "IoT/Devices/BooleanDatapointRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class BooleanDatapointSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for datapoints holding a boolean value.
	///
	/// In addition to the methods defined in this interface,
	/// a BooleanDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	BooleanDatapointSkeleton();
		/// Creates a BooleanDatapointSkeleton.

	virtual ~BooleanDatapointSkeleton();
		/// Destroys a BooleanDatapointSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& BooleanDatapointSkeleton::remoting__typeId() const
{
	return IBooleanDatapoint::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_BooleanDatapointSkeleton_INCLUDED

