//
// GNSSSensorEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  GNSSSensorEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GNSSSensorEventDispatcher_INCLUDED
#define IoT_Devices_GNSSSensorEventDispatcher_INCLUDED


#include "IoT/Devices/GNSSSensorRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class GNSSSensorEventDispatcher: public Poco::RemotingNG::EventDispatcher
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
	GNSSSensorEventDispatcher(GNSSSensorRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a GNSSSensorEventDispatcher.

	virtual ~GNSSSensorEventDispatcher();
		/// Destroys the GNSSSensorEventDispatcher.

	void event__positionLost(const void* pSender);

	void event__positionUpdate(const void* pSender, const IoT::Devices::PositionUpdate& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__positionLostImpl(const std::string& subscriberURI);

	void event__positionUpdateImpl(const std::string& subscriberURI, const IoT::Devices::PositionUpdate& data);

	static const std::string DEFAULT_NS;
	GNSSSensorRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& GNSSSensorEventDispatcher::remoting__typeId() const
{
	return IGNSSSensor::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_GNSSSensorEventDispatcher_INCLUDED

