//
// BasicDatapointParamsDeserializer.h
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


#ifndef TypeDeserializer_IoT_Datapoints_BasicDatapointParams_INCLUDED
#define TypeDeserializer_IoT_Datapoints_BasicDatapointParams_INCLUDED


#include "IoT/Datapoints/TagDeserializer.h"
#include "IoT/Datapoints/TagSerializer.h"
#include "IoT/Datapoints/Types.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Datapoints::BasicDatapointParams>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Datapoints::BasicDatapointParams& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::Datapoints::BasicDatapointParams& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"access"s,"composite"s,"customData"s,"name"s,"tags"s};
		TypeDeserializer<int >::deserialize(REMOTING__NAMES[0], false, deser, value.access);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], false, deser, value.composite);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], false, deser, value.customData);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, deser, value.name);
		TypeDeserializer<std::vector < IoT::Datapoints::Tag > >::deserialize(REMOTING__NAMES[4], false, deser, value.tags);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Datapoints_BasicDatapointParams_INCLUDED

