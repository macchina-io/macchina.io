//
// StatusMessageDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeDeserializer_IoT_DeviceStatus_StatusMessage_INCLUDED
#define TypeDeserializer_IoT_DeviceStatus_StatusMessage_INCLUDED


#include "IoT/DeviceStatus/DeviceStatusService.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::DeviceStatus::StatusMessage>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::DeviceStatus::StatusMessage& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::DeviceStatus::StatusMessage& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"acknowledgeable","acknowledged","id","messageClass","source","status","text","timestamp"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool ret = false;
		TypeDeserializer<bool >::deserialize(REMOTING__NAMES[0], true, deser, value.acknowledgeable);
		TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], true, deser, value.acknowledged);
		TypeDeserializer<Poco::Int64 >::deserialize(REMOTING__NAMES[2], true, deser, value.id);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, deser, value.messageClass);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[4], true, deser, value.source);
		int genstatus;
		ret = TypeDeserializer<int >::deserialize(REMOTING__NAMES[5], true, deser, genstatus);
		if (ret) value.status = static_cast<IoT::DeviceStatus::DeviceStatus>(genstatus);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[6], true, deser, value.text);
		TypeDeserializer<Poco::DateTime >::deserialize(REMOTING__NAMES[7], true, deser, value.timestamp);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_DeviceStatus_StatusMessage_INCLUDED

