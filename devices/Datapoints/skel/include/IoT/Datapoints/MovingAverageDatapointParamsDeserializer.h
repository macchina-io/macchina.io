//
// MovingAverageDatapointParamsDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_Datapoints_MovingAverageDatapointParams_INCLUDED
#define TypeDeserializer_IoT_Datapoints_MovingAverageDatapointParams_INCLUDED


#include "IoT/Datapoints/TagDeserializer.h"
#include "IoT/Datapoints/TagSerializer.h"
#include "IoT/Datapoints/Types.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Datapoints::MovingAverageDatapointParams>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Datapoints::MovingAverageDatapointParams& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::Datapoints::MovingAverageDatapointParams& value)
	{
		using namespace std::string_literals;
		
		// IoT::Datapoints::BasicDatapointParams
		{
		static const std::string REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[] = {"name"s,"composite"s,"access"s,"tags"s,"customData"s};
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[0], true, deser, value.name);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[1], false, deser, value.composite);
		TypeDeserializer<int>::deserialize(REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[2], false, deser, value.access);
		TypeDeserializer<std::vector<IoT::Datapoints::Tag>>::deserialize(REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[3], false, deser, value.tags);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES__IOT__DATAPOINTS__BASICDATAPOINTPARAMS[4], false, deser, value.customData);
		}
		
		static const std::string REMOTING__NAMES[] = {"physicalQuantity"s,"physicalUnit"s,"windowSize"s};
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[0], false, deser, value.physicalQuantity);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[1], false, deser, value.physicalUnit);
		TypeDeserializer<std::size_t>::deserialize(REMOTING__NAMES[2], false, deser, value.windowSize);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Datapoints_MovingAverageDatapointParams_INCLUDED

