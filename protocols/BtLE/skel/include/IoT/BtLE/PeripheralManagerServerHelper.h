//
// PeripheralManagerServerHelper.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralManagerServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_PeripheralManagerServerHelper_INCLUDED
#define IoT_BtLE_PeripheralManagerServerHelper_INCLUDED


#include "IoT/BtLE/IPeripheralManager.h"
#include "IoT/BtLE/PeripheralManager.h"
#include "IoT/BtLE/PeripheralManagerRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace BtLE {


class PeripheralManagerServerHelper
	/// This class manages Peripheral objects in the service registry.
	///
	/// Given the address of a Bt LE Peripheral device, the
	/// findPeripheral() method will return an existing Peripheral object
	/// representing that device if it already exists, or otherwise
	/// create a new Peripheral object using the PeripheralFactory.
	///
	/// Once a Peripheral is no longer needed, it can be disposed by
	/// calling remove().
{
public:
	using Service = IoT::BtLE::PeripheralManager;

	PeripheralManagerServerHelper();
		/// Creates a PeripheralManagerServerHelper.

	~PeripheralManagerServerHelper();
		/// Destroys the PeripheralManagerServerHelper.

	static Poco::AutoPtr<IoT::BtLE::PeripheralManagerRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::BtLE::PeripheralManager> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::BtLE::PeripheralManager instance.

	static std::string registerObject(Poco::SharedPtr<IoT::BtLE::PeripheralManager> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::BtLE::PeripheralManager instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::BtLE::PeripheralManagerRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::BtLE::PeripheralManager from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::BtLE::PeripheralManagerRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::BtLE::PeripheralManager> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	static PeripheralManagerServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::BtLE::PeripheralManagerRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::BtLE::PeripheralManagerRemoteObject> PeripheralManagerServerHelper::createRemoteObject(Poco::SharedPtr<IoT::BtLE::PeripheralManager> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return PeripheralManagerServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline std::string PeripheralManagerServerHelper::registerObject(Poco::SharedPtr<IoT::BtLE::PeripheralManager> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return PeripheralManagerServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string PeripheralManagerServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::BtLE::PeripheralManagerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return PeripheralManagerServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void PeripheralManagerServerHelper::unregisterObject(const std::string& uri)
{
	PeripheralManagerServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace BtLE
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::BtLE, PeripheralManager)


#endif // IoT_BtLE_PeripheralManagerServerHelper_INCLUDED

