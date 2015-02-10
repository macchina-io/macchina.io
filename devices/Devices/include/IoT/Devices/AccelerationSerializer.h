//
// AccelerationSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_Devices_Acceleration_INCLUDED
#define TypeSerializer_IoT_Devices_Acceleration_INCLUDED


#include "IoT/Devices/Accelerometer.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Devices::Acceleration>
{
public:
	static void serialize(const std::string& name, const IoT::Devices::Acceleration& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Devices::Acceleration& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"x","y","z",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<double >::serialize(REMOTING__NAMES[0], value.x, ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[1], value.y, ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[2], value.z, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Devices_Acceleration_INCLUDED

