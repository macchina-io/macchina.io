//
// ExplicitAddressingZigBeeReceivePacketDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeDeserializer_IoT_XBee_ExplicitAddressingZigBeeReceivePacket_INCLUDED
#define TypeDeserializer_IoT_XBee_ExplicitAddressingZigBeeReceivePacket_INCLUDED


#include "IoT/XBee/XBeeNode.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::XBee::ExplicitAddressingZigBeeReceivePacket>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::XBee::ExplicitAddressingZigBeeReceivePacket& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::XBee::ExplicitAddressingZigBeeReceivePacket& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"clusterID","destinationEndpoint","deviceAddress","networkAddress","options","payload","profileID","sourceEndpoint"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[0], true, deser, value.clusterID);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[1], true, deser, value.destinationEndpoint);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, deser, value.deviceAddress);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, deser, value.networkAddress);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[4], true, deser, value.options);
		TypeDeserializer<std::vector < Poco::UInt8 > >::deserialize(REMOTING__NAMES[5], true, deser, value.payload);
		TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[6], true, deser, value.profileID);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[7], true, deser, value.sourceEndpoint);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_XBee_ExplicitAddressingZigBeeReceivePacket_INCLUDED

