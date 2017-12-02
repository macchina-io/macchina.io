#
# Makefile
#
# Makefile for Poco JS Net library
#

include $(POCO_BASE)/build/rules/global

CXXFLAGS += -DV8_DEPRECATION_WARNINGS=1

objects = HTTPRequestWrapper HTTPResponseWrapper HTMLFormWrapper

target         = PocoJSNet
target_version = 1
target_libs    = PocoJSCore PocoUtil PocoXML PocoNet PocoFoundation v8

include $(POCO_BASE)/build/rules/lib
