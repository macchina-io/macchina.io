//
// StatisticsDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_MQTT_Statistics_INCLUDED
#define TypeDeserializer_IoT_MQTT_Statistics_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "IoT/MQTT/TopicCountDeserializer.h"
#include "IoT/MQTT/TopicCountSerializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::MQTT::Statistics>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::MQTT::Statistics& value)
	{
		using namespace std::string_literals;
		
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::MQTT::Statistics& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"publishedMessages"s,"receivedMessages"s};
		TypeDeserializer<std::vector < IoT::MQTT::TopicCount > >::deserialize(REMOTING__NAMES[0], true, deser, value.publishedMessages);
		TypeDeserializer<std::vector < IoT::MQTT::TopicCount > >::deserialize(REMOTING__NAMES[1], true, deser, value.receivedMessages);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_MQTT_Statistics_INCLUDED

