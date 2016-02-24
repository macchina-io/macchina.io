#
# Makefile
#
# $Id: //poco/1.6/RemotingNG/samples/Pizzeria/Makefile#1 $
#
# Makefile for RemotingNG Pizzeria sample.
#

include $(POCO_BASE)/build/rules/global

objects = DeliveryAddress IPizzaDeliveryService Pizza PizzaDeliveryService PizzaDeliveryServiceRemoteObject \
	PizzaDeliveryServiceServerHelper PizzaDeliveryServiceSkeleton Topping \
	PizzaPickupService PizzaPickupServiceServerHelper \
	PizzaPickupServiceRemoteObject PizzaPickupServiceSkeleton \
	IPizzaPickupService \
	PizzeriaServer

target         = Pizzeria
target_version = 1
target_libs    = PocoRemotingNGTCP PocoRemotingNG PocoUtil PocoNet PocoJSON PocoXML PocoFoundation

include $(POCO_BASE)/build/rules/exec
