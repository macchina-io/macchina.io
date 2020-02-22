//
// ImageDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeDeserializer_IoT_Devices_Image_INCLUDED
#define TypeDeserializer_IoT_Devices_Image_INCLUDED


#include "IoT/Devices/Camera.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Devices::Image>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Devices::Image& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::Devices::Image& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"encoding"s,"height"s,"image"s,"step"s,"width"s};
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[0], true, deser, value.encoding);
		TypeDeserializer<int >::deserialize(REMOTING__NAMES[1], true, deser, value.height);
		TypeDeserializer<Poco::SharedPtr < std::vector < char > > >::deserialize(REMOTING__NAMES[2], true, deser, value.image);
		TypeDeserializer<int >::deserialize(REMOTING__NAMES[3], true, deser, value.step);
		TypeDeserializer<int >::deserialize(REMOTING__NAMES[4], true, deser, value.width);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Devices_Image_INCLUDED

