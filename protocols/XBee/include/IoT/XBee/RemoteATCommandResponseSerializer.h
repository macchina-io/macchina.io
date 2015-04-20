//
// RemoteATCommandResponseSerializer.h
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


#ifndef TypeSerializer_IoT_XBee_RemoteATCommandResponse_INCLUDED
#define TypeSerializer_IoT_XBee_RemoteATCommandResponse_INCLUDED


#include "IoT/XBee/XBeeNode.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::XBee::RemoteATCommandResponse>
{
public:
	static void serialize(const std::string& name, const IoT::XBee::RemoteATCommandResponse& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::XBee::RemoteATCommandResponse& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"command","data","deviceAddress","frameID","networkAddress","status",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.command, ser);
		TypeSerializer<std::vector < Poco::UInt8 > >::serialize(REMOTING__NAMES[1], value.data, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], value.deviceAddress, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[3], value.frameID, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[4], value.networkAddress, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[5], value.status, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_XBee_RemoteATCommandResponse_INCLUDED

