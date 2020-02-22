//
// FilterSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_CAN_Filter_INCLUDED
#define TypeSerializer_IoT_CAN_Filter_INCLUDED


#include "IoT/CAN/CANEndpoint.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::CAN::Filter>
{
public:
	static void serialize(const std::string& name, const IoT::CAN::Filter& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::CAN::Filter& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"id"s,"invert"s,"mask"s,""s};
		TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[0], value.id, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[1], value.invert, ser);
		TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[2], value.mask, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_CAN_Filter_INCLUDED

