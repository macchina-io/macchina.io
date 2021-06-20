//
// PropertyDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_MQTT_Property_INCLUDED
#define TypeDeserializer_IoT_MQTT_Property_INCLUDED


#include "IoT/MQTT/Types.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::MQTT::Property>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::MQTT::Property& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::MQTT::Property& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"binaryValue"s,"byteValue"s,"identifier"s,"name"s,"stringValue"s,"uint16Value"s,"uint32Value"s};
		bool ret = false;
		TypeDeserializer<Poco::Optional < std::vector < char > > >::deserialize(REMOTING__NAMES[0], true, deser, value.binaryValue);
		TypeDeserializer<Poco::Optional < Poco::UInt8 > >::deserialize(REMOTING__NAMES[1], true, deser, value.byteValue);
		int genidentifier;
		ret = TypeDeserializer<int >::deserialize(REMOTING__NAMES[2], false, deser, genidentifier);
		if (ret) value.identifier = static_cast<IoT::MQTT::PropertyID>(genidentifier);
		TypeDeserializer<Poco::Optional < std::string > >::deserialize(REMOTING__NAMES[3], true, deser, value.name);
		TypeDeserializer<Poco::Optional < std::string > >::deserialize(REMOTING__NAMES[4], true, deser, value.stringValue);
		TypeDeserializer<Poco::Optional < Poco::UInt16 > >::deserialize(REMOTING__NAMES[5], true, deser, value.uint16Value);
		TypeDeserializer<Poco::Optional < Poco::UInt32 > >::deserialize(REMOTING__NAMES[6], true, deser, value.uint32Value);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_MQTT_Property_INCLUDED

