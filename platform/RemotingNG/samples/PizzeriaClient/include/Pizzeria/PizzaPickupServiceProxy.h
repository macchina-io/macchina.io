//
// PizzaPickupServiceProxy.h
//
// Package: Generated
// Module:  PizzaPickupServiceProxy
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef PizzaPickupServiceProxy_INCLUDED
#define PizzaPickupServiceProxy_INCLUDED


#include "Pizzeria/PizzaPickupServiceRemoteObject.h"
#include "Poco/ExpirationDecorator.h"
#include "Poco/RemotingNG/Proxy.h"
#include "Poco/UniqueExpireCache.h"


namespace Pizzeria {


class PizzaPickupServiceProxy: public Pizzeria::PizzaPickupServiceRemoteObject, public Poco::RemotingNG::Proxy
	/// Pizzeria that allows self pickup.
{
public:
	typedef Poco::AutoPtr<PizzaPickupServiceProxy> Ptr;

	PizzaPickupServiceProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a PizzaPickupServiceProxy.

	virtual ~PizzaPickupServiceProxy();
		/// Destroys the PizzaPickupServiceProxy.

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

private:
	static const std::string DEFAULT_NS;
	mutable Poco::UniqueExpireCache<std::string, Poco::ExpirationDecorator<int> > _cache;
	mutable Pizzeria::Pizza _getAnyPizzaRet;
	mutable Pizzeria::ExtTopping _getMostPopularToppingRet;
	mutable std::set < std::string > _getPizzaNamesRet;
	mutable std::vector < Pizzeria::Pizza > _getPizzasRet;
	mutable bool _getToppingsResultIsSet;
	mutable std::vector < Pizzeria::ExtTopping > _getToppingsRet;
	mutable Poco::Timespan _getWaitTimeRet;
	mutable Poco::DateTime _orderForSelfPickupRet;
	mutable Poco::DateTime _orderRet;
};


} // namespace Pizzeria


#endif // PizzaPickupServiceProxy_INCLUDED

