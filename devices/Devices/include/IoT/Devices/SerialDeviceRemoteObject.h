//
// SerialDeviceRemoteObject.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SerialDeviceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SerialDeviceRemoteObject_INCLUDED
#define IoT_Devices_SerialDeviceRemoteObject_INCLUDED


#include "IoT/Devices/ISerialDevice.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Devices {


class SerialDeviceRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::Devices::ISerialDevice
	/// This class provides a simple interface for accessing
	/// a serial port.
	///
	/// There are two modes of operation for receiving data:
	/// polling (blocking) mode (default) and events (callback) mode.
	///
	/// In polling mode, repeatedly call poll() to detect
	/// if data is available, then call one of the read() methods
	/// to receive available data. The read() methods can also be
	/// called if no data is available, but will block until
	/// at least one character can be read.
	///
	/// In event mode the class will start a thread that polls
	/// and reads available data from the serial port, and fires
	/// the lineReceived event whenever something has been read.
	/// Since callback mode uses readLine() to receive entire lines
	/// (if possible), delimiter characters and timeout can be set
	/// via the "delimiters" (string) and "timeout" (double) properties.
	///
	/// Clients of the class can switch between polling and event
	/// mode by enabling or disabling the "events" feature:
	///
	///     setFeature("events", true);
{
public:
	typedef Poco::AutoPtr<SerialDeviceRemoteObject> Ptr;

	SerialDeviceRemoteObject();
		/// Creates a SerialDeviceRemoteObject.

	virtual ~SerialDeviceRemoteObject();
		/// Destroys the SerialDeviceRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& SerialDeviceRemoteObject::remoting__typeId() const
{
	return ISerialDevice::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SerialDeviceRemoteObject_INCLUDED

