#
# Makefile
#
# $Id: //poco/1.6/RemotingNG/samples/PizzeriaClient/Makefile#1 $
#
# Makefile for RemotingNG PizzeriaClient sample.
#

include $(POCO_BASE)/build/rules/global

CXXFLAGS += -I../Pizzeria/include

objects = \
	IPizzaDeliveryService \
	IPizzaPickupService \
	PizzaDeliveryServiceClientHelper \
	PizzaDeliveryServiceRemoteObject \
	PizzaDeliveryServiceProxy \
	PizzaDeliveryServiceProxyFactory \
	PizzaPickupServiceClientHelper \
	PizzaPickupServiceRemoteObject \
	PizzaPickupServiceProxy \
	PizzaPickupServiceProxyFactory \
	Pizza \
	Topping \
	DeliveryAddress \
	PizzeriaClient

target         = PizzeriaClient
target_version = 1
target_libs    = PocoRemotingNGTCP PocoRemotingNG PocoUtil PocoNet PocoJSON PocoXML PocoFoundation

include $(POCO_BASE)/build/rules/exec
