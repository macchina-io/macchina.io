//
// MessageArrivedEventSerializer.h
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


#ifndef TypeSerializer_IoT_MQTT_MessageArrivedEvent_INCLUDED
#define TypeSerializer_IoT_MQTT_MessageArrivedEvent_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "IoT/MQTT/MessageDeserializer.h"
#include "IoT/MQTT/MessageSerializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::MQTT::MessageArrivedEvent>
{
public:
	static void serialize(const std::string& name, const IoT::MQTT::MessageArrivedEvent& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::MQTT::MessageArrivedEvent& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"dup","handled","message","topic",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[0], value.dup, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[1], value.handled, ser);
		TypeSerializer<IoT::MQTT::Message >::serialize(REMOTING__NAMES[2], value.message, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], value.topic, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_MQTT_MessageArrivedEvent_INCLUDED

