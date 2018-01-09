#
# Makefile
#
# Makefile for Poco JS Bridge library
#

include $(POCO_BASE)/build/rules/global

CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = Serializer Deserializer Listener \
	TaggedBinarySerializer TaggedBinaryReader \
	BridgeWrapper

target         = PocoJSBridge
target_version = 1
target_libs    = PocoJSCore PocoRemotingNG PocoUtil PocoXML PocoFoundation
ext_libs       = v8 v8_libplatform v8_libbase

include $(POCO_BASE)/build/rules/lib
