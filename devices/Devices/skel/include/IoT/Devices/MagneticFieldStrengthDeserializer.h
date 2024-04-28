//
// MagneticFieldStrengthDeserializer.h
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


#ifndef TypeDeserializer_IoT_Devices_MagneticFieldStrength_INCLUDED
#define TypeDeserializer_IoT_Devices_MagneticFieldStrength_INCLUDED


#include "IoT/Devices/Magnetometer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Devices::MagneticFieldStrength>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Devices::MagneticFieldStrength& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::Devices::MagneticFieldStrength& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"x"s,"y"s,"z"s,"r"s};
		TypeDeserializer<double>::deserialize(REMOTING__NAMES[0], true, deser, value.x);
		TypeDeserializer<double>::deserialize(REMOTING__NAMES[1], true, deser, value.y);
		TypeDeserializer<double>::deserialize(REMOTING__NAMES[2], true, deser, value.z);
		TypeDeserializer<double>::deserialize(REMOTING__NAMES[3], true, deser, value.r);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Devices_MagneticFieldStrength_INCLUDED

