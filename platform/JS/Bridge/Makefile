#
# Makefile
#
# Makefile for Poco JS Bridge library
#

include $(POCO_BASE)/build/rules/global

EXTRA_CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = Serializer Deserializer Listener \
	TaggedBinarySerializer TaggedBinaryReader \
	BridgeWrapper

target         = PocoJSBridge
target_version = 1
target_libs    = PocoJSCore PocoRemotingNG PocoUtil PocoXML PocoFoundation
target_extlibs = v8

include $(POCO_BASE)/build/rules/lib
