//
// DeviceServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_DeviceServerHelper_INCLUDED
#define IoT_Devices_DeviceServerHelper_INCLUDED


#include "IoT/Devices/Device.h"
#include "IoT/Devices/DeviceRemoteObject.h"
#include "IoT/Devices/IDevice.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class DeviceServerHelper
	/// The base class for all devices and sensors.
	///
	/// This class defines a generic interface for setting
	/// and querying device properties and features.
	///
	/// Every implementation of Device should expose the
	/// following properties:
	///   - symbolicName (string): A name in reverse DNS notation
	///     that identifies the device type (e.g., "io.macchina.serialport").
	///   - name (string): A human-readable device type (e.g., "Serial Port").
{
public:
	typedef IoT::Devices::Device Service;

	DeviceServerHelper();
		/// Creates a DeviceServerHelper.

	~DeviceServerHelper();
		/// Destroys the DeviceServerHelper.

	static Poco::AutoPtr<IoT::Devices::DeviceRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::Device> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::Device instance.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::Device> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::Device instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::DeviceRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::Device from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::DeviceRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Device> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	static DeviceServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::DeviceRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::DeviceRemoteObject> DeviceServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::Device> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return DeviceServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline std::string DeviceServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::Device> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return DeviceServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string DeviceServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::DeviceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return DeviceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void DeviceServerHelper::unregisterObject(const std::string& uri)
{
	DeviceServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, Device)


#endif // IoT_Devices_DeviceServerHelper_INCLUDED

