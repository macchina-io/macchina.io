//
// MQTTClientSkeleton.h
//
// Library: IoT/MQTT
// Package: Generated
// Module:  MQTTClientSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_MQTT_MQTTClientSkeleton_INCLUDED
#define IoT_MQTT_MQTTClientSkeleton_INCLUDED


#include "IoT/MQTT/MQTTClientRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace MQTT {


class MQTTClientSkeleton: public Poco::RemotingNG::Skeleton
	/// The interface for MQTT clients.
	///
	/// Implementations are expected to receive their client ID and
	/// server URI via an implementation defined configuration mechanism.
	/// Once configured, a MQTTClient always uses the same client ID and
	/// connects to the same server. A MQTT client should automatically
	/// attempt to reconnect if the connection to the server is lost.
	///
	/// A single client instance can either support MQTT version 3.1/3.1.1
	/// or version 5. Which MQTT version is supported by the client is
	/// determined when configuring the client.
	///
	/// Users of the class must call the appropriate methods supporting
	/// the client's configured MQTT version.
{
public:
	MQTTClientSkeleton();
		/// Creates a MQTTClientSkeleton.

	virtual ~MQTTClientSkeleton();
		/// Destroys a MQTTClientSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& MQTTClientSkeleton::remoting__typeId() const
{
	return IMQTTClient::remoting__typeId();
}


} // namespace MQTT
} // namespace IoT


#endif // IoT_MQTT_MQTTClientSkeleton_INCLUDED

