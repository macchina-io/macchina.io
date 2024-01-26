//
// SubscribeOptionsSerializer.h
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


#ifndef TypeSerializer_IoT_MQTT_SubscribeOptions_INCLUDED
#define TypeSerializer_IoT_MQTT_SubscribeOptions_INCLUDED


#include "IoT/MQTT/Types.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::MQTT::SubscribeOptions>
{
public:
	static void serialize(const std::string& name, const IoT::MQTT::SubscribeOptions& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::MQTT::SubscribeOptions& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"noLocal"s,"retainAsPublished"s,"retainHandling"s,""s};
		TypeSerializer<bool >::serialize(REMOTING__NAMES[0], value.noLocal, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[1], value.retainAsPublished, ser);
		TypeSerializer<int >::serialize(REMOTING__NAMES[2], value.retainHandling, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_MQTT_SubscribeOptions_INCLUDED

