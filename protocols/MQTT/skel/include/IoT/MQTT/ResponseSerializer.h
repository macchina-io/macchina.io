//
// ResponseSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_MQTT_Response_INCLUDED
#define TypeSerializer_IoT_MQTT_Response_INCLUDED


#include "IoT/MQTT/PropertyDeserializer.h"
#include "IoT/MQTT/PropertySerializer.h"
#include "IoT/MQTT/Types.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::MQTT::Response>
{
public:
	static void serialize(const std::string& name, const IoT::MQTT::Response& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::MQTT::Response& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"properties"s,"reasonCode"s,"reasonCodes"s,""s};
		TypeSerializer<std::vector < IoT::MQTT::Property > >::serialize(REMOTING__NAMES[0], value.properties, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[1], value.reasonCode, ser);
		TypeSerializer<std::vector < Poco::UInt8 > >::serialize(REMOTING__NAMES[2], value.reasonCodes, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_MQTT_Response_INCLUDED

