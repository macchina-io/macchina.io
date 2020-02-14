//
// PropertySerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_WebTunnel_Property_INCLUDED
#define TypeSerializer_IoT_WebTunnel_Property_INCLUDED


#include "IoT/WebTunnel/WebTunnelService.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::WebTunnel::Property>
{
public:
	static void serialize(const std::string& name, const IoT::WebTunnel::Property& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::WebTunnel::Property& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"name"s,"value"s,""s};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.name, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.value, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_WebTunnel_Property_INCLUDED

