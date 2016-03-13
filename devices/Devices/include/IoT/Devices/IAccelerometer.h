//
// IAccelerometer.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IAccelerometer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IAccelerometer_INCLUDED
#define IoT_Devices_IAccelerometer_INCLUDED


#include "IoT/Devices/Accelerometer.h"
#include "IoT/Devices/IDevice.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IAccelerometer: public IoT::Devices::IDevice
	/// The interface for three-axis Accelerometers.
{
public:
	typedef Poco::AutoPtr<IAccelerometer> Ptr;

	IAccelerometer();
		/// Creates a IAccelerometer.

	virtual ~IAccelerometer();
		/// Destroys the IAccelerometer.

	virtual IoT::Devices::Acceleration acceleration() const = 0;
		/// Returns the most recently measured acceleration values.

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

	Poco::BasicEvent < const Acceleration > accelerationChanged;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IAccelerometer_INCLUDED

