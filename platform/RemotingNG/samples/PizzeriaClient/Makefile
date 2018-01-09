#
# Makefile
#
# Makefile for RemotingNG PizzeriaClient sample.
#

include $(POCO_BASE)/build/rules/global

CXXFLAGS += -I../Pizzeria/include

objects = \
	IPizzaDeliveryService \
	IPizzaPickupService \
	PizzaDeliveryServiceClientHelper \
	PizzaDeliveryServiceProxy \
	PizzaDeliveryServiceProxyFactory \
	PizzaPickupServiceClientHelper \
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
