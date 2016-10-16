//
// StatusUpdateSerializer.h
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


#ifndef TypeSerializer_IoT_DeviceStatus_StatusUpdate_INCLUDED
#define TypeSerializer_IoT_DeviceStatus_StatusUpdate_INCLUDED


#include "IoT/DeviceStatus/DeviceStatusService.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::DeviceStatus::StatusUpdate>
{
public:
	static void serialize(const std::string& name, const IoT::DeviceStatus::StatusUpdate& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::DeviceStatus::StatusUpdate& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"acknowledgeable","messageClass","source","status","text",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[0], value.acknowledgeable, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.messageClass, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], value.source, ser);
		TypeSerializer<int >::serialize(REMOTING__NAMES[3], value.status, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[4], value.text, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_DeviceStatus_StatusUpdate_INCLUDED

