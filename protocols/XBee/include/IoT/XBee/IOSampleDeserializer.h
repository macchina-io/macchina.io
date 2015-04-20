//
// IOSampleDeserializer.h
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


#ifndef TypeDeserializer_IoT_XBee_IOSample_INCLUDED
#define TypeDeserializer_IoT_XBee_IOSample_INCLUDED


#include "IoT/XBee/XBeeNode.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::XBee::IOSample>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::XBee::IOSample& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::XBee::IOSample& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"analogChannelMask","analogSamples","deviceAddress","digitalChannelMask","digitalSamples","nSampleSets","networkAddress","options"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[0], true, deser, value.analogChannelMask);
		TypeDeserializer<std::vector < Poco::Int16 > >::deserialize(REMOTING__NAMES[1], true, deser, value.analogSamples);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, deser, value.deviceAddress);
		TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[3], true, deser, value.digitalChannelMask);
		TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[4], true, deser, value.digitalSamples);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[5], true, deser, value.nSampleSets);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[6], true, deser, value.networkAddress);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[7], true, deser, value.options);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_XBee_IOSample_INCLUDED

