//
// FrameSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_CAN_Frame_INCLUDED
#define TypeSerializer_IoT_CAN_Frame_INCLUDED


#include "IoT/CAN/CANEndpoint.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::CAN::Frame>
{
public:
	static void serialize(const std::string& name, const IoT::CAN::Frame& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::CAN::Frame& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"dlc","eff","id","payload","rtr",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[0], value.dlc, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[1], value.eff, ser);
		TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[2], value.id, ser);
		TypeSerializer<Poco::Array < char, 8 > >::serialize(REMOTING__NAMES[3], value.payload, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[4], value.rtr, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_CAN_Frame_INCLUDED

