//
// IPizzaDeliveryService.cpp
//
// Package: Generated
// Module:  IPizzaDeliveryService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2015, Applied Informatics Software Engineering GmbH.
//


#include "Pizzeria/IPizzaDeliveryService.h"


namespace Pizzeria {


IPizzaDeliveryService::IPizzaDeliveryService():
	Poco::RefCountedObject()

{
}


IPizzaDeliveryService::~IPizzaDeliveryService()
{
}


const Poco::RemotingNG::Identifiable::TypeId& IPizzaDeliveryService::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("PizzaDeliveryService");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace Pizzeria

