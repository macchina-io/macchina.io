//
// PositionUpdateDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_Devices_PositionUpdate_INCLUDED
#define TypeDeserializer_IoT_Devices_PositionUpdate_INCLUDED


#include "IoT/Devices/GNSSSensor.h"
#include "IoT/Devices/LatLonDeserializer.h"
#include "IoT/Devices/LatLonSerializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Devices::PositionUpdate>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Devices::PositionUpdate& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::Devices::PositionUpdate& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"position"s,"course"s,"speed"s,"magneticVariation"s,"timestamp"s};
		TypeDeserializer<IoT::Devices::LatLon>::deserialize(REMOTING__NAMES[0], true, deser, value.position);
		TypeDeserializer<double>::deserialize(REMOTING__NAMES[1], true, deser, value.course);
		TypeDeserializer<double>::deserialize(REMOTING__NAMES[2], true, deser, value.speed);
		TypeDeserializer<double>::deserialize(REMOTING__NAMES[3], true, deser, value.magneticVariation);
		TypeDeserializer<Poco::Timestamp>::deserialize(REMOTING__NAMES[4], true, deser, value.timestamp);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Devices_PositionUpdate_INCLUDED

