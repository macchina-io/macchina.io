//
// PacketSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_UDP_Packet_INCLUDED
#define TypeSerializer_IoT_UDP_Packet_INCLUDED


#include "IoT/UDP/EndpointAddressDeserializer.h"
#include "IoT/UDP/EndpointAddressSerializer.h"
#include "IoT/UDP/UDPEndpoint.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::UDP::Packet>
{
public:
	static void serialize(const std::string& name, const IoT::UDP::Packet& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::UDP::Packet& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"destination"s,"payload"s,"source"s,""s};
		TypeSerializer<IoT::UDP::EndpointAddress >::serialize(REMOTING__NAMES[0], value.destination, ser);
		TypeSerializer<std::vector < char > >::serialize(REMOTING__NAMES[1], value.payload, ser);
		TypeSerializer<IoT::UDP::EndpointAddress >::serialize(REMOTING__NAMES[2], value.source, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_UDP_Packet_INCLUDED

