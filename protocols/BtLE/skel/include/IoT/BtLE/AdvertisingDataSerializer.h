//
// AdvertisingDataSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_BtLE_AdvertisingData_INCLUDED
#define TypeSerializer_IoT_BtLE_AdvertisingData_INCLUDED


#include "IoT/BtLE/PeripheralBrowser.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::BtLE::AdvertisingData>
{
public:
	static void serialize(const std::string& name, const IoT::BtLE::AdvertisingData& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::BtLE::AdvertisingData& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"type"s,"data"s,""s};
		TypeSerializer<Poco::UInt8>::serialize(REMOTING__NAMES[0], value.type, ser);
		TypeSerializer<std::vector<char>>::serialize(REMOTING__NAMES[1], value.data, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_BtLE_AdvertisingData_INCLUDED

