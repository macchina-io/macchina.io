//
// DeliveryAddressDetailsSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TypeSerializer_Pizzeria_DeliveryAddress_Details_INCLUDED
#define TypeSerializer_Pizzeria_DeliveryAddress_Details_INCLUDED


#include "Pizzeria/DeliveryAddress.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Pizzeria::DeliveryAddress::Details>
{
public:
	static void serialize(const std::string& name, const Pizzeria::DeliveryAddress::Details& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const Pizzeria::DeliveryAddress::Details& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"milesAway",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<double >::serialize(REMOTING__NAMES[0], value.milesAway, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Pizzeria_DeliveryAddress_Details_INCLUDED

