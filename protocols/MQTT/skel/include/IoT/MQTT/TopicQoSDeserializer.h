//
// TopicQoSDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_MQTT_TopicQoS_INCLUDED
#define TypeDeserializer_IoT_MQTT_TopicQoS_INCLUDED


#include "IoT/MQTT/Types.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::MQTT::TopicQoS>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::MQTT::TopicQoS& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::MQTT::TopicQoS& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"topic"s,"qos"s};
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[0], true, deser, value.topic);
		TypeDeserializer<int>::deserialize(REMOTING__NAMES[1], true, deser, value.qos);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_MQTT_TopicQoS_INCLUDED

