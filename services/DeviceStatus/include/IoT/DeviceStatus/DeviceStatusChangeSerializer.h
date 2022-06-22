//
// DeviceStatusChangeSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
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
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::DeviceStatus::DeviceStatusChange& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"currentStatus"s,"message"s,"previousStatus"s,""s};
		TypeSerializer<int >::serialize(REMOTING__NAMES[0], static_cast<int>(value.currentStatus), ser);
		TypeSerializer<Poco::Optional < IoT::DeviceStatus::StatusMessage > >::serialize(REMOTING__NAMES[1], value.message, ser);
		TypeSerializer<int >::serialize(REMOTING__NAMES[2], static_cast<int>(value.previousStatus), ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_DeviceStatus_DeviceStatusChange_INCLUDED

