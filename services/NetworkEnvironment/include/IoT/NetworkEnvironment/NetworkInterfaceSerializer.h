//
// NetworkInterfaceSerializer.h
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
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::NetworkEnvironment::NetworkInterface& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"adapterName","addresses","displayName","index","isLoopback","isPointToPoint","isRunning","isUp","macAddress","mtu","name","supportsBroadcast","supportsIP","supportsIPv4","supportsIPv6","supportsMulticast","type",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.adapterName, ser);
		TypeSerializer<std::vector < IoT::NetworkEnvironment::AddressTuple > >::serialize(REMOTING__NAMES[1], value.addresses, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], value.displayName, ser);
		TypeSerializer<unsigned >::serialize(REMOTING__NAMES[3], value.index, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[4], value.isLoopback, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[5], value.isPointToPoint, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[6], value.isRunning, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[7], value.isUp, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[8], value.macAddress, ser);
		TypeSerializer<unsigned >::serialize(REMOTING__NAMES[9], value.mtu, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[10], value.name, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[11], value.supportsBroadcast, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[12], value.supportsIP, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[13], value.supportsIPv4, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[14], value.supportsIPv6, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[15], value.supportsMulticast, ser);
		TypeSerializer<int >::serialize(REMOTING__NAMES[16], value.type, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_NetworkEnvironment_NetworkInterface_INCLUDED

