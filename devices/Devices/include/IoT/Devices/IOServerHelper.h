//
// IOServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IOServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IOServerHelper_INCLUDED
#define IoT_Devices_IOServerHelper_INCLUDED


#include "IoT/Devices/IIO.h"
#include "IoT/Devices/IO.h"
#include "IoT/Devices/IORemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class IOServerHelper
	/// The base class for general purpose input/output (GPIO)
	/// devices.
	///
	/// The IO class supports up to 32 logical pins. Each logical
	/// pin is mapped to a physical pin on the hardware. Logical
	/// pins are counted from 0 to 31. Mapping to physical pins
	/// is configured when setting up the IO implementation class,
	/// typically using a configuration file.
	///
	/// Implementations that support interrupt-capable input pins
	/// should expose an int property named "stateChangedEventMask"
	/// that allows enabling interrupts for specific pins, based
	/// on the given bit mask.
	///
	/// Implementations supporting dynamically changing pin directions
	/// should expose int properties named "configureInputs" and
	/// "configureOutputs" that take a bit mask specifying affected pins.
{
public:
	typedef IoT::Devices::IO Service;

	IOServerHelper();
		/// Creates a IOServerHelper.

	~IOServerHelper();
		/// Destroys the IOServerHelper.

	static Poco::AutoPtr<IoT::Devices::IORemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::IO> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::IO instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::IO> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::IO instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::IORemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::IORemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::IO> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static IOServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::IORemoteObject> pRemoteObject, const std::string& listenerId);

	void unregisterObjectImpl(const std::string& uri);

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::IORemoteObject> IOServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::IO> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return IOServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void IOServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	IOServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string IOServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::IO> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return IOServerHelper::instance().registerObjectImpl(new IORemoteObject(oid, pServiceObject), listenerId);
}


inline void IOServerHelper::unregisterObject(const std::string& uri)
{
	IOServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, IO)


#endif // IoT_Devices_IOServerHelper_INCLUDED

