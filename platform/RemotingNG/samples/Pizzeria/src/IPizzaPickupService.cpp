//
// IPizzaPickupService.cpp
//
// Package: Generated
// Module:  IPizzaPickupService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2015, Applied Informatics Software Engineering GmbH.
//


#include "Pizzeria/IPizzaPickupService.h"


namespace Pizzeria {


IPizzaPickupService::IPizzaPickupService():
	Pizzeria::IPizzaDeliveryService()

{
}


IPizzaPickupService::~IPizzaPickupService()
{
}


const Poco::RemotingNG::Identifiable::TypeId& IPizzaPickupService::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("PizzaPickupService");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace Pizzeria

