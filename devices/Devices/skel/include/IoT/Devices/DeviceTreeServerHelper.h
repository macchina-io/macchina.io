//
// DeviceTreeServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceTreeServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_DeviceTreeServerHelper_INCLUDED
#define IoT_Devices_DeviceTreeServerHelper_INCLUDED


#include "IoT/Devices/DeviceTree.h"
#include "IoT/Devices/DeviceTreeRemoteObject.h"
#include "IoT/Devices/IDeviceTree.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class DeviceTreeServerHelper
	/// This class manages a hierarchical structure
	/// of devices, consisting of Composite and 
	/// leaf Device objects.
{
public:
	using Service = IoT::Devices::DeviceTree;

	DeviceTreeServerHelper();
		/// Creates a DeviceTreeServerHelper.

	~DeviceTreeServerHelper();
		/// Destroys the DeviceTreeServerHelper.

	static Poco::AutoPtr<IoT::Devices::DeviceTreeRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::DeviceTree> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::DeviceTree instance.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::DeviceTree> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::DeviceTree instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::DeviceTreeRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::DeviceTree from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::DeviceTreeRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::DeviceTree> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	static DeviceTreeServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::DeviceTreeRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::DeviceTreeRemoteObject> DeviceTreeServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::DeviceTree> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return DeviceTreeServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline std::string DeviceTreeServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::DeviceTree> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return DeviceTreeServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string DeviceTreeServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::DeviceTreeRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return DeviceTreeServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void DeviceTreeServerHelper::unregisterObject(const std::string& uri)
{
	DeviceTreeServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, DeviceTree)


#endif // IoT_Devices_DeviceTreeServerHelper_INCLUDED

