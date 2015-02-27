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
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MQTT_MQTTClientSkeleton_INCLUDED
#define IoT_MQTT_MQTTClientSkeleton_INCLUDED


#include "IoT/MQTT/MQTTClientRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace MQTT {


class MQTTClientSkeleton: public Poco::RemotingNG::Skeleton
	/// The interface for MQTT clients.
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

