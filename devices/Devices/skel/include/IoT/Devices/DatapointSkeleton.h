//
// DatapointSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  DatapointSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_DatapointSkeleton_INCLUDED
#define IoT_Devices_DatapointSkeleton_INCLUDED


#include "IoT/Devices/DatapointRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class DatapointSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for datapoints.
	/// Datapoints typically represent the result of
	/// sensor measurements, or data obtained from monitoring
	/// processes.
	///
	/// The main difference between a Datapoint and a Sensor is
	/// that a Sensor is typically an interface to a specific
	/// device (i.e., a temperature sensor), whereas a Datapoint 
	/// holds a value that has been acquired from another
	/// device (via a network or bus system) or computed
	/// from other data points.
	///
	/// In addition to the methods defined in this interface,
	/// a Sensor implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
	///   - updated (timestamp, optional): The point in time when the
	///     datapoint's value was last updated.
	///   - access (string, optional): Access permissions ("rw" - read/write,
	///     "ro" - read-only, "wo" - write-only).
	///
	/// Subclasses of Datapoint implement specific value types.
{
public:
	DatapointSkeleton();
		/// Creates a DatapointSkeleton.

	virtual ~DatapointSkeleton();
		/// Destroys a DatapointSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& DatapointSkeleton::remoting__typeId() const
{
	return IDatapoint::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_DatapointSkeleton_INCLUDED

