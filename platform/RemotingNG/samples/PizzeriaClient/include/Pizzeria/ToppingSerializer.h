//
// ToppingSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_Pizzeria_Topping_INCLUDED
#define TypeSerializer_Pizzeria_Topping_INCLUDED


#include "Pizzeria/Topping.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Pizzeria::Topping>
{
public:
	static void serialize(const std::string& name, const Pizzeria::Topping& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const Pizzeria::Topping& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"name","price",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.getName(), ser);
		TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[1], value.getPrice(), ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Pizzeria_Topping_INCLUDED

