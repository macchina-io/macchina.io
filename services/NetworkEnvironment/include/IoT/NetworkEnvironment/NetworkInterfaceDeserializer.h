//
// NetworkInterfaceDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_NetworkEnvironment_NetworkInterface_INCLUDED
#define TypeDeserializer_IoT_NetworkEnvironment_NetworkInterface_INCLUDED


#include "IoT/NetworkEnvironment/AddressTupleDeserializer.h"
#include "IoT/NetworkEnvironment/AddressTupleSerializer.h"
#include "IoT/NetworkEnvironment/NetworkEnvironmentService.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::NetworkEnvironment::NetworkInterface>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::NetworkEnvironment::NetworkInterface& value)
	{
		using namespace std::string_literals;
		
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::NetworkEnvironment::NetworkInterface& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"index"s,"name"s,"displayName"s,"adapterName"s,"macAddress"s,"addresses"s,"mtu"s,"type"s,"supportsIP"s,"supportsIPv4"s,"supportsIPv6"s,"supportsBroadcast"s,"supportsMulticast"s,"isLoopback"s,"isPointToPoint"s,"isRunning"s,"isUp"s};
		bool ret = false;
		TypeDeserializer<unsigned>::deserialize(REMOTING__NAMES[0], true, deser, value.index);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[1], true, deser, value.name);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[2], true, deser, value.displayName);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[3], true, deser, value.adapterName);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[4], true, deser, value.macAddress);
		TypeDeserializer<std::vector<IoT::NetworkEnvironment::AddressTuple>>::deserialize(REMOTING__NAMES[5], true, deser, value.addresses);
		TypeDeserializer<unsigned>::deserialize(REMOTING__NAMES[6], true, deser, value.mtu);
		int gentype;
		ret = TypeDeserializer<int>::deserialize(REMOTING__NAMES[7], true, deser, gentype);
		if (ret) value.type = static_cast<IoT::NetworkEnvironment::MIBInterfaceType>(gentype);
		TypeDeserializer<bool>::deserialize(REMOTING__NAMES[8], true, deser, value.supportsIP);
		TypeDeserializer<bool>::deserialize(REMOTING__NAMES[9], true, deser, value.supportsIPv4);
		TypeDeserializer<bool>::deserialize(REMOTING__NAMES[10], true, deser, value.supportsIPv6);
		TypeDeserializer<bool>::deserialize(REMOTING__NAMES[11], true, deser, value.supportsBroadcast);
		TypeDeserializer<bool>::deserialize(REMOTING__NAMES[12], true, deser, value.supportsMulticast);
		TypeDeserializer<bool>::deserialize(REMOTING__NAMES[13], true, deser, value.isLoopback);
		TypeDeserializer<bool>::deserialize(REMOTING__NAMES[14], true, deser, value.isPointToPoint);
		TypeDeserializer<bool>::deserialize(REMOTING__NAMES[15], true, deser, value.isRunning);
		TypeDeserializer<bool>::deserialize(REMOTING__NAMES[16], true, deser, value.isUp);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_NetworkEnvironment_NetworkInterface_INCLUDED

