//
// CANFDFrameDeserializer.h
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


#ifndef TypeDeserializer_IoT_CAN_CANFDFrame_INCLUDED
#define TypeDeserializer_IoT_CAN_CANFDFrame_INCLUDED


#include "IoT/CAN/CANFDFrame.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::CAN::CANFDFrame>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::CAN::CANFDFrame& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::CAN::CANFDFrame& value)
	{
		static const std::string REMOTING__NAMES[] = {"id","flags","payload"};
		bool ret = false;
		Poco::UInt32 gen_id;
		ret = TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[0], true, deser, gen_id);
		if (ret) value.id(gen_id);
		Poco::UInt8 gen_flags;
		ret = TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[1], false, deser, gen_flags);
		if (ret) value.flags(gen_flags);
		std::vector < char > gen_payload;
		ret = TypeDeserializer<std::vector < char > >::deserialize(REMOTING__NAMES[2], true, deser, gen_payload);
		if (ret) value.payload(gen_payload);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_CAN_CANFDFrame_INCLUDED

