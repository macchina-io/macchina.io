//
// PizzeriaClient.cpp
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//
// Note: The code for invoking the PizzaDeliveryService has been directly
// generated from the PizzaDeliveryService class, using the RemoteGenNG
// tool.
//


#include "Pizzeria/PizzaDeliveryServiceClientHelper.h"
#include "Pizzeria/DeliveryAddress.h"
#include "Pizzeria/Topping.h"
#include "Pizzeria/Pizza.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/RemotingNG/TCP/TransportFactory.h"
#include <iostream>


int main(int argc, char** argv)
{
	try
	{
		// register transport
		Poco::RemotingNG::TCP::TransportFactory::registerFactory();

		// get proxy for remote object
		Pizzeria::IPizzaDeliveryService::Ptr pPizzeria = Pizzeria::PizzaDeliveryServiceClientHelper::find("remoting.tcp://127.0.0.1:8123/tcp/Pizzeria.PizzaDeliveryService/ThePizzeria");

		// invoke methods on remote object

		std::cout << "Toppings: " << std::endl;
		std::vector<Pizzeria::ExtTopping> toppings = pPizzeria->getToppings();
		for (std::vector<Pizzeria::ExtTopping>::const_iterator it = toppings.begin(); it != toppings.end(); ++it)
		{
			std::cout << it->getName() << std::endl;
		}

		std::cout << std::endl;
		std::cout << "Pizzas: " << std::endl;
		std::set<std::string> names = pPizzeria->getPizzaNames();
		for (std::set<std::string>::const_iterator it = names.begin(); it != names.end(); ++it)
		{
			std::cout << *it << std::endl;
		}

		std::vector<Pizzeria::Pizza> pizzas = pPizzeria->getPizzas();

		Pizzeria::DeliveryAddress addr;
		addr.setPersonName("Jane Doe");
		addr.setStreet("Walnut Street");
		addr.setHouseNumber(4231);
		addr.setCityName("Springfield");
		addr.setZip("76543");
		addr.setState("NT");
		addr.setPhoneNumber("(939) 123 4567");

		Poco::DateTime deliveryTime = pPizzeria->order(pizzas[2], addr);
		std::cout << std::endl << "Delivery Time: " << Poco::DateTimeFormatter::format(deliveryTime, Poco::DateTimeFormat::SORTABLE_FORMAT) << std::endl;
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
		return 1;
	}
	return 0;
}
