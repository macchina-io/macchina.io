//
// RotationSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_Devices_Rotation_INCLUDED
#define TypeSerializer_IoT_Devices_Rotation_INCLUDED


#include "IoT/Devices/Gyroscope.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Devices::Rotation>
{
public:
	static void serialize(const std::string& name, const IoT::Devices::Rotation& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Devices::Rotation& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"x"s,"y"s,"z"s,""s};
		TypeSerializer<double >::serialize(REMOTING__NAMES[0], value.x, ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[1], value.y, ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[2], value.z, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Devices_Rotation_INCLUDED

