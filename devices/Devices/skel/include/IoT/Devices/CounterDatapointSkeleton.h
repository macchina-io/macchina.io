//
// CounterDatapointSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  CounterDatapointSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_CounterDatapointSkeleton_INCLUDED
#define IoT_Devices_CounterDatapointSkeleton_INCLUDED


#include "IoT/Devices/CounterDatapointRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class CounterDatapointSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for datapoints holding a counter
	/// (a 64-bit unsigned integer).
	///
	/// In addition to the methods defined in this interface,
	/// a CounterDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	CounterDatapointSkeleton();
		/// Creates a CounterDatapointSkeleton.

	virtual ~CounterDatapointSkeleton();
		/// Destroys a CounterDatapointSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& CounterDatapointSkeleton::remoting__typeId() const
{
	return ICounterDatapoint::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_CounterDatapointSkeleton_INCLUDED

