//
// PizzaDeliveryServiceStub.h
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


#ifndef PizzaDeliveryServiceStub_INCLUDED
#define PizzaDeliveryServiceStub_INCLUDED


#include "Pizzeria/PizzaDeliveryServiceRemoteObject.h"
#include "Poco/SharedPtr.h"


namespace Pizzeria {


class PizzaDeliveryServiceStub: public Pizzeria::PizzaDeliveryServiceRemoteObject
{
public:
	typedef Poco::AutoPtr<PizzaDeliveryServiceStub> Ptr;

	PizzaDeliveryServiceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<Pizzeria::PizzaDeliveryService> pServiceObject);
		/// Creates a PizzaDeliveryServiceStub.

	virtual ~PizzaDeliveryServiceStub();
		/// Destroys the PizzaDeliveryServiceStub.

	const Pizzeria::Pizza& getAnyPizza() const;

	const Pizzeria::ExtTopping& getMostPopularTopping() const;

	const std::set < std::string >& getPizzaNames() const;

	const std::vector < Pizzeria::Pizza >& getPizzas() const;
		/// Returns the different types of pizza which we offer.

	const std::vector < Pizzeria::ExtTopping >& getToppings() const;

	Poco::Timespan getWaitTime() const;
		/// Returns the approximate wait time.

	virtual Poco::DateTime order(const Pizzeria::Pizza& pizza, const Pizzeria::DeliveryAddress& deliverTo);
		/// Order a pizza, send it to the given deliveryAddress.
		/// Returns the expected time when the Pizza will arrive.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	Poco::SharedPtr<Pizzeria::PizzaDeliveryService> _pServiceObject;
};


inline const Pizzeria::Pizza& PizzaDeliveryServiceStub::getAnyPizza() const
{
	return _pServiceObject->getAnyPizza();
}


inline const Pizzeria::ExtTopping& PizzaDeliveryServiceStub::getMostPopularTopping() const
{
	return _pServiceObject->getMostPopularTopping();
}


inline const std::set < std::string >& PizzaDeliveryServiceStub::getPizzaNames() const
{
	return _pServiceObject->getPizzaNames();
}


inline const std::vector < Pizzeria::Pizza >& PizzaDeliveryServiceStub::getPizzas() const
{
	return _pServiceObject->getPizzas();
}


inline const std::vector < Pizzeria::ExtTopping >& PizzaDeliveryServiceStub::getToppings() const
{
	return _pServiceObject->getToppings();
}


inline Poco::Timespan PizzaDeliveryServiceStub::getWaitTime() const
{
	return _pServiceObject->getWaitTime();
}


inline Poco::DateTime PizzaDeliveryServiceStub::order(const Pizzeria::Pizza& pizza, const Pizzeria::DeliveryAddress& deliverTo)
{
	Poco::FastMutex::ScopedLock lock(remoting__mutex());
	return _pServiceObject->order(pizza, deliverTo);
}


inline const Poco::RemotingNG::Identifiable::TypeId& PizzaDeliveryServiceStub::remoting__typeId() const
{
	return IPizzaDeliveryService::remoting__typeId();
}


} // namespace Pizzeria


#endif // PizzaDeliveryServiceStub_INCLUDED

