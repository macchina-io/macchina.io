//
// TopicQoSDeserializer.h
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


#ifndef TypeDeserializer_IoT_MQTT_TopicQoS_INCLUDED
#define TypeDeserializer_IoT_MQTT_TopicQoS_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::MQTT::TopicQoS>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::MQTT::TopicQoS& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::MQTT::TopicQoS& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"qos","topic"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<int >::deserialize(REMOTING__NAMES[0], true, deser, value.qos);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, deser, value.topic);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_MQTT_TopicQoS_INCLUDED

