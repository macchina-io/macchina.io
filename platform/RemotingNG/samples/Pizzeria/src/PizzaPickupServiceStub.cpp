//
// PizzaPickupServiceStub.cpp
//
// Package: Generated
// Module:  PizzaPickupServiceStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "Pizzeria/PizzaPickupServiceStub.h"


namespace Pizzeria {


PizzaPickupServiceStub::PizzaPickupServiceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<Pizzeria::PizzaPickupService> pServiceObject):
	Pizzeria::PizzaPickupServiceRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
}


PizzaPickupServiceStub::~PizzaPickupServiceStub()
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

