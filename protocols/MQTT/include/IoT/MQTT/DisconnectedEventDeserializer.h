//
// DisconnectedEventDeserializer.h
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


#ifndef TypeDeserializer_IoT_MQTT_DisconnectedEvent_INCLUDED
#define TypeDeserializer_IoT_MQTT_DisconnectedEvent_INCLUDED


#include "IoT/MQTT/PropertyDeserializer.h"
#include "IoT/MQTT/PropertySerializer.h"
#include "IoT/MQTT/Types.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::MQTT::DisconnectedEvent>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::MQTT::DisconnectedEvent& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::MQTT::DisconnectedEvent& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"properties"s,"reasonCode"s};
		bool ret = false;
		TypeDeserializer<std::vector < IoT::MQTT::Property > >::deserialize(REMOTING__NAMES[0], true, deser, value.properties);
		int genreasonCode;
		ret = TypeDeserializer<int >::deserialize(REMOTING__NAMES[1], true, deser, genreasonCode);
		if (ret) value.reasonCode = static_cast<IoT::MQTT::ReasonCode>(genreasonCode);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_MQTT_DisconnectedEvent_INCLUDED

