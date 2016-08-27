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

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::IO from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::IORemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::IO> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static IOServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::IORemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

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
	return IOServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string IOServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::IORemoteObject> pRemoteObject, const std::string& listenerId)
{
	return IOServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void IOServerHelper::unregisterObject(const std::string& uri)
{
	IOServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, IO)


#endif // IoT_Devices_IOServerHelper_INCLUDED

