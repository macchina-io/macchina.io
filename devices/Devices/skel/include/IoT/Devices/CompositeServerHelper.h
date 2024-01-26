//
// CompositeServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  CompositeServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_CompositeServerHelper_INCLUDED
#define IoT_Devices_CompositeServerHelper_INCLUDED


#include "IoT/Devices/Composite.h"
#include "IoT/Devices/CompositeRemoteObject.h"
#include "IoT/Devices/IComposite.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class CompositeServerHelper
	/// A composite device consists of one or
	/// more sub devices or device fragments.
	///
	/// Composites are used to build hierarchies
	/// of devices, also known as device trees.
	/// This is intended to represent the hierarchical
	/// structure of a more complex device.
	///
	/// For example, for an electric vehicle, the
	/// (simplified) device tree may look like:
	///
	///     / (root)
	///      Battery/
	///       Voltage
	///       Temperature
	///       ChargeLevel
	///      Motor/
	///        Switch
	///        PowerUsage
	///        RPM
	///        Temperature
	///        ...    
	///      ...
	///
	/// The DeviceTree class can be used to conveniently
	/// find a device in the tree.
{
public:
	using Service = IoT::Devices::Composite;

	CompositeServerHelper();
		/// Creates a CompositeServerHelper.

	~CompositeServerHelper();
		/// Destroys the CompositeServerHelper.

	static Poco::AutoPtr<IoT::Devices::CompositeRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::Composite> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::Composite instance.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::Composite> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::Composite instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::CompositeRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::Composite from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::CompositeRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Composite> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	static CompositeServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::CompositeRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::CompositeRemoteObject> CompositeServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::Composite> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return CompositeServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline std::string CompositeServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::Composite> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return CompositeServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string CompositeServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::CompositeRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return CompositeServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void CompositeServerHelper::unregisterObject(const std::string& uri)
{
	CompositeServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, Composite)


#endif // IoT_Devices_CompositeServerHelper_INCLUDED

