//
// SensorReadDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeDeserializer_IoT_XBee_SensorRead_INCLUDED
#define TypeDeserializer_IoT_XBee_SensorRead_INCLUDED


#include "IoT/XBee/XBeeNode.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::XBee::SensorRead>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::XBee::SensorRead& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::XBee::SensorRead& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"analogSamples","deviceAddress","networkAddress","options","sensor","temperature"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<std::vector < Poco::Int16 > >::deserialize(REMOTING__NAMES[0], true, deser, value.analogSamples);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, deser, value.deviceAddress);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, deser, value.networkAddress);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[3], true, deser, value.options);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[4], true, deser, value.sensor);
		TypeDeserializer<Poco::Int16 >::deserialize(REMOTING__NAMES[5], true, deser, value.temperature);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_XBee_SensorRead_INCLUDED

