//
// GNSSSensorSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  GNSSSensorSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GNSSSensorSkeleton_INCLUDED
#define IoT_Devices_GNSSSensorSkeleton_INCLUDED


#include "IoT/Devices/GNSSSensorRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class GNSSSensorSkeleton: public Poco::RemotingNG::Skeleton
	/// The interface for GNSS/GPS receivers.
	///
	/// Implementations of this class should also support the
	/// following (optional) properties for configuration:
	///
	///   - positionChangedPeriod (int): the minimum time interval
	///     in milliseconds between firings of the positionUpdate event.
	///   - positionChangedDelta (int): the minimum distance (in meters)
	///     the receiver must move before the positionUpdate event
	///     is fired again.
	///   - positionTimeout (int): Timeout in milliseconds after which the
	///     positionLost event is fired if no valid position has been
	///     received from the GNSS receiver.
{
public:
	GNSSSensorSkeleton();
		/// Creates a GNSSSensorSkeleton.

	virtual ~GNSSSensorSkeleton();
		/// Destroys a GNSSSensorSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& GNSSSensorSkeleton::remoting__typeId() const
{
	return IGNSSSensor::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_GNSSSensorSkeleton_INCLUDED

