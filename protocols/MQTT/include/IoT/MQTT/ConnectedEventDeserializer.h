//
// ConnectedEventDeserializer.h
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


#ifndef TypeDeserializer_IoT_MQTT_ConnectedEvent_INCLUDED
#define TypeDeserializer_IoT_MQTT_ConnectedEvent_INCLUDED


#include "IoT/MQTT/ConnectionInfoDeserializer.h"
#include "IoT/MQTT/ConnectionInfoSerializer.h"
#include "IoT/MQTT/MQTTClient.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::MQTT::ConnectedEvent>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::MQTT::ConnectedEvent& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::MQTT::ConnectedEvent& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"connectionInfo"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<IoT::MQTT::ConnectionInfo >::deserialize(REMOTING__NAMES[0], true, deser, value.connectionInfo);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_MQTT_ConnectedEvent_INCLUDED

