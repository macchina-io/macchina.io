//
// PizzaDeliveryServiceStub.cpp
//
// Package: Generated
// Module:  PizzaDeliveryServiceStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "Pizzeria/PizzaDeliveryServiceStub.h"


namespace Pizzeria {


PizzaDeliveryServiceStub::PizzaDeliveryServiceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<Pizzeria::PizzaDeliveryService> pServiceObject):
	Pizzeria::PizzaDeliveryServiceRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
}


PizzaDeliveryServiceStub::~PizzaDeliveryServiceStub()
{
	try
	{
	}
	catch (...)
	{
		poco_unexpected();
	}
}


} // namespace Pizzeria

