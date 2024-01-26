//
// DatapointFactoryServerHelper.h
//
// Library: IoT/Datapoints
// Package: Generated
// Module:  DatapointFactoryServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_DatapointFactoryServerHelper_INCLUDED
#define IoT_Datapoints_DatapointFactoryServerHelper_INCLUDED


#include "IoT/Datapoints/DatapointFactory.h"
#include "IoT/Datapoints/DatapointFactoryRemoteObject.h"
#include "IoT/Datapoints/IDatapointFactory.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Datapoints {


class DatapointFactoryServerHelper
	/// A factory for the dynamic creation of Datapoints.
{
public:
	using Service = IoT::Datapoints::DatapointFactory;

	DatapointFactoryServerHelper();
		/// Creates a DatapointFactoryServerHelper.

	~DatapointFactoryServerHelper();
		/// Destroys the DatapointFactoryServerHelper.

	static Poco::AutoPtr<IoT::Datapoints::DatapointFactoryRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Datapoints::DatapointFactory> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Datapoints::DatapointFactory instance.

	static std::string registerObject(Poco::SharedPtr<IoT::Datapoints::DatapointFactory> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Datapoints::DatapointFactory instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Datapoints::DatapointFactoryRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Datapoints::DatapointFactory from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Datapoints::DatapointFactoryRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Datapoints::DatapointFactory> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	static DatapointFactoryServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Datapoints::DatapointFactoryRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Datapoints::DatapointFactoryRemoteObject> DatapointFactoryServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Datapoints::DatapointFactory> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return DatapointFactoryServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline std::string DatapointFactoryServerHelper::registerObject(Poco::SharedPtr<IoT::Datapoints::DatapointFactory> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return DatapointFactoryServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string DatapointFactoryServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Datapoints::DatapointFactoryRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return DatapointFactoryServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void DatapointFactoryServerHelper::unregisterObject(const std::string& uri)
{
	DatapointFactoryServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Datapoints
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Datapoints, DatapointFactory)


#endif // IoT_Datapoints_DatapointFactoryServerHelper_INCLUDED

