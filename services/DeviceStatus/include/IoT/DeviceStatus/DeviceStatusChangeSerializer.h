//
// DeviceStatusChangeSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_DeviceStatus_DeviceStatusChange_INCLUDED
#define TypeSerializer_IoT_DeviceStatus_DeviceStatusChange_INCLUDED


#include "IoT/DeviceStatus/DeviceStatusService.h"
#include "IoT/DeviceStatus/StatusMessageDeserializer.h"
#include "IoT/DeviceStatus/StatusMessageSerializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::DeviceStatus::DeviceStatusChange>
{
public:
	static void serialize(const std::string& name, const IoT::DeviceStatus::DeviceStatusChange& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::DeviceStatus::DeviceStatusChange& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"currentStatus","message","previousStatus",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<int >::serialize(REMOTING__NAMES[0], value.currentStatus, ser);
		TypeSerializer<Poco::Optional < IoT::DeviceStatus::StatusMessage > >::serialize(REMOTING__NAMES[1], value.message, ser);
		TypeSerializer<int >::serialize(REMOTING__NAMES[2], value.previousStatus, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_DeviceStatus_DeviceStatusChange_INCLUDED

