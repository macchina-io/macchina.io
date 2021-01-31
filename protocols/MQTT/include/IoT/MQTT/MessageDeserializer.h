//
// MessageDeserializer.h
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


#ifndef TypeDeserializer_IoT_MQTT_Message_INCLUDED
#define TypeDeserializer_IoT_MQTT_Message_INCLUDED


#include "IoT/MQTT/PropertyDeserializer.h"
#include "IoT/MQTT/PropertySerializer.h"
#include "IoT/MQTT/Types.h"
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
		
		static const std::string REMOTING__NAMES[] = {"binaryPayload"s,"payload"s,"properties"s,"qos"s,"retained"s};
		TypeDeserializer<std::vector < char > >::deserialize(REMOTING__NAMES[0], false, deser, value.binaryPayload);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], false, deser, value.payload);
		TypeDeserializer<std::vector < IoT::MQTT::Property > >::deserialize(REMOTING__NAMES[2], false, deser, value.properties);
		TypeDeserializer<int >::deserialize(REMOTING__NAMES[3], false, deser, value.qos);
		TypeDeserializer<bool >::deserialize(REMOTING__NAMES[4], false, deser, value.retained);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_MQTT_Message_INCLUDED

