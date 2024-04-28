//
// AddressTupleSerializer.h
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


#ifndef TypeSerializer_IoT_NetworkEnvironment_AddressTuple_INCLUDED
#define TypeSerializer_IoT_NetworkEnvironment_AddressTuple_INCLUDED


#include "IoT/NetworkEnvironment/NetworkEnvironmentService.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::NetworkEnvironment::AddressTuple>
{
public:
	static void serialize(const std::string& name, const IoT::NetworkEnvironment::AddressTuple& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::NetworkEnvironment::AddressTuple& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"version"s,"address"s,"subnetMask"s,"broadcastOrDestinationAddress"s,""s};
		TypeSerializer<int>::serialize(REMOTING__NAMES[0], value.version, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[1], value.address, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[2], value.subnetMask, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[3], value.broadcastOrDestinationAddress, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_NetworkEnvironment_AddressTuple_INCLUDED

