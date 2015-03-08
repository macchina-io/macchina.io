//
// SerialDeviceEventDispatcher.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SerialDeviceEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SerialDeviceEventDispatcher_INCLUDED
#define IoT_Devices_SerialDeviceEventDispatcher_INCLUDED


#include "IoT/Devices/SerialDeviceRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class SerialDeviceEventDispatcher: public Poco::RemotingNG::EventDispatcher
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
	SerialDeviceEventDispatcher(SerialDeviceRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a SerialDeviceEventDispatcher.

	virtual ~SerialDeviceEventDispatcher();
		/// Destroys the SerialDeviceEventDispatcher.

	void event__lineReceived(const void* pSender, const std::string& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__lineReceivedImpl(const std::string& subscriberURI, const std::string& data);

	static const std::string DEFAULT_NS;
	SerialDeviceRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SerialDeviceEventDispatcher::remoting__typeId() const
{
	return ISerialDevice::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SerialDeviceEventDispatcher_INCLUDED

