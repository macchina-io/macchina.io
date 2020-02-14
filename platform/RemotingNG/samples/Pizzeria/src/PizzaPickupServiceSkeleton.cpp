//
// PizzaPickupServiceSkeleton.cpp
//
// Package: Generated
// Module:  PizzaPickupServiceSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#include "Pizzeria/PizzaPickupServiceSkeleton.h"
#include "Pizzeria/DeliveryAddressDeserializer.h"
#include "Pizzeria/DeliveryAddressSerializer.h"
#include "Pizzeria/PizzaDeserializer.h"
#include "Pizzeria/PizzaSerializer.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/MethodHandler.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/SharedPtr.h"


namespace Pizzeria {


class PizzaPickupServiceGetAnyPizzaMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"getAnyPizza"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			Pizzeria::PizzaPickupServiceRemoteObject* remoting__pCastedRO = static_cast<Pizzeria::PizzaPickupServiceRemoteObject*>(remoting__pRemoteObject.get());
			Pizzeria::Pizza remoting__return = remoting__pCastedRO->getAnyPizza();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("getAnyPizzaReply");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Pizzeria::Pizza >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class PizzaPickupServiceGetMostPopularToppingMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"getMostPopularTopping"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			Pizzeria::PizzaPickupServiceRemoteObject* remoting__pCastedRO = static_cast<Pizzeria::PizzaPickupServiceRemoteObject*>(remoting__pRemoteObject.get());
			Pizzeria::ExtTopping remoting__return = remoting__pCastedRO->getMostPopularTopping();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("getMostPopularToppingReply");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Pizzeria::ExtTopping >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class PizzaPickupServiceGetPizzaNamesMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"getPizzaNames"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			Pizzeria::PizzaPickupServiceRemoteObject* remoting__pCastedRO = static_cast<Pizzeria::PizzaPickupServiceRemoteObject*>(remoting__pRemoteObject.get());
			std::set < std::string > remoting__return = remoting__pCastedRO->getPizzaNames();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("getPizzaNamesReply");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::set < std::string > >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class PizzaPickupServiceGetPizzasMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"getPizzas"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			Pizzeria::PizzaPickupServiceRemoteObject* remoting__pCastedRO = static_cast<Pizzeria::PizzaPickupServiceRemoteObject*>(remoting__pRemoteObject.get());
			std::vector < Pizzeria::Pizza > remoting__return = remoting__pCastedRO->getPizzas();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("getPizzasReply");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::vector < Pizzeria::Pizza > >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class PizzaPickupServiceGetToppingsMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"getToppings"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			Pizzeria::PizzaPickupServiceRemoteObject* remoting__pCastedRO = static_cast<Pizzeria::PizzaPickupServiceRemoteObject*>(remoting__pRemoteObject.get());
			std::vector < Pizzeria::ExtTopping > remoting__return = remoting__pCastedRO->getToppings();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("getToppingsReply");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::vector < Pizzeria::ExtTopping > >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class PizzaPickupServiceGetWaitTimeMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"getWaitTime"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			Pizzeria::PizzaPickupServiceRemoteObject* remoting__pCastedRO = static_cast<Pizzeria::PizzaPickupServiceRemoteObject*>(remoting__pRemoteObject.get());
			Poco::Timespan remoting__return = remoting__pCastedRO->getWaitTime();
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("getWaitTimeReply");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::Timespan >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class PizzaPickupServiceSetWaitTimeMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"setWaitTime","span"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::Timespan span;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<Poco::Timespan >::deserialize(REMOTING__NAMES[1], true, remoting__deser, span);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			Pizzeria::PizzaPickupServiceRemoteObject* remoting__pCastedRO = static_cast<Pizzeria::PizzaPickupServiceRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setWaitTime(span);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("setWaitTimeReply");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class PizzaPickupServiceOrderForSelfPickupMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"orderForSelfPickup","phoneNumber","pizza"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Pizzeria::Pizza pizza;
			std::string phoneNumber;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, phoneNumber);
			Poco::RemotingNG::TypeDeserializer<Pizzeria::Pizza >::deserialize(REMOTING__NAMES[2], true, remoting__deser, pizza);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			Pizzeria::PizzaPickupServiceRemoteObject* remoting__pCastedRO = static_cast<Pizzeria::PizzaPickupServiceRemoteObject*>(remoting__pRemoteObject.get());
			Poco::DateTime remoting__return = remoting__pCastedRO->orderForSelfPickup(pizza, phoneNumber);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, PizzaPickupServiceSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("orderForSelfPickupReply");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::DateTime >::serialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, remoting__return, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


PizzaPickupServiceSkeleton::PizzaPickupServiceSkeleton():
	Poco::RemotingNG::Skeleton()

{
	addMethodHandler("getAnyPizza", new Pizzeria::PizzaPickupServiceGetAnyPizzaMethodHandler);
	addMethodHandler("getMostPopularTopping", new Pizzeria::PizzaPickupServiceGetMostPopularToppingMethodHandler);
	addMethodHandler("getPizzaNames", new Pizzeria::PizzaPickupServiceGetPizzaNamesMethodHandler);
	addMethodHandler("getPizzas", new Pizzeria::PizzaPickupServiceGetPizzasMethodHandler);
	addMethodHandler("getToppings", new Pizzeria::PizzaPickupServiceGetToppingsMethodHandler);
	addMethodHandler("getWaitTime", new Pizzeria::PizzaPickupServiceGetWaitTimeMethodHandler);
	addMethodHandler("orderForSelfPickup", new Pizzeria::PizzaPickupServiceOrderForSelfPickupMethodHandler);
	addMethodHandler("setWaitTime", new Pizzeria::PizzaPickupServiceSetWaitTimeMethodHandler);
}


PizzaPickupServiceSkeleton::~PizzaPickupServiceSkeleton()
{
}


const std::string PizzaPickupServiceSkeleton::DEFAULT_NS("http://www.appinf.com/webservices/PizzaDeliveryService/");
} // namespace Pizzeria

