//
// ZigBeeTransmitRequestDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_XBee_ZigBeeTransmitRequest_INCLUDED
#define TypeDeserializer_IoT_XBee_ZigBeeTransmitRequest_INCLUDED


#include "IoT/XBee/XBeeNode.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::XBee::ZigBeeTransmitRequest>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::XBee::ZigBeeTransmitRequest& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::XBee::ZigBeeTransmitRequest& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"broadcastRadius"s,"deviceAddress"s,"frameID"s,"networkAddress"s,"options"s,"payload"s};
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[0], true, deser, value.broadcastRadius);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, deser, value.deviceAddress);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[2], true, deser, value.frameID);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, deser, value.networkAddress);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[4], true, deser, value.options);
		TypeDeserializer<std::vector < Poco::UInt8 > >::deserialize(REMOTING__NAMES[5], true, deser, value.payload);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_XBee_ZigBeeTransmitRequest_INCLUDED

