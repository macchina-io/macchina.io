//
// CANFrameDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_CAN_CANFrame_INCLUDED
#define TypeDeserializer_IoT_CAN_CANFrame_INCLUDED


#include "IoT/CAN/CANFrame.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::CAN::CANFrame>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::CAN::CANFrame& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::CAN::CANFrame& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"id"s,"flags"s,"dlc"s,"payload"s};
		bool ret = false;
		Poco::UInt32 gen_id;
		ret = TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[0], true, deser, gen_id);
		if (ret) value.id(gen_id);
		Poco::UInt8 gen_flags;
		ret = TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[1], false, deser, gen_flags);
		if (ret) value.flags(gen_flags);
		Poco::UInt8 gen_dlc;
		ret = TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[2], true, deser, gen_dlc);
		if (ret) value.dlc(gen_dlc);
		Poco::Array < char, 8 > gen_payload;
		ret = TypeDeserializer<Poco::Array < char, 8 > >::deserialize(REMOTING__NAMES[3], true, deser, gen_payload);
		if (ret) value.payload(gen_payload);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_CAN_CANFrame_INCLUDED

