//
// PositionUpdateSerializer.h
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


#ifndef TypeSerializer_IoT_Devices_PositionUpdate_INCLUDED
#define TypeSerializer_IoT_Devices_PositionUpdate_INCLUDED


#include "IoT/Devices/GNSSSensor.h"
#include "IoT/Devices/LatLonDeserializer.h"
#include "IoT/Devices/LatLonSerializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Devices::PositionUpdate>
{
public:
	static void serialize(const std::string& name, const IoT::Devices::PositionUpdate& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Devices::PositionUpdate& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"course","magneticVariation","position","speed","timestamp",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<double >::serialize(REMOTING__NAMES[0], value.course, ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[1], value.magneticVariation, ser);
		TypeSerializer<IoT::Devices::LatLon >::serialize(REMOTING__NAMES[2], value.position, ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[3], value.speed, ser);
		TypeSerializer<Poco::Timestamp >::serialize(REMOTING__NAMES[4], value.timestamp, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Devices_PositionUpdate_INCLUDED

