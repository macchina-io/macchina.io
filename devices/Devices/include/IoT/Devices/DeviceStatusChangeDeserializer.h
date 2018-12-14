//
// DeviceStatusChangeDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeDeserializer_IoT_Devices_DeviceStatusChange_INCLUDED
#define TypeDeserializer_IoT_Devices_DeviceStatusChange_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Devices::DeviceStatusChange>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Devices::DeviceStatusChange& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::Devices::DeviceStatusChange& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"current","previous"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool ret = false;
		int gencurrent;
		ret = TypeDeserializer<int >::deserialize(REMOTING__NAMES[0], true, deser, gencurrent);
		if (ret) value.current = static_cast<IoT::Devices::DeviceStatus>(gencurrent);
		int genprevious;
		ret = TypeDeserializer<int >::deserialize(REMOTING__NAMES[1], true, deser, genprevious);
		if (ret) value.previous = static_cast<IoT::Devices::DeviceStatus>(genprevious);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Devices_DeviceStatusChange_INCLUDED

