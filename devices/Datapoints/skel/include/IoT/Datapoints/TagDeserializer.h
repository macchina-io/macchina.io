//
// TagDeserializer.h
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


#ifndef TypeDeserializer_IoT_Datapoints_Tag_INCLUDED
#define TypeDeserializer_IoT_Datapoints_Tag_INCLUDED


#include "IoT/Datapoints/Types.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Datapoints::Tag>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Datapoints::Tag& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::Datapoints::Tag& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"name"s,"value"s};
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[0], true, deser, value.name);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[1], true, deser, value.value);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Datapoints_Tag_INCLUDED

