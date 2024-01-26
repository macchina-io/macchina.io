//
// MovingAverageDatapointParamsSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_Datapoints_MovingAverageDatapointParams_INCLUDED
#define TypeSerializer_IoT_Datapoints_MovingAverageDatapointParams_INCLUDED


#include "IoT/Datapoints/TagDeserializer.h"
#include "IoT/Datapoints/TagSerializer.h"
#include "IoT/Datapoints/Types.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Datapoints::MovingAverageDatapointParams>
{
public:
	static void serialize(const std::string& name, const IoT::Datapoints::MovingAverageDatapointParams& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Datapoints::MovingAverageDatapointParams& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		// IoT::Datapoints::BasicDatapointParams
		{
		static const std::string REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[] = {"access"s,"composite"s,"customData"s,"name"s,"tags"s,""s};
		TypeSerializer<int >::serialize(REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[0], value.access, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[1], value.composite, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[2], value.customData, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[3], value.name, ser);
		TypeSerializer<std::vector < IoT::Datapoints::Tag > >::serialize(REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[4], value.tags, ser);
		}
		
		static const std::string REMOTING__NAMES[] = {"physicalQuantity"s,"physicalUnit"s,"windowSize"s,""s};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.physicalQuantity, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.physicalUnit, ser);
		TypeSerializer<std::size_t >::serialize(REMOTING__NAMES[2], value.windowSize, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Datapoints_MovingAverageDatapointParams_INCLUDED

