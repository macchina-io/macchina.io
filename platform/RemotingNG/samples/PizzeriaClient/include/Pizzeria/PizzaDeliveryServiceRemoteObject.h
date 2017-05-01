//
// PizzaDeliveryServiceRemoteObject.h
//
// Package: Generated
// Module:  PizzaDeliveryServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef PizzaDeliveryServiceRemoteObject_INCLUDED
#define PizzaDeliveryServiceRemoteObject_INCLUDED


#include "Pizzeria/IPizzaDeliveryService.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace Pizzeria {


class PizzaDeliveryServiceRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public Pizzeria::IPizzaDeliveryService
{
public:
	typedef Poco::AutoPtr<PizzaDeliveryServiceRemoteObject> Ptr;

	PizzaDeliveryServiceRemoteObject();
		/// Creates a PizzaDeliveryServiceRemoteObject.

	virtual ~PizzaDeliveryServiceRemoteObject();
		/// Destroys the PizzaDeliveryServiceRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& PizzaDeliveryServiceRemoteObject::remoting__typeId() const
{
	return IPizzaDeliveryService::remoting__typeId();
}


} // namespace Pizzeria


#endif // PizzaDeliveryServiceRemoteObject_INCLUDED

