//
// MessageDeliveredEventSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_MQTT_MessageDeliveredEvent_INCLUDED
#define TypeSerializer_IoT_MQTT_MessageDeliveredEvent_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::MQTT::MessageDeliveredEvent>
{
public:
	static void serialize(const std::string& name, const IoT::MQTT::MessageDeliveredEvent& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::MQTT::MessageDeliveredEvent& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"token",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<int >::serialize(REMOTING__NAMES[0], value.token, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_MQTT_MessageDeliveredEvent_INCLUDED

