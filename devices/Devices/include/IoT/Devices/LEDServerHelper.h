//
// LEDServerHelper.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  LEDServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_LEDServerHelper_INCLUDED
#define IoT_Devices_LEDServerHelper_INCLUDED


#include "IoT/Devices/ILED.h"
#include "IoT/Devices/LED.h"
#include "IoT/Devices/LEDRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class LEDServerHelper
	/// The base class for LEDs.
	///
	/// Each instance of the LED class represents a single physical
	/// LED. Some LED devices support different brightness levels,
	/// this is accounted for by allowing to specify a brightness
	/// level in range 0.0 to 1.0, where 0.0 turns the LED off and
	/// 1.0 is the maximum brightness. 
	///
	/// Some implementations may also support blinking LEDs.
	/// This is exposed via the "blinkOn" and "blinkOff" properties,
	/// which take as values the time in milliseconds the LED should
	/// be on, or off, respectively. There is also a shortcut
	/// method, blink(), which allows setting both properties at once.
	///
	/// To turn on blinking, both "blinkOn" and "blinkOff" must be 
	/// set to a non-zero value. Furthermore, the brightness must
	/// be non-zero.
{
public:
	typedef IoT::Devices::LED Service;

	LEDServerHelper();
		/// Creates a LEDServerHelper.

	~LEDServerHelper();
		/// Destroys the LEDServerHelper.

	static Poco::AutoPtr<IoT::Devices::LEDRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::LED> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::LED instance.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::LED> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::LED instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::LEDRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::LED from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::LEDRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::LED> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	static LEDServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::LEDRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::LEDRemoteObject> LEDServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::LED> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return LEDServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline std::string LEDServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::LED> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return LEDServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string LEDServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::LEDRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return LEDServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void LEDServerHelper::unregisterObject(const std::string& uri)
{
	LEDServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, LED)


#endif // IoT_Devices_LEDServerHelper_INCLUDED

