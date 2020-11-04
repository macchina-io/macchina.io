//
// CharacteristicDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_BtLE_Characteristic_INCLUDED
#define TypeDeserializer_IoT_BtLE_Characteristic_INCLUDED


#include "IoT/BtLE/Peripheral.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::BtLE::Characteristic>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::BtLE::Characteristic& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::BtLE::Characteristic& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"properties"s,"valueHandle"s};
		TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[0], true, deser, value.properties);
		TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[1], true, deser, value.valueHandle);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_BtLE_Characteristic_INCLUDED

