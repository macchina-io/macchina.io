//
// AddressTupleDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"address","broadcastOrDestinationAddress","subnetMask","version"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[0], true, deser, value.address);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, deser, value.broadcastOrDestinationAddress);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, deser, value.subnetMask);
		TypeDeserializer<int >::deserialize(REMOTING__NAMES[3], true, deser, value.version);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_NetworkEnvironment_AddressTuple_INCLUDED

