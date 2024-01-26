//
// Counter.h
//
// Library: IoT/Devices
// Package: Devices
// Module:  Counter
//
// Definition of the Counter interface.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_Counter_INCLUDED
#define IoT_Devices_Counter_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"
#include "Poco/Optional.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API Counter: public Device
	/// A counter counts events.
{
public:
	using CounterType = Poco::Int32;

	Poco::BasicEvent<const CounterType> countChanged;
		/// Fired when the counter has changed.

	Counter();
		/// Creates the Counter.

	~Counter();
		/// Destroys the Counter.

	virtual CounterType count() const = 0;
		/// Returns the current value of the counter.

	virtual CounterType reset() = 0;
		/// Returns the current value of the counter and
		/// sets the counter to 0.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Counter_INCLUDED
