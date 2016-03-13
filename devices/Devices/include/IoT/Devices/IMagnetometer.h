//
// IMagnetometer.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IMagnetometer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IMagnetometer_INCLUDED
#define IoT_Devices_IMagnetometer_INCLUDED


#include "IoT/Devices/IDevice.h"
#include "IoT/Devices/Magnetometer.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IMagnetometer: public IoT::Devices::IDevice
	/// The interface for three-axis Magnetometers.
{
public:
	typedef Poco::AutoPtr<IMagnetometer> Ptr;

	IMagnetometer();
		/// Creates a IMagnetometer.

	virtual ~IMagnetometer();
		/// Destroys the IMagnetometer.

	virtual IoT::Devices::MagneticFieldStrength fieldStrength() const = 0;
		/// Returns the most recently measured field strength values.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const MagneticFieldStrength > fieldStrengthChanged;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IMagnetometer_INCLUDED

