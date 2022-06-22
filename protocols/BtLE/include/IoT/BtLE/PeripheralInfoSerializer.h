//
// PeripheralInfoSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_BtLE_PeripheralInfo_INCLUDED
#define TypeSerializer_IoT_BtLE_PeripheralInfo_INCLUDED


#include "IoT/BtLE/PeripheralBrowser.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::BtLE::PeripheralInfo>
{
public:
	static void serialize(const std::string& name, const IoT::BtLE::PeripheralInfo& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::BtLE::PeripheralInfo& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"address"s,"name"s,""s};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.address, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.name, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_BtLE_PeripheralInfo_INCLUDED

