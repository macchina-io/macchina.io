//
// SensorReadSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_XBee_SensorRead_INCLUDED
#define TypeSerializer_IoT_XBee_SensorRead_INCLUDED


#include "IoT/XBee/XBeeNode.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::XBee::SensorRead>
{
public:
	static void serialize(const std::string& name, const IoT::XBee::SensorRead& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::XBee::SensorRead& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"analogSamples","deviceAddress","networkAddress","options","sensor","temperature",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<std::vector < Poco::Int16 > >::serialize(REMOTING__NAMES[0], value.analogSamples, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.deviceAddress, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], value.networkAddress, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[3], value.options, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[4], value.sensor, ser);
		TypeSerializer<Poco::Int16 >::serialize(REMOTING__NAMES[5], value.temperature, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_XBee_SensorRead_INCLUDED

