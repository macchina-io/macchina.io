//
// MQTTClientRemoteObject.h
//
// Library: IoT/MQTT
// Package: Generated
// Module:  MQTTClientRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MQTT_MQTTClientRemoteObject_INCLUDED
#define IoT_MQTT_MQTTClientRemoteObject_INCLUDED


#include "IoT/MQTT/IMQTTClient.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace MQTT {


class MQTTClientRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::MQTT::IMQTTClient
	/// The interface for MQTT clients.
	///
	/// Implementations are expected to receive their client ID and
	/// server URI via an implementation defined configuration mechanism.
	/// Once configured, a MQTTClient always uses the same client ID and
	/// connects to the same server. A MQTT client should automatically
	/// attempt to reconnect if the connection to the server is lost.
{
public:
	typedef Poco::AutoPtr<MQTTClientRemoteObject> Ptr;

	MQTTClientRemoteObject();
		/// Creates a MQTTClientRemoteObject.

	virtual ~MQTTClientRemoteObject();
		/// Destroys the MQTTClientRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& MQTTClientRemoteObject::remoting__typeId() const
{
	return IMQTTClient::remoting__typeId();
}


} // namespace MQTT
} // namespace IoT


#endif // IoT_MQTT_MQTTClientRemoteObject_INCLUDED

