//
// EventNotificationSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_WebEvent_EventNotification_INCLUDED
#define TypeSerializer_IoT_WebEvent_EventNotification_INCLUDED


#include "IoT/WebEvent/WebEventNotifier.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::WebEvent::EventNotification>
{
public:
	static void serialize(const std::string& name, const IoT::WebEvent::EventNotification& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::WebEvent::EventNotification& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"data"s,"subjectName"s,""s};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.data, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.subjectName, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_WebEvent_EventNotification_INCLUDED

