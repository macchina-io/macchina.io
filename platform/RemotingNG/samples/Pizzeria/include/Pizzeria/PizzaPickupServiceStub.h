//
// PizzaPickupServiceStub.h
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


#ifndef PizzaPickupServiceStub_INCLUDED
#define PizzaPickupServiceStub_INCLUDED


#include "Pizzeria/PizzaPickupServiceRemoteObject.h"
#include "Poco/SharedPtr.h"


namespace Pizzeria {


class PizzaPickupServiceStub: public Pizzeria::PizzaPickupServiceRemoteObject
	/// Pizzeria that allows self pickup.
{
public:
	typedef Poco::AutoPtr<PizzaPickupServiceStub> Ptr;

	PizzaPickupServiceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<Pizzeria::PizzaPickupService> pServiceObject);
		/// Creates a PizzaPickupServiceStub.

	virtual ~PizzaPickupServiceStub();
		/// Destroys the PizzaPickupServiceStub.

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

	Poco::DateTime orderForSelfPickup(const Pizzeria::Pizza& pizza, const std::string& phoneNumber);
		/// Order a pizza, send it to the given deliveryAddress.
		/// Returns the expected time when the Pizza will arrive.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	Poco::SharedPtr<Pizzeria::PizzaPickupService> _pServiceObject;
};


inline const Pizzeria::Pizza& PizzaPickupServiceStub::getAnyPizza() const
{
	return _pServiceObject->getAnyPizza();
}


inline const Pizzeria::ExtTopping& PizzaPickupServiceStub::getMostPopularTopping() const
{
	return _pServiceObject->getMostPopularTopping();
}


inline const std::set < std::string >& PizzaPickupServiceStub::getPizzaNames() const
{
	return _pServiceObject->getPizzaNames();
}


inline const std::vector < Pizzeria::Pizza >& PizzaPickupServiceStub::getPizzas() const
{
	return _pServiceObject->getPizzas();
}


inline const std::vector < Pizzeria::ExtTopping >& PizzaPickupServiceStub::getToppings() const
{
	return _pServiceObject->getToppings();
}


inline Poco::Timespan PizzaPickupServiceStub::getWaitTime() const
{
	return _pServiceObject->getWaitTime();
}


inline Poco::DateTime PizzaPickupServiceStub::order(const Pizzeria::Pizza& pizza, const Pizzeria::DeliveryAddress& deliverTo)
{
	Poco::FastMutex::ScopedLock lock(remoting__mutex());
	return _pServiceObject->order(pizza, deliverTo);
}


inline Poco::DateTime PizzaPickupServiceStub::orderForSelfPickup(const Pizzeria::Pizza& pizza, const std::string& phoneNumber)
{
	Poco::FastMutex::ScopedLock lock(remoting__mutex());
	return _pServiceObject->orderForSelfPickup(pizza, phoneNumber);
}


inline const Poco::RemotingNG::Identifiable::TypeId& PizzaPickupServiceStub::remoting__typeId() const
{
	return IPizzaPickupService::remoting__typeId();
}


} // namespace Pizzeria


#endif // PizzaPickupServiceStub_INCLUDED

