//
// CharacteristicSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_BtLE_Characteristic_INCLUDED
#define TypeSerializer_IoT_BtLE_Characteristic_INCLUDED


#include "IoT/BtLE/Peripheral.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::BtLE::Characteristic>
{
public:
	static void serialize(const std::string& name, const IoT::BtLE::Characteristic& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::BtLE::Characteristic& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"properties","valueHandle",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[0], value.properties, ser);
		TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[1], value.valueHandle, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_BtLE_Characteristic_INCLUDED

