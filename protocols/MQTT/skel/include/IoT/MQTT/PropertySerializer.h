//
// PropertySerializer.h
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


#ifndef TypeSerializer_IoT_MQTT_Property_INCLUDED
#define TypeSerializer_IoT_MQTT_Property_INCLUDED


#include "IoT/MQTT/Types.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::MQTT::Property>
{
public:
	static void serialize(const std::string& name, const IoT::MQTT::Property& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::MQTT::Property& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"binaryValue"s,"byteValue"s,"identifier"s,"name"s,"stringValue"s,"uint16Value"s,"uint32Value"s,""s};
		TypeSerializer<Poco::Optional < std::vector < char > > >::serialize(REMOTING__NAMES[0], value.binaryValue, ser);
		TypeSerializer<Poco::Optional < Poco::UInt8 > >::serialize(REMOTING__NAMES[1], value.byteValue, ser);
		TypeSerializer<int >::serialize(REMOTING__NAMES[2], static_cast<int>(value.identifier), ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[3], value.name, ser);
		TypeSerializer<Poco::Optional < std::string > >::serialize(REMOTING__NAMES[4], value.stringValue, ser);
		TypeSerializer<Poco::Optional < Poco::UInt16 > >::serialize(REMOTING__NAMES[5], value.uint16Value, ser);
		TypeSerializer<Poco::Optional < Poco::UInt32 > >::serialize(REMOTING__NAMES[6], value.uint32Value, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_MQTT_Property_INCLUDED

