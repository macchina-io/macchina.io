//
// DeviceNodeSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_Devices_DeviceNode_INCLUDED
#define TypeSerializer_IoT_Devices_DeviceNode_INCLUDED


#include "IoT/Devices/DeviceTree.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Devices::DeviceNode>
{
public:
	static void serialize(const std::string& name, const IoT::Devices::DeviceNode& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Devices::DeviceNode& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"composite"s,"fragments"s,"id"s,"name"s,"type"s,""s};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.composite, ser);
		TypeSerializer<Poco::Optional < std::vector < std::string > > >::serialize(REMOTING__NAMES[1], value.fragments, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], value.id, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], value.name, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[4], value.type, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Devices_DeviceNode_INCLUDED

