//
// PeripheralServerHelper.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralServerHelper_INCLUDED
#define IoT_BtLE_PeripheralServerHelper_INCLUDED


#include "IoT/BtLE/IPeripheral.h"
#include "IoT/BtLE/Peripheral.h"
#include "IoT/BtLE/PeripheralRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace BtLE {


class PeripheralServerHelper
	/// This class provides a high-level interface to a Bluetooth LE peripheral
	/// device using the Bluetooth Generic Attribute Profile (GATT).
{
public:
	typedef IoT::BtLE::Peripheral Service;

	PeripheralServerHelper();
		/// Creates a PeripheralServerHelper.

	~PeripheralServerHelper();
		/// Destroys the PeripheralServerHelper.

	static Poco::AutoPtr<IoT::BtLE::PeripheralRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::BtLE::Peripheral> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::BtLE::Peripheral instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::BtLE::Peripheral> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::BtLE::Peripheral instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::BtLE::PeripheralRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::BtLE::Peripheral from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::BtLE::PeripheralRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::BtLE::Peripheral> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static PeripheralServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::BtLE::PeripheralRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::BtLE::PeripheralRemoteObject> PeripheralServerHelper::createRemoteObject(Poco::SharedPtr<IoT::BtLE::Peripheral> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return PeripheralServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void PeripheralServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	PeripheralServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string PeripheralServerHelper::registerObject(Poco::SharedPtr<IoT::BtLE::Peripheral> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return PeripheralServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string PeripheralServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::BtLE::PeripheralRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return PeripheralServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void PeripheralServerHelper::unregisterObject(const std::string& uri)
{
	PeripheralServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace BtLE
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::BtLE, Peripheral)


#endif // IoT_BtLE_PeripheralServerHelper_INCLUDED

