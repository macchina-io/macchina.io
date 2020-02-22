//
// UnitsOfMeasureServiceServerHelper.h
//
// Library: IoT/UnitsOfMeasure
// Package: Generated
// Module:  UnitsOfMeasureServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2018-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_UnitsOfMeasure_UnitsOfMeasureServiceServerHelper_INCLUDED
#define IoT_UnitsOfMeasure_UnitsOfMeasureServiceServerHelper_INCLUDED


#include "IoT/UnitsOfMeasure/IUnitsOfMeasureService.h"
#include "IoT/UnitsOfMeasure/UnitsOfMeasureService.h"
#include "IoT/UnitsOfMeasure/UnitsOfMeasureServiceRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace UnitsOfMeasure {


class UnitsOfMeasureServiceServerHelper
	/// The UnitsOfMeasureService service is mainly used to map
	/// [[http://unitsofmeasure.org/ucum.html Unified Code for Units of Measure]] (UCUM),
	/// codes, such as used with the IoT::Devices::Sensor interface, to display/print units.
	///
	/// It provides a programmatic interface to the
	/// [[http://unitsofmeasure.org/ucum-essence.xml UCUM-Essence XML file]]
	/// containing unit definitions.
{
public:
	using Service = IoT::UnitsOfMeasure::UnitsOfMeasureService;

	UnitsOfMeasureServiceServerHelper();
		/// Creates a UnitsOfMeasureServiceServerHelper.

	~UnitsOfMeasureServiceServerHelper();
		/// Destroys the UnitsOfMeasureServiceServerHelper.

	static Poco::AutoPtr<IoT::UnitsOfMeasure::UnitsOfMeasureServiceRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::UnitsOfMeasure::UnitsOfMeasureService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::UnitsOfMeasure::UnitsOfMeasureService instance.

	static std::string registerObject(Poco::SharedPtr<IoT::UnitsOfMeasure::UnitsOfMeasureService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::UnitsOfMeasure::UnitsOfMeasureService instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::UnitsOfMeasure::UnitsOfMeasureServiceRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::UnitsOfMeasure::UnitsOfMeasureService from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::UnitsOfMeasure::UnitsOfMeasureServiceRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::UnitsOfMeasure::UnitsOfMeasureService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	static UnitsOfMeasureServiceServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::UnitsOfMeasure::UnitsOfMeasureServiceRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::UnitsOfMeasure::UnitsOfMeasureServiceRemoteObject> UnitsOfMeasureServiceServerHelper::createRemoteObject(Poco::SharedPtr<IoT::UnitsOfMeasure::UnitsOfMeasureService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return UnitsOfMeasureServiceServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline std::string UnitsOfMeasureServiceServerHelper::registerObject(Poco::SharedPtr<IoT::UnitsOfMeasure::UnitsOfMeasureService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return UnitsOfMeasureServiceServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string UnitsOfMeasureServiceServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::UnitsOfMeasure::UnitsOfMeasureServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return UnitsOfMeasureServiceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void UnitsOfMeasureServiceServerHelper::unregisterObject(const std::string& uri)
{
	UnitsOfMeasureServiceServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace UnitsOfMeasure
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::UnitsOfMeasure, UnitsOfMeasureService)


#endif // IoT_UnitsOfMeasure_UnitsOfMeasureServiceServerHelper_INCLUDED

