#
# Makefile
#
# Makefile for Poco JS Bridge library
#

include $(POCO_BASE)/build/rules/global

objects = Serializer Deserializer Listener \
	TaggedBinarySerializer TaggedBinaryReader \
	BridgeWrapper

target         = PocoJSBridge
target_version = 1
target_libs    = PocoJSCore PocoRemotingNG PocoUtil PocoXML PocoFoundation v8

include $(POCO_BASE)/build/rules/lib
