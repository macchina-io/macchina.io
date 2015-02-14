//
// IGNSSSensor.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IGNSSSensor
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IGNSSSensor_INCLUDED
#define IoT_Devices_IGNSSSensor_INCLUDED


#include "IoT/Devices/GNSSSensor.h"
#include "IoT/Devices/IDevice.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IGNSSSensor: public IoT::Devices::IDevice
	/// The interface for GNSS/GPS receivers.
{
public:
	typedef Poco::AutoPtr<IGNSSSensor> Ptr;

	IGNSSSensor();
		/// Creates a IGNSSSensor.

	virtual ~IGNSSSensor();
		/// Destroys the IGNSSSensor.

	virtual double altitude() const = 0;
		/// Returns the current altitude above sea level in meters.
		/// Returns -9999 if no altitude is available.

	virtual double hdop() const = 0;
		/// Returns the Horizontal Dilution Of Precision (HDOP) in meters,
		/// or -9999 if no HDOP value is available.

	virtual double heading() const = 0;
		/// Returns the current heading in degrees [0, 360).

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual double magneticVariation() const = 0;
		/// Returns the current magnetic variation in degrees [0, 360).
		/// Returns -1 if no magnetic variation is available.

	virtual IoT::Devices::LatLon position() const = 0;
		/// Returns the last obtained position.
		///
		/// If no position is available, latitude and longitude will both be 0.
		/// To disambiguate with a real position, also check positionAvailable().

	virtual bool positionAvailable() const = 0;
		/// Returns true if a valid position is available.

	virtual void remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual double speed() const = 0;
		/// Returns the current speed in nautical knots.
		/// If no speed is available, returns -1.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const PositionUpdate > positionUpdate;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IGNSSSensor_INCLUDED

