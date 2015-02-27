#
# Makefile
#
# $Id$
#
# Makefile for Paho MQTT Client
#

include $(POCO_BASE)/build/rules/global

SYSLIBS += -lssl -lcrypto

ifeq ($(OSNAME),Darwin)
CFLAGS += -DUSE_NAMED_SEMAPHORES
endif

CFLAGS += -DOPENSSL

objects = \
	Clients \
	Heap \
	LinkedList \
	Log \
	MQTTClient \
	MQTTPacket \
	MQTTPacketOut \
	MQTTPersistence \
	MQTTPersistenceDefault \
	MQTTProtocolClient \
	MQTTProtocolOut \
	MQTTVersion \
	Messages \
	SSLSocket \
	Socket \
	SocketBuffer \
	StackTrace \
	Thread \
	Tree \
	utf-8

target         = PahoMQTT
target_version = 1
target_libs    = 

include $(POCO_BASE)/build/rules/lib
