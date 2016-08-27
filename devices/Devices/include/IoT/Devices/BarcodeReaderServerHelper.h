//
// BarcodeReaderServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  BarcodeReaderServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_BarcodeReaderServerHelper_INCLUDED
#define IoT_Devices_BarcodeReaderServerHelper_INCLUDED


#include "IoT/Devices/BarcodeReader.h"
#include "IoT/Devices/BarcodeReaderRemoteObject.h"
#include "IoT/Devices/IBarcodeReader.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class BarcodeReaderServerHelper
	/// The base class for barcode reader devices.
	///
	/// Only a single event, barcodeRead, is supported.
	/// Any device-specific configuration should be
	/// done via device features and properties.
{
public:
	typedef IoT::Devices::BarcodeReader Service;

	BarcodeReaderServerHelper();
		/// Creates a BarcodeReaderServerHelper.

	~BarcodeReaderServerHelper();
		/// Destroys the BarcodeReaderServerHelper.

	static Poco::AutoPtr<IoT::Devices::BarcodeReaderRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::BarcodeReader> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::BarcodeReader instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::BarcodeReader> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::BarcodeReader instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::BarcodeReaderRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::BarcodeReader from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::BarcodeReaderRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::BarcodeReader> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static BarcodeReaderServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::BarcodeReaderRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::BarcodeReaderRemoteObject> BarcodeReaderServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::BarcodeReader> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return BarcodeReaderServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void BarcodeReaderServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	BarcodeReaderServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string BarcodeReaderServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::BarcodeReader> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return BarcodeReaderServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string BarcodeReaderServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::BarcodeReaderRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return BarcodeReaderServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void BarcodeReaderServerHelper::unregisterObject(const std::string& uri)
{
	BarcodeReaderServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, BarcodeReader)


#endif // IoT_Devices_BarcodeReaderServerHelper_INCLUDED

