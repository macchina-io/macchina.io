//
// Counter.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/Counter.h#2 $
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
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Counter_INCLUDED
#define IoT_Devices_Counter_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API Counter: public Device
	/// A counter counts events.
{
public:
	Poco::BasicEvent<const Poco::Int32> countChanged;
		/// Fired when the counter has changed.

	Counter();
		/// Creates the Counter.

	~Counter();
		/// Destroys the Counter.

	virtual Poco::Int32 count() const = 0;
		/// Returns the current value of the counter.

	virtual Poco::Int32 reset() = 0;
		/// Returns the current value of the counter and
		/// sets the counter to 0.
};


} } // namespace IoT::Devices


#endif // IoT_Devices_Counter_INCLUDED
