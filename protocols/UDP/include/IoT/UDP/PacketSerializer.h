//
// PacketSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::UDP::Packet& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"destination","payload","source",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<IoT::UDP::EndpointAddress >::serialize(REMOTING__NAMES[0], value.destination, ser);
		TypeSerializer<std::vector < char > >::serialize(REMOTING__NAMES[1], value.payload, ser);
		TypeSerializer<IoT::UDP::EndpointAddress >::serialize(REMOTING__NAMES[2], value.source, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_UDP_Packet_INCLUDED

