//
// ExplicitAddressingZigBeeTransmitRequestSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_XBee_ExplicitAddressingZigBeeTransmitRequest_INCLUDED
#define TypeSerializer_IoT_XBee_ExplicitAddressingZigBeeTransmitRequest_INCLUDED


#include "IoT/XBee/XBeeNode.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::XBee::ExplicitAddressingZigBeeTransmitRequest>
{
public:
	static void serialize(const std::string& name, const IoT::XBee::ExplicitAddressingZigBeeTransmitRequest& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::XBee::ExplicitAddressingZigBeeTransmitRequest& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"broadcastRadius"s,"clusterID"s,"destinationEndpoint"s,"deviceAddress"s,"frameID"s,"networkAddress"s,"options"s,"payload"s,"profileID"s,"sourceEndpoint"s,""s};
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[0], value.broadcastRadius, ser);
		TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[1], value.clusterID, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[2], value.destinationEndpoint, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], value.deviceAddress, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[4], value.frameID, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[5], value.networkAddress, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[6], value.options, ser);
		TypeSerializer<std::vector < Poco::UInt8 > >::serialize(REMOTING__NAMES[7], value.payload, ser);
		TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[8], value.profileID, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[9], value.sourceEndpoint, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_XBee_ExplicitAddressingZigBeeTransmitRequest_INCLUDED

