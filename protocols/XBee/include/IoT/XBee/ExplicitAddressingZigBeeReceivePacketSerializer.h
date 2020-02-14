//
// ExplicitAddressingZigBeeReceivePacketSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_XBee_ExplicitAddressingZigBeeReceivePacket_INCLUDED
#define TypeSerializer_IoT_XBee_ExplicitAddressingZigBeeReceivePacket_INCLUDED


#include "IoT/XBee/XBeeNode.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::XBee::ExplicitAddressingZigBeeReceivePacket>
{
public:
	static void serialize(const std::string& name, const IoT::XBee::ExplicitAddressingZigBeeReceivePacket& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::XBee::ExplicitAddressingZigBeeReceivePacket& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"clusterID"s,"destinationEndpoint"s,"deviceAddress"s,"networkAddress"s,"options"s,"payload"s,"profileID"s,"sourceEndpoint"s,""s};
		TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[0], value.clusterID, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[1], value.destinationEndpoint, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], value.deviceAddress, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], value.networkAddress, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[4], value.options, ser);
		TypeSerializer<std::vector < Poco::UInt8 > >::serialize(REMOTING__NAMES[5], value.payload, ser);
		TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[6], value.profileID, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[7], value.sourceEndpoint, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_XBee_ExplicitAddressingZigBeeReceivePacket_INCLUDED

