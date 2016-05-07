//
// DeviceStatusChangeDeserializer.h
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


#ifndef TypeDeserializer_IoT_DeviceStatus_DeviceStatusChange_INCLUDED
#define TypeDeserializer_IoT_DeviceStatus_DeviceStatusChange_INCLUDED


#include "IoT/DeviceStatus/DeviceStatusService.h"
#include "IoT/DeviceStatus/StatusMessageDeserializer.h"
#include "IoT/DeviceStatus/StatusMessageSerializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::DeviceStatus::DeviceStatusChange>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::DeviceStatus::DeviceStatusChange& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::DeviceStatus::DeviceStatusChange& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"currentStatus","message","previousStatus"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool ret = false;
		int gencurrentStatus;
		ret = TypeDeserializer<int >::deserialize(REMOTING__NAMES[0], true, deser, gencurrentStatus);
		if (ret) value.currentStatus = static_cast<IoT::DeviceStatus::DeviceStatus>(gencurrentStatus);
		TypeDeserializer<Poco::Optional < IoT::DeviceStatus::StatusMessage > >::deserialize(REMOTING__NAMES[1], true, deser, value.message);
		int genpreviousStatus;
		ret = TypeDeserializer<int >::deserialize(REMOTING__NAMES[2], true, deser, genpreviousStatus);
		if (ret) value.previousStatus = static_cast<IoT::DeviceStatus::DeviceStatus>(genpreviousStatus);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_DeviceStatus_DeviceStatusChange_INCLUDED

