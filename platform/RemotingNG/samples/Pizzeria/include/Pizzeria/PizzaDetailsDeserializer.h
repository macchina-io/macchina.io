//
// PizzaDetailsDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeDeserializer_Pizzeria_Pizza_Details_INCLUDED
#define TypeDeserializer_Pizzeria_Pizza_Details_INCLUDED


#include "Pizzeria/Pizza.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<Pizzeria::Pizza::Details>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, Pizzeria::Pizza::Details& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, Pizzeria::Pizza::Details& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"calories","carboHydrates","percentFat"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<double >::deserialize(REMOTING__NAMES[0], true, deser, value.calories);
		TypeDeserializer<double >::deserialize(REMOTING__NAMES[1], true, deser, value.carboHydrates);
		TypeDeserializer<double >::deserialize(REMOTING__NAMES[2], true, deser, value.percentFat);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_Pizzeria_Pizza_Details_INCLUDED

