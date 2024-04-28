//
// NetworkInterfaceSerializer.h
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


#ifndef TypeSerializer_IoT_NetworkEnvironment_NetworkInterface_INCLUDED
#define TypeSerializer_IoT_NetworkEnvironment_NetworkInterface_INCLUDED


#include "IoT/NetworkEnvironment/AddressTupleDeserializer.h"
#include "IoT/NetworkEnvironment/AddressTupleSerializer.h"
#include "IoT/NetworkEnvironment/NetworkEnvironmentService.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::NetworkEnvironment::NetworkInterface>
{
public:
	static void serialize(const std::string& name, const IoT::NetworkEnvironment::NetworkInterface& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::NetworkEnvironment::NetworkInterface& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"index"s,"name"s,"displayName"s,"adapterName"s,"macAddress"s,"addresses"s,"mtu"s,"type"s,"supportsIP"s,"supportsIPv4"s,"supportsIPv6"s,"supportsBroadcast"s,"supportsMulticast"s,"isLoopback"s,"isPointToPoint"s,"isRunning"s,"isUp"s,""s};
		TypeSerializer<unsigned>::serialize(REMOTING__NAMES[0], value.index, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[1], value.name, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[2], value.displayName, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[3], value.adapterName, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[4], value.macAddress, ser);
		TypeSerializer<std::vector<IoT::NetworkEnvironment::AddressTuple>>::serialize(REMOTING__NAMES[5], value.addresses, ser);
		TypeSerializer<unsigned>::serialize(REMOTING__NAMES[6], value.mtu, ser);
		TypeSerializer<int>::serialize(REMOTING__NAMES[7], static_cast<int>(value.type), ser);
		TypeSerializer<bool>::serialize(REMOTING__NAMES[8], value.supportsIP, ser);
		TypeSerializer<bool>::serialize(REMOTING__NAMES[9], value.supportsIPv4, ser);
		TypeSerializer<bool>::serialize(REMOTING__NAMES[10], value.supportsIPv6, ser);
		TypeSerializer<bool>::serialize(REMOTING__NAMES[11], value.supportsBroadcast, ser);
		TypeSerializer<bool>::serialize(REMOTING__NAMES[12], value.supportsMulticast, ser);
		TypeSerializer<bool>::serialize(REMOTING__NAMES[13], value.isLoopback, ser);
		TypeSerializer<bool>::serialize(REMOTING__NAMES[14], value.isPointToPoint, ser);
		TypeSerializer<bool>::serialize(REMOTING__NAMES[15], value.isRunning, ser);
		TypeSerializer<bool>::serialize(REMOTING__NAMES[16], value.isUp, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_NetworkEnvironment_NetworkInterface_INCLUDED

