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
	Base64 \
	Clients \
	Heap \
	LinkedList \
	Log \
	Messages \
	MQTTClient \
	MQTTPacket \
	MQTTPacketOut \
	MQTTPersistence \
	MQTTPersistenceDefault \
	MQTTProperties \
	MQTTProtocolClient \
	MQTTProtocolOut \
	MQTTReasonCodes \
	MQTTTime \
	MQTTVersion \
	OsWrapper \
	SHA1 \
	Socket \
	SocketBuffer \
	SSLSocket \
	StackTrace \
	Thread \
	Tree \
	utf-8 \
	WebSocket

target         = PahoMQTT
target_version = 1
target_libs    =

include $(POCO_BASE)/build/rules/lib
