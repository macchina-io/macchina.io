//
// TopicQoSSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_MQTT_TopicQoS_INCLUDED
#define TypeSerializer_IoT_MQTT_TopicQoS_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::MQTT::TopicQoS>
{
public:
	static void serialize(const std::string& name, const IoT::MQTT::TopicQoS& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::MQTT::TopicQoS& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"qos"s,"topic"s,""s};
		TypeSerializer<int >::serialize(REMOTING__NAMES[0], value.qos, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.topic, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_MQTT_TopicQoS_INCLUDED

