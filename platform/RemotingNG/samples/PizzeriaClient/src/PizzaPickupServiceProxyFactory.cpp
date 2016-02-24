//
// PizzaPickupServiceProxyFactory.cpp
//
// Package: Generated
// Module:  PizzaPickupServiceProxyFactory
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "Pizzeria/PizzaPickupServiceProxyFactory.h"


namespace Pizzeria {


PizzaPickupServiceProxyFactory::PizzaPickupServiceProxyFactory():
	Poco::RemotingNG::ProxyFactory()

{
}


PizzaPickupServiceProxyFactory::~PizzaPickupServiceProxyFactory()
{
}


Poco::RemotingNG::Proxy* PizzaPickupServiceProxyFactory::createProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid) const
{
	return new Pizzeria::PizzaPickupServiceProxy(oid);
}


} // namespace Pizzeria

