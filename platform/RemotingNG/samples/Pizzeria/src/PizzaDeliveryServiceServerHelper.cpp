//
// PizzaDeliveryServiceServerHelper.cpp
//
// Package: Generated
// Module:  PizzaDeliveryServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2015, Applied Informatics Software Engineering GmbH.
//


#include "Pizzeria/PizzaDeliveryServiceServerHelper.h"
#include "Pizzeria/PizzaDeliveryServiceSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace Pizzeria {


namespace
{
	static Poco::SingletonHolder<PizzaDeliveryServiceServerHelper> shPizzaDeliveryServiceServerHelper;
}


PizzaDeliveryServiceServerHelper::PizzaDeliveryServiceServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerSkeleton("PizzaDeliveryService", new PizzaDeliveryServiceSkeleton);
}


PizzaDeliveryServiceServerHelper::~PizzaDeliveryServiceServerHelper()
{
	try
	{
		_pORB->unregisterSkeleton("PizzaDeliveryService", true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string PizzaDeliveryServiceServerHelper::registerRemoteObject(Poco::AutoPtr<Pizzeria::PizzaDeliveryServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return PizzaDeliveryServiceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


Poco::AutoPtr<Pizzeria::PizzaDeliveryServiceRemoteObject> PizzaDeliveryServiceServerHelper::createRemoteObjectImpl(Poco::SharedPtr<Pizzeria::PizzaDeliveryService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new PizzaDeliveryServiceRemoteObject(oid, pServiceObject);
}


PizzaDeliveryServiceServerHelper& PizzaDeliveryServiceServerHelper::instance()
{
	return *shPizzaDeliveryServiceServerHelper.get();
}


std::string PizzaDeliveryServiceServerHelper::registerObjectImpl(Poco::AutoPtr<Pizzeria::PizzaDeliveryServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void PizzaDeliveryServiceServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


} // namespace Pizzeria

