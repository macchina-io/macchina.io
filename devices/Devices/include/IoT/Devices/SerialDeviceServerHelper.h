//
// SerialDeviceServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SerialDeviceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SerialDeviceServerHelper_INCLUDED
#define IoT_Devices_SerialDeviceServerHelper_INCLUDED


#include "IoT/Devices/ISerialDevice.h"
#include "IoT/Devices/SerialDevice.h"
#include "IoT/Devices/SerialDeviceRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class SerialDeviceServerHelper
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
	typedef IoT::Devices::SerialDevice Service;

	SerialDeviceServerHelper();
		/// Creates a SerialDeviceServerHelper.

	~SerialDeviceServerHelper();
		/// Destroys the SerialDeviceServerHelper.

	static Poco::AutoPtr<IoT::Devices::SerialDeviceRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::SerialDevice> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::SerialDevice instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::SerialDevice> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::SerialDevice instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::SerialDeviceRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::SerialDevice from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::SerialDeviceRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::SerialDevice> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static SerialDeviceServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::SerialDeviceRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::SerialDeviceRemoteObject> SerialDeviceServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::SerialDevice> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return SerialDeviceServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void SerialDeviceServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	SerialDeviceServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string SerialDeviceServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::SerialDevice> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return SerialDeviceServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string SerialDeviceServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::SerialDeviceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return SerialDeviceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void SerialDeviceServerHelper::unregisterObject(const std::string& uri)
{
	SerialDeviceServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, SerialDevice)


#endif // IoT_Devices_SerialDeviceServerHelper_INCLUDED

