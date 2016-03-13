//
// IIO.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IIO
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IIO_INCLUDED
#define IoT_Devices_IIO_INCLUDED


#include "IoT/Devices/IDevice.h"
#include "IoT/Devices/IO.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IIO: public IoT::Devices::IDevice
	/// The interface for general purpose input/output (GPIO)
	/// ports.
	///
	/// This class represents a single GPIO pin. 
	/// Mapping to physical pins is configured when setting up 
	/// the specific IO implementation class, typically using a 
	/// configuration file.
	///
	/// Implementations supporting dynamically changing pin directions
	/// should expose a string property named "direction" that takes the
	/// values "in" and "out".
{
public:
	typedef Poco::AutoPtr<IIO> Ptr;

	IIO();
		/// Creates a IIO.

	virtual ~IIO();
		/// Destroys the IIO.

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

	virtual void set(bool state) = 0;
		/// Sets the state of an output pin to the given state.

	virtual bool state() const = 0;
		/// Returns the current state of the pin.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const bool > stateChanged;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IIO_INCLUDED

