//
// SensorServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SensorServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SensorServerHelper_INCLUDED
#define IoT_Devices_SensorServerHelper_INCLUDED


#include "IoT/Devices/ISensor.h"
#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/SensorRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class SensorServerHelper
	/// The base class for analog sensors, such as
	/// temperature or ambient light sensors.
	///
	/// In addition to the methods defined in this interface,
	/// a Sensor implementation should expose the following
	/// properties:
	///   - physicalQuantity (string): The physical quantity that is
	///     being measured by the sensor, e.g. "temperature".
	///   - physicalUnit (string): The physical unit the measured value
	///     is being represented in (e.g. "°C"), UTF-8 encoded.
	///     See the PHYSICAL_UNIT_* strings for predefined values.
	///   - displayValue (string, optional): The current value of the sensor,
	///     formatted as string for display purposes.
{
public:
	typedef IoT::Devices::Sensor Service;

	SensorServerHelper();
		/// Creates a SensorServerHelper.

	~SensorServerHelper();
		/// Destroys the SensorServerHelper.

	static Poco::AutoPtr<IoT::Devices::SensorRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::Sensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::Sensor instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::Sensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::Sensor instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::SensorRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::Sensor from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::SensorRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Sensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static SensorServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::SensorRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::SensorRemoteObject> SensorServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::Sensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return SensorServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void SensorServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	SensorServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string SensorServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::Sensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return SensorServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string SensorServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::SensorRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return SensorServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void SensorServerHelper::unregisterObject(const std::string& uri)
{
	SensorServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, Sensor)


#endif // IoT_Devices_SensorServerHelper_INCLUDED

