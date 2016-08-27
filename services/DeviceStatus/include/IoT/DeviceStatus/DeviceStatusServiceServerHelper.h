//
// DeviceStatusServiceServerHelper.h
//
// Library: IoT/DeviceStatus
// Package: Generated
// Module:  DeviceStatusServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_DeviceStatus_DeviceStatusServiceServerHelper_INCLUDED
#define IoT_DeviceStatus_DeviceStatusServiceServerHelper_INCLUDED


#include "IoT/DeviceStatus/DeviceStatusService.h"
#include "IoT/DeviceStatus/DeviceStatusServiceRemoteObject.h"
#include "IoT/DeviceStatus/IDeviceStatusService.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace DeviceStatus {


class DeviceStatusServiceServerHelper
	/// The DeviceStatusService keeps track of the current operational
	/// status of a device.
{
public:
	typedef IoT::DeviceStatus::DeviceStatusService Service;

	DeviceStatusServiceServerHelper();
		/// Creates a DeviceStatusServiceServerHelper.

	~DeviceStatusServiceServerHelper();
		/// Destroys the DeviceStatusServiceServerHelper.

	static Poco::AutoPtr<IoT::DeviceStatus::DeviceStatusServiceRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::DeviceStatus::DeviceStatusService instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::DeviceStatus::DeviceStatusService instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::DeviceStatus::DeviceStatusServiceRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::DeviceStatus::DeviceStatusService from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::DeviceStatus::DeviceStatusServiceRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static DeviceStatusServiceServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::DeviceStatus::DeviceStatusServiceRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::DeviceStatus::DeviceStatusServiceRemoteObject> DeviceStatusServiceServerHelper::createRemoteObject(Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return DeviceStatusServiceServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void DeviceStatusServiceServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	DeviceStatusServiceServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string DeviceStatusServiceServerHelper::registerObject(Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return DeviceStatusServiceServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string DeviceStatusServiceServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::DeviceStatus::DeviceStatusServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return DeviceStatusServiceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void DeviceStatusServiceServerHelper::unregisterObject(const std::string& uri)
{
	DeviceStatusServiceServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace DeviceStatus
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::DeviceStatus, DeviceStatusService)


#endif // IoT_DeviceStatus_DeviceStatusServiceServerHelper_INCLUDED

