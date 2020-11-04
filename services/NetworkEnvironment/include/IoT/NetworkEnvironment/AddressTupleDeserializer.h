//
// AddressTupleDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_NetworkEnvironment_AddressTuple_INCLUDED
#define TypeDeserializer_IoT_NetworkEnvironment_AddressTuple_INCLUDED


#include "IoT/NetworkEnvironment/NetworkEnvironmentService.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::NetworkEnvironment::AddressTuple>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::NetworkEnvironment::AddressTuple& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::NetworkEnvironment::AddressTuple& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"address"s,"broadcastOrDestinationAddress"s,"subnetMask"s,"version"s};
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[0], true, deser, value.address);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, deser, value.broadcastOrDestinationAddress);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, deser, value.subnetMask);
		TypeDeserializer<int >::deserialize(REMOTING__NAMES[3], true, deser, value.version);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_NetworkEnvironment_AddressTuple_INCLUDED

