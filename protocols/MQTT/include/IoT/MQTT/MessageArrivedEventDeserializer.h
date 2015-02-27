//
// MessageArrivedEventDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeDeserializer_IoT_MQTT_MessageArrivedEvent_INCLUDED
#define TypeDeserializer_IoT_MQTT_MessageArrivedEvent_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "IoT/MQTT/MessageDeserializer.h"
#include "IoT/MQTT/MessageSerializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::MQTT::MessageArrivedEvent>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::MQTT::MessageArrivedEvent& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::MQTT::MessageArrivedEvent& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"dup","handled","message","topic"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<bool >::deserialize(REMOTING__NAMES[0], true, deser, value.dup);
		TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], true, deser, value.handled);
		TypeDeserializer<IoT::MQTT::Message >::deserialize(REMOTING__NAMES[2], true, deser, value.message);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, deser, value.topic);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_MQTT_MessageArrivedEvent_INCLUDED

