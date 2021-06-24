//
// DeviceStatusChangeSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_Devices_DeviceStatusChange_INCLUDED
#define TypeSerializer_IoT_Devices_DeviceStatusChange_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Devices::DeviceStatusChange>
{
public:
	static void serialize(const std::string& name, const IoT::Devices::DeviceStatusChange& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Devices::DeviceStatusChange& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"current"s,"previous"s,""s};
		TypeSerializer<int >::serialize(REMOTING__NAMES[0], static_cast<int>(value.current), ser);
		TypeSerializer<int >::serialize(REMOTING__NAMES[1], static_cast<int>(value.previous), ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Devices_DeviceStatusChange_INCLUDED

