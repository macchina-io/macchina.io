//
// KeyValueSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_Settings_KeyValue_INCLUDED
#define TypeSerializer_IoT_Settings_KeyValue_INCLUDED


#include "IoT/Settings/SettingsService.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Settings::KeyValue>
{
public:
	static void serialize(const std::string& name, const IoT::Settings::KeyValue& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Settings::KeyValue& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"key"s,"value"s,""s};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.key, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.value, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Settings_KeyValue_INCLUDED

