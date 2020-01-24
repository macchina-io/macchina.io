//
// DeviceStatusChangeSerializer.h
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


#ifndef TypeSerializer_IoT_Devices_DeviceStatusChange_INCLUDED
#define TypeSerializer_IoT_Devices_DeviceStatusChange_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Devices::DeviceStatusChange>
{
public:
	static void serialize(const std::string& name, const IoT::Devices::DeviceStatusChange& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Devices::DeviceStatusChange& value, Serializer& ser)
	{
		static const std::string REMOTING__NAMES[] = {"current","previous",""};
		TypeSerializer<int >::serialize(REMOTING__NAMES[0], value.current, ser);
		TypeSerializer<int >::serialize(REMOTING__NAMES[1], value.previous, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Devices_DeviceStatusChange_INCLUDED

