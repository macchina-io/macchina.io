#
# Makefile
#
# Makefile for Paho MQTT Client
#

include $(POCO_BASE)/build/rules/global

SYSLIBS += -lssl -lcrypto

ifeq ($(OSNAME),Darwin)
CFLAGS += -DOSX -Wno-deprecated-declarations
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
	utf-8 \
	Base64 \
	MQTTProperties \
	MQTTReasonCodes \
	OsWrapper \
	SHA1 \
	WebSocket

target         = PahoMQTT
target_version = 1
target_libs    =

include $(POCO_BASE)/build/rules/lib
