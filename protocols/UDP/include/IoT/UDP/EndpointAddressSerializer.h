//
// EndpointAddressSerializer.h
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


#ifndef TypeSerializer_IoT_UDP_EndpointAddress_INCLUDED
#define TypeSerializer_IoT_UDP_EndpointAddress_INCLUDED


#include "IoT/UDP/UDPEndpoint.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::UDP::EndpointAddress>
{
public:
	static void serialize(const std::string& name, const IoT::UDP::EndpointAddress& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::UDP::EndpointAddress& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"ipAddress"s,"port"s,""s};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.ipAddress, ser);
		TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[1], value.port, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_UDP_EndpointAddress_INCLUDED

