//
// EndpointAddressDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeDeserializer_IoT_UDP_EndpointAddress_INCLUDED
#define TypeDeserializer_IoT_UDP_EndpointAddress_INCLUDED


#include "IoT/UDP/UDPEndpoint.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::UDP::EndpointAddress>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::UDP::EndpointAddress& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::UDP::EndpointAddress& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"ipAddress","port"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[0], true, deser, value.ipAddress);
		TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[1], true, deser, value.port);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_UDP_EndpointAddress_INCLUDED

