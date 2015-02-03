//
// ISensor.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ISensor
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_ISensor_INCLUDED
#define IoT_Devices_ISensor_INCLUDED


#include "IoT/Devices/IDevice.h"
#include "IoT/Devices/Sensor.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class ISensor: public IoT::Devices::IDevice
	/// The base class for analog sensors, such as
	/// temperature or ambient light sensors.
{
public:
	typedef Poco::AutoPtr<ISensor> Ptr;

	ISensor();
		/// Creates a ISensor.

	virtual ~ISensor();
		/// Destroys the ISensor.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

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

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual double value() const = 0;
		/// Returns the current value measured by the sensor.

	Poco::BasicEvent < const double > valueChanged;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_ISensor_INCLUDED

