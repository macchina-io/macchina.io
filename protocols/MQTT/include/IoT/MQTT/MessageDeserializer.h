//
// MessageDeserializer.h
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


#ifndef TypeDeserializer_IoT_MQTT_Message_INCLUDED
#define TypeDeserializer_IoT_MQTT_Message_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::MQTT::Message>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::MQTT::Message& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::MQTT::Message& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"binaryPayload"s,"payload"s,"qos"s,"retained"s};
		TypeDeserializer<std::vector < char > >::deserialize(REMOTING__NAMES[0], false, deser, value.binaryPayload);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], false, deser, value.payload);
		TypeDeserializer<int >::deserialize(REMOTING__NAMES[2], true, deser, value.qos);
		TypeDeserializer<bool >::deserialize(REMOTING__NAMES[3], false, deser, value.retained);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_MQTT_Message_INCLUDED

