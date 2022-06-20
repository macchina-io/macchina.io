//
// CANFrameSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_CAN_CANFrame_INCLUDED
#define TypeSerializer_IoT_CAN_CANFrame_INCLUDED


#include "IoT/CAN/CANFrame.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::CAN::CANFrame>
{
public:
	static void serialize(const std::string& name, const IoT::CAN::CANFrame& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::CAN::CANFrame& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"id"s,"flags"s,"dlc"s,"payload"s,""s};
		TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[0], value.id(), ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[1], value.flags(), ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[2], value.dlc(), ser);
		TypeSerializer<Poco::Array < char, 8 > >::serialize(REMOTING__NAMES[3], value.payload(), ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_CAN_CANFrame_INCLUDED

