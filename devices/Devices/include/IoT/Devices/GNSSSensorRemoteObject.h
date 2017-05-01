//
// GNSSSensorRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  GNSSSensorRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GNSSSensorRemoteObject_INCLUDED
#define IoT_Devices_GNSSSensorRemoteObject_INCLUDED


#include "IoT/Devices/IGNSSSensor.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class GNSSSensorRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::IGNSSSensor
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
	typedef Poco::AutoPtr<GNSSSensorRemoteObject> Ptr;

	GNSSSensorRemoteObject();
		/// Creates a GNSSSensorRemoteObject.

	virtual ~GNSSSensorRemoteObject();
		/// Destroys the GNSSSensorRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& GNSSSensorRemoteObject::remoting__typeId() const
{
	return IGNSSSensor::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_GNSSSensorRemoteObject_INCLUDED

