//
// FrameDeserializer.h
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


#ifndef TypeDeserializer_IoT_CAN_Frame_INCLUDED
#define TypeDeserializer_IoT_CAN_Frame_INCLUDED


#include "IoT/CAN/CANEndpoint.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::CAN::Frame>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::CAN::Frame& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::CAN::Frame& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"dlc","eff","id","payload","rtr"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[0], true, deser, value.dlc);
		TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], false, deser, value.eff);
		TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[2], true, deser, value.id);
		TypeDeserializer<Poco::Array < char, 8 > >::deserialize(REMOTING__NAMES[3], true, deser, value.payload);
		TypeDeserializer<bool >::deserialize(REMOTING__NAMES[4], false, deser, value.rtr);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_CAN_Frame_INCLUDED

