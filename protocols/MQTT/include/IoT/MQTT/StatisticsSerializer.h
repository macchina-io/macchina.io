//
// StatisticsSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_MQTT_Statistics_INCLUDED
#define TypeSerializer_IoT_MQTT_Statistics_INCLUDED


#include "IoT/MQTT/TopicCountDeserializer.h"
#include "IoT/MQTT/TopicCountSerializer.h"
#include "IoT/MQTT/Types.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::MQTT::Statistics>
{
public:
	static void serialize(const std::string& name, const IoT::MQTT::Statistics& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::MQTT::Statistics& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"publishedMessages"s,"receivedMessages"s,""s};
		TypeSerializer<std::vector < IoT::MQTT::TopicCount > >::serialize(REMOTING__NAMES[0], value.publishedMessages, ser);
		TypeSerializer<std::vector < IoT::MQTT::TopicCount > >::serialize(REMOTING__NAMES[1], value.receivedMessages, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_MQTT_Statistics_INCLUDED

