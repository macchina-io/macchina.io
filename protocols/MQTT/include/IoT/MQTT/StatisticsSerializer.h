//
// StatisticsSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_MQTT_Statistics_INCLUDED
#define TypeSerializer_IoT_MQTT_Statistics_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "IoT/MQTT/TopicCountDeserializer.h"
#include "IoT/MQTT/TopicCountSerializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::MQTT::Statistics>
{
public:
	static void serialize(const std::string& name, const IoT::MQTT::Statistics& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::MQTT::Statistics& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"publishedMessages","receivedMessages",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<std::vector < IoT::MQTT::TopicCount > >::serialize(REMOTING__NAMES[0], value.publishedMessages, ser);
		TypeSerializer<std::vector < IoT::MQTT::TopicCount > >::serialize(REMOTING__NAMES[1], value.receivedMessages, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_MQTT_Statistics_INCLUDED

