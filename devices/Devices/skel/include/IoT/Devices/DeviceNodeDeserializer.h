//
// DeviceNodeDeserializer.h
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


#ifndef TypeDeserializer_IoT_Devices_DeviceNode_INCLUDED
#define TypeDeserializer_IoT_Devices_DeviceNode_INCLUDED


#include "IoT/Devices/DeviceTree.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Devices::DeviceNode>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Devices::DeviceNode& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::Devices::DeviceNode& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"composite"s,"fragments"s,"id"s,"name"s,"type"s};
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[0], true, deser, value.composite);
		TypeDeserializer<Poco::Optional < std::vector < std::string > > >::deserialize(REMOTING__NAMES[1], true, deser, value.fragments);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, deser, value.id);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, deser, value.name);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[4], true, deser, value.type);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Devices_DeviceNode_INCLUDED

