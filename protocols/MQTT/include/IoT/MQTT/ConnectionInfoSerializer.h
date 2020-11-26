//
// ConnectionInfoSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_MQTT_ConnectionInfo_INCLUDED
#define TypeSerializer_IoT_MQTT_ConnectionInfo_INCLUDED


#include "IoT/MQTT/Types.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::MQTT::ConnectionInfo>
{
public:
	static void serialize(const std::string& name, const IoT::MQTT::ConnectionInfo& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::MQTT::ConnectionInfo& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"serverURI"s,"sessionPresent"s,""s};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.serverURI, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[1], value.sessionPresent, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_MQTT_ConnectionInfo_INCLUDED

