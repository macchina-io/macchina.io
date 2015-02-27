//
// TopicCountSerializer.h
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


#ifndef TypeSerializer_IoT_MQTT_TopicCount_INCLUDED
#define TypeSerializer_IoT_MQTT_TopicCount_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::MQTT::TopicCount>
{
public:
	static void serialize(const std::string& name, const IoT::MQTT::TopicCount& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::MQTT::TopicCount& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"messageCount","topic",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<int >::serialize(REMOTING__NAMES[0], value.messageCount, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.topic, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_MQTT_TopicCount_INCLUDED

