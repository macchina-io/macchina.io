//
// FlagsDatapointSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  FlagsDatapointSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_FlagsDatapointSkeleton_INCLUDED
#define IoT_Devices_FlagsDatapointSkeleton_INCLUDED


#include "IoT/Devices/FlagsDatapointRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class FlagsDatapointSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for datapoints holding a variable number of
	/// flag bits, internally stored as a std::vector<bool>.
	///
	/// An implementation should handle conversion between a
	/// flag bit and the corresponding symbolic name of
	/// a flag.
	///
	/// In addition to the methods defined in this interface,
	/// a FlagsDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	FlagsDatapointSkeleton();
		/// Creates a FlagsDatapointSkeleton.

	virtual ~FlagsDatapointSkeleton();
		/// Destroys a FlagsDatapointSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& FlagsDatapointSkeleton::remoting__typeId() const
{
	return IFlagsDatapoint::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_FlagsDatapointSkeleton_INCLUDED

