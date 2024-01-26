//
// PeripheralInfoDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_BtLE_PeripheralInfo_INCLUDED
#define TypeDeserializer_IoT_BtLE_PeripheralInfo_INCLUDED


#include "IoT/BtLE/AdvertisingDataDeserializer.h"
#include "IoT/BtLE/AdvertisingDataSerializer.h"
#include "IoT/BtLE/PeripheralBrowser.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::BtLE::PeripheralInfo>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::BtLE::PeripheralInfo& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::BtLE::PeripheralInfo& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"address"s,"addressType"s,"connectable"s,"data"s,"name"s,"rssi"s};
		bool ret = false;
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[0], true, deser, value.address);
		int genaddressType;
		ret = TypeDeserializer<int >::deserialize(REMOTING__NAMES[1], true, deser, genaddressType);
		if (ret) value.addressType = static_cast<IoT::BtLE::AddressType>(genaddressType);
		TypeDeserializer<bool >::deserialize(REMOTING__NAMES[2], true, deser, value.connectable);
		TypeDeserializer<std::vector < IoT::BtLE::AdvertisingData > >::deserialize(REMOTING__NAMES[3], true, deser, value.data);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[4], true, deser, value.name);
		TypeDeserializer<short >::deserialize(REMOTING__NAMES[5], true, deser, value.rssi);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_BtLE_PeripheralInfo_INCLUDED

