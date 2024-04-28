//
// BasicDatapointParamsSerializer.h
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


#ifndef TypeSerializer_IoT_Datapoints_BasicDatapointParams_INCLUDED
#define TypeSerializer_IoT_Datapoints_BasicDatapointParams_INCLUDED


#include "IoT/Datapoints/TagDeserializer.h"
#include "IoT/Datapoints/TagSerializer.h"
#include "IoT/Datapoints/Types.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Datapoints::BasicDatapointParams>
{
public:
	static void serialize(const std::string& name, const IoT::Datapoints::BasicDatapointParams& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Datapoints::BasicDatapointParams& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"name"s,"composite"s,"access"s,"tags"s,"customData"s,""s};
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[0], value.name, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[1], value.composite, ser);
		TypeSerializer<int>::serialize(REMOTING__NAMES[2], value.access, ser);
		TypeSerializer<std::vector<IoT::Datapoints::Tag>>::serialize(REMOTING__NAMES[3], value.tags, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[4], value.customData, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Datapoints_BasicDatapointParams_INCLUDED

