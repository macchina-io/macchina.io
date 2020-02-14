//
// PizzaDetailsSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeSerializer_Pizzeria_Pizza_Details_INCLUDED
#define TypeSerializer_Pizzeria_Pizza_Details_INCLUDED


#include "Pizzeria/Pizza.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Pizzeria::Pizza::Details>
{
public:
	static void serialize(const std::string& name, const Pizzeria::Pizza::Details& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const Pizzeria::Pizza::Details& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"calories","carboHydrates","percentFat",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<double >::serialize(REMOTING__NAMES[0], value.calories, ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[1], value.carboHydrates, ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[2], value.percentFat, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Pizzeria_Pizza_Details_INCLUDED

