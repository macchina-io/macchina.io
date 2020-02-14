//
// FilterDeserializer.h
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


#ifndef TypeDeserializer_IoT_CAN_Filter_INCLUDED
#define TypeDeserializer_IoT_CAN_Filter_INCLUDED


#include "IoT/CAN/CANEndpoint.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::CAN::Filter>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::CAN::Filter& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::CAN::Filter& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"id"s,"invert"s,"mask"s};
		TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[0], true, deser, value.id);
		TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], false, deser, value.invert);
		TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[2], true, deser, value.mask);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_CAN_Filter_INCLUDED

