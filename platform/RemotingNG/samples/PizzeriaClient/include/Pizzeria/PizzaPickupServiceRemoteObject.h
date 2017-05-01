//
// PizzaPickupServiceRemoteObject.h
//
// Package: Generated
// Module:  PizzaPickupServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef PizzaPickupServiceRemoteObject_INCLUDED
#define PizzaPickupServiceRemoteObject_INCLUDED


#include "Pizzeria/IPizzaPickupService.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace Pizzeria {


class PizzaPickupServiceRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public Pizzeria::IPizzaPickupService
	/// Pizzeria that allows self pickup.
{
public:
	typedef Poco::AutoPtr<PizzaPickupServiceRemoteObject> Ptr;

	PizzaPickupServiceRemoteObject();
		/// Creates a PizzaPickupServiceRemoteObject.

	virtual ~PizzaPickupServiceRemoteObject();
		/// Destroys the PizzaPickupServiceRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& PizzaPickupServiceRemoteObject::remoting__typeId() const
{
	return IPizzaPickupService::remoting__typeId();
}


} // namespace Pizzeria


#endif // PizzaPickupServiceRemoteObject_INCLUDED

